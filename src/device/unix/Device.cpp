#include "Device.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/inotify.h>
#include <sys/limits.h>
#include <sys/poll.h>
#include <linux/input.h>
#include <errno.h>

#define INPUT_EVENT_SIZE sizeof(struct input_event)

NS_DEVICE_BEGIN

Device::Device(const std::string& path)
:_path(path),
_fd(-1)
{
    
}

void Device::open(OpenType type)
{
    int flags=0;
    switch(type){
        case:OpenType.Read:
            flags=O_RDONLY | O_NDELAY;
            break;
        case:OpenType.Write:
            flags=O_WRONLY | O_NDELAY;
            break;
        case:OpenType.ReadWrite:
            flags=O_RDWR;
            break;
    }
    _fd=open(_path.c_str(),flags);
    if (_fd < 0) {
        fprintf(stderr, "could not open %s, %s\n", _path.c_str(), strerror(errno));
        return;
    }
    
    //TODO get id and version
}

void Device::close()
{
    if(_fd<0)
    {
        return;
    }
    
    close(_fd);
    _fd=-1;
}

int Device::read(struct input_event* event)
{
    if(_fd<0 || event==NULL)
    {
        return 0;
    }
    
    return read(_fd, event, INPUT_EVENT_SIZE);
}

int Device::write(struct input_event* event)
{
    if(_fd<0 || event==NULL)
    {
        return 0;
    }
    return write(_fd, event, INPUT_EVENT_SIZE);
}

NS_DEVICE_END