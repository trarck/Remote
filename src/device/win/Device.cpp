#include "Device.h"

#include "Define.h"

#define INPUT_EVENT_SIZE sizeof(struct input_event)

NS_DEVICE_BEGIN

Device::Device(const std::string& path)
:_path(path),
_fd(0)
{
    
}

void Device::open(OpenType type)
{

    
    //TODO get id and version
}

void Device::close()
{

}

int Device::read(struct input_event* event)
{
    return 0;
}

int Device::write(struct input_event* event)
{
    return 0;
}

NS_DEVICE_END