#ifndef RC_DEVICE_DEVICEMANAGER_H_
#define RC_DEVICE_DEVICEMANAGER_H_
#include "DeviceMacros.h"

#include <yh/yh.h>

#include "InputDevice.h"
#include "Define.h"

NS_DEVICE_BEGIN

class InputManager:public Ref
{
public:
    InputManager();
    
    ~InputManager();
    
    void addDevice(const std::string& name);

	void addDevice(const std::string& name,Device.OpenType type);
    
    void removeDevice(const std::string& name);

	bool contains(const std::string& name);
    
	int readEvents(struct input_event* events);
	int writeEvents(struct input_event* events,int count);

	void generatePollFds();

protected:
    Vector<Device> _devices;
	struct pollfd* _fds;

	bool _fdsDirty;
}

NS_DEVICE_END

#endif // RC_DEVICE_DEVICEMANAGER_H_