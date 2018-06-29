#include <stdlib.h>
#include <android/log.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/input.h>
#include <dirent.h>
#include <errno.h>
//#include "nativemethod.h"
 
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO, "EventEmulate", __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, "EventEmulate", __VA_ARGS__)
 
#define DEV_DIR "/dev/input"
#define sizeof_bit_array(bits)  ((bits + 7) / 8)
#define test_bit(bit, array)    (array[bit/8] & (1<<(bit%8)))
#define ABS_MT_POSITION_X 0x35
#define ABS_MT_POSITION_Y 0x36
 
struct EVENT_INFO
{
    int fd_touch;
    int fd_key;
    int screen_width;
    int screen_height;
    int abs_x_min;
    int abs_x_max;
    int abs_y_min;
    int abs_y_max;
};
 
int scan_dir(const char *dirname);
int open_dev(const char *deviceName);
int write_event(int fd, int type, int code, int value);
void calculateXY(float x, float y, int *abs_x, int *abs_y);
int containsNonZeroByte(const uint8_t* array, uint32_t startIndex, uint32_t endIndex);
 
struct EVENT_INFO ei;
int initEVT = 0;
 
int EVT_open(struct NATIVE_INFO *info)
{
    struct input_absinfo absinfo;
 
    if(initEVT)
        return 0;
 
    if(info == NULL)
    {
        LOGE("info null point.");
        goto fail;
    }
 
    if(info->FB_width == 0 || info->FB_height == 0)
    {
        LOGE("error width %d and height %d.", info->FB_width, info->FB_height);
        goto fail;
    }
 
    memset(&ei, 0, sizeof(ei));
    ei.screen_width = info->FB_width;
    ei.screen_height = info->FB_height;
 
    scan_dir(DEV_DIR);
 
    if(ioctl(ei.fd_touch, EVIOCGABS(ABS_X), &absinfo)) {
        LOGI("Error reading absolute controller ABS_X[%d]: %s", errno, strerror(errno));
        return;
    }
    ei.abs_x_min = absinfo.minimum;
    ei.abs_x_max = absinfo.maximum;
 
    if(ioctl(ei.fd_touch, EVIOCGABS(ABS_Y), &absinfo)) {
        LOGI("Error reading absolute controller ABS_Y[%d]: %s", errno, strerror(errno));
        return;
    }
    ei.abs_y_min = absinfo.minimum;
    ei.abs_y_max = absinfo.maximum;
 
    initEVT = 1;
    return 0;
 
fail:
    EVT_close();
    return -1;
}
 
int EVT_close()
{
    if(ei.fd_key > 0)
        close(ei.fd_key);
    if(ei.fd_touch > 0)
        close(ei.fd_touch);
 
    initEVT = 0;
    return 0;
}
 
int EVT_touch(int action, float x, float y)
{
    int abs_x, abs_y;
 
    if(initEVT == 0)
    {
        LOGE("event not inital");
        return -1;
    }
 
    switch(action)
    {
    case ACTION_DOWN:
        calculateXY(x, y, &abs_x, &abs_y);
        write_event(ei.fd_touch, 3, 0, abs_x);
        write_event(ei.fd_touch, 3, 1, abs_y);
        write_event(ei.fd_touch, 1, 330, 1);
        write_event(ei.fd_touch, 0, 0, 0);
        break;
    case ACTION_UP:
        write_event(ei.fd_touch, 1, 330, 0);
        write_event(ei.fd_touch, 0, 0, 0);
        break;
    case ACTION_MOVE:
        calculateXY(x, y, &abs_x, &abs_y);
        write_event(ei.fd_touch, 3, 0, abs_x);
        write_event(ei.fd_touch, 3, 1, abs_y);
        write_event(ei.fd_touch, 0, 0, 0);
        break;
    }
    return 0;
}
 
int EVT_key(int action, int key)
{
    if(initEVT == 0)
    {
        LOGE("event not inital");
        return -1;
    }
 
    switch(action)
    {
    case ACTION_DOWN:
        write_event(ei.fd_key, 1, key, 1);
        break;
    case ACTION_UP:
        write_event(ei.fd_key, 1, key, 0);
        break;
    }
    return 0;
}
 
 
int scan_dir(const char *dirname)
{
    char devname[PATH_MAX];
    char *filename;
    DIR *dir;
    struct dirent *de;
    dir = opendir(dirname);
    if(dir == NULL)
        return -1;
    strcpy(devname, dirname);
    filename = devname + strlen(devname);
    *filename++ = '/';
    while((de = readdir(dir))) {
        if(de->d_name[0] == '.' &&
           (de->d_name[1] == '\0' ||
            (de->d_name[1] == '.' && de->d_name[2] == '\0')))
            continue;
        strcpy(filename, de->d_name);
        open_dev(devname);
    }
    closedir(dir);
    return 0;
}
 
int open_dev(const char *deviceName)
{
    int fd;
    int version;
    uint8_t key_bitmask[sizeof_bit_array(KEY_MAX + 1)];
    uint8_t abs_bitmask[sizeof_bit_array(ABS_MAX + 1)];
 
    fd = open(deviceName, O_RDWR);
    if(fd < 0) {
        LOGI("could not open device[%d]: %s", errno, strerror(errno));
        return -1;
    }
 
    if(ioctl(fd, EVIOCGVERSION, &version)) {
        return -1;
    }
 
    memset(key_bitmask, 0, sizeof(key_bitmask));
    if (ioctl(fd, EVIOCGBIT(EV_KEY, sizeof(key_bitmask)), key_bitmask) >= 0) {
        if (containsNonZeroByte(key_bitmask, 0, sizeof_bit_array(BTN_MISC))
                || containsNonZeroByte(key_bitmask, sizeof_bit_array(BTN_GAMEPAD),
                        sizeof_bit_array(BTN_DIGI))
                || containsNonZeroByte(key_bitmask, sizeof_bit_array(KEY_OK),
                        sizeof_bit_array(KEY_MAX + 1))) {
            ei.fd_key = fd;
            LOGI("get key input device: %s", deviceName);
        }
    }
 
    memset(abs_bitmask, 0, sizeof(abs_bitmask));
    if (ioctl(fd, EVIOCGBIT(EV_ABS, sizeof(abs_bitmask)), abs_bitmask) >= 0) {
        // Is this a new modern multi-touch driver?
        if (test_bit(ABS_MT_POSITION_X, abs_bitmask)
                && test_bit(ABS_MT_POSITION_Y, abs_bitmask)) {
            ei.fd_touch = fd;
            LOGI("get multi-touch input device: %s", deviceName);
 
        // Is this an old style single-touch driver?
        } else if (test_bit(BTN_TOUCH, key_bitmask)
                && test_bit(ABS_X, abs_bitmask) && test_bit(ABS_Y, abs_bitmask)) {
            ei.fd_touch = fd;
            LOGI("get single-touch input device: %s", deviceName);
        }
    }
}
 
int write_event(int fd, int type, int code, int value)
{
    struct input_event event;
 
    memset(&event, 0, sizeof(event));
    event.type = type;
    event.code = code;
    event.value = value;
    if(write(fd, &event, sizeof(event)) < sizeof(event)) {
        LOGI("write event failed[%d]: %s", errno, strerror(errno));
        return -1;
    }
    return 0;
}
 
void calculateXY(float x, float y, int *abs_x, int *abs_y)
{
    *abs_x = ei.abs_x_min +
            (int)((x * (float)(ei.abs_x_max - ei.abs_x_min)) / ei.screen_width + 0.5);
    *abs_y = ei.abs_y_min +
            (int)((y * (float)(ei.abs_y_max - ei.abs_y_min)) / ei.screen_height + 0.5);
}
 
int containsNonZeroByte(const uint8_t* array, uint32_t startIndex, uint32_t endIndex)
{
    const uint8_t* end = array + endIndex;
    array += startIndex;
    while (array != end) {
        if (*(array++) != 0) {
            return 1;
        }
    }
    return 0;
}