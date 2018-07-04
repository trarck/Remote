#include "InputDevice.h"

#include "Define.h"

#define INPUT_EVENT_SIZE sizeof(struct input_event)

NS_DEVICE_BEGIN

InputDevice::InputDevice(const std::string& path)
:_path(path),
_fd(0)
{
    
}

void InputDevice::open(OpenType type)
{

    
    //TODO get id and version
}

void InputDevice::close()
{

}

int InputDevice::read(struct input_event* event)
{
    return 0;
}

int InputDevice::write(struct input_event* event)
{
    return 0;
}

NS_DEVICE_END