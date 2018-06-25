#ifndef RC_DEVICE_INPUT_EVENT_H_
#define RC_DEVICE_INPUT_EVENT_H_
#include "DeviceMacros.h"

struct input_event {
 struct timeval time;
 unsigned short type;
 unsigned short code;
 int value;
};


#endif // RC_DEVICE_INPUT_EVENT_H_