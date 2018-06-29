#ifndef RC_DEVICE_INPUT_EVENT_H_
#define RC_DEVICE_INPUT_EVENT_H_

struct input_event {
 struct timeval time;
 unsigned short type;
 unsigned short code;
 int value;
};

/* define in WinSock2.h
struct pollfd {
 int fd;
 short events;
 short revents;
};
*/

#define poll WSAPoll

#endif // RC_DEVICE_INPUT_EVENT_H_