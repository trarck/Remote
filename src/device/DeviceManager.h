#ifndef RC_DEVICE_DEVICEMANAGER_H_
#define RC_DEVICE_DEVICEMANAGER_H_
#include "DeviceMacros.h"

#include <yh/yh.h>
#include "Device.h"

NS_DEVICE_BEGIN

class DeviceManager:public Ref
{
public:
    DeviceManager();
    
    ~DeviceManager();
    
    void addDevice(std::string& name);
    
    void removeDevice(std::string& name);
    
protected:
    Vector<Device> _devices;
}

NS_DEVICE_END

#endif // RC_DEVICE_DEVICEMANAGER_H_