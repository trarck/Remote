#include "InputManager.h"
	
InputManager::InputManager()
:_fds(NULL),
_fdsDirty(false)
{
    
}

InputManager::~InputManager()
{
	if (_fds != NULL)
	{
		free(_fds);
	}
}

void InputManager::addDevice(const std::string& name)
{
	addDevice(Device.OpenType.ReadWrite);
}

void InputManager::addDevice(const std::string& name, Device.OpenType type)
{
	if (contains(name)) 
	{
		return;
	}

	Device* device = new Device(name);

	device->open(Device.OpenType.ReadWrite);

	_devices.pushBack(device);

	device->release();

	//_fdsDirty = true;
}

void InputManager::removeDevice(const std::string& name)
{
	for (var iter = _devices.begin(); iter != _devices.end();++iter)
	{
		if ((*iter)->name == name) 
		{
			_devices.erase(iter);
			break;
		}
	}
	//_fdsDirty = true;
}

bool InputManager::contains(const std::string& name)
{
	for (var iter = _devices.begin(); iter != _devices.end(); ++iter)
	{
		if ((*iter)->name == name)
		{
			return true;
		}
	}
	return false;
}

int  InputManager::readEvents(struct input_event* events)
{
	if (_devices.size() == 0 || data==NULL) return 0;

	if (_fds == NULL)
	{
		generatePollFds();
	}

	if (poll(_fds, _devices.size(), -1) < 0)
	{
		YHERROR("InputManager::readDevice poll error");
	}
	
	int numRead=0,count=0;

	for (int i = 0, l = _devices.size(); i < l;++i)
	{
		if (_fds[i].revents& POLLIN) {
			numRead = _devices[i].read(&events[count]);
			if (numRead != sizeof(struct input_event)) {
				YHERROR("read error need %d real %d", sizeof(struct input_event), numRead);
				return count;
			}
			++count;
		}
	}
	return count;
}

int InputManager::writeEvents(struct input_event* events,int count)
{
	for (int i = 0; i < count; ++i) {

	}
}

void InputManager::generatePollFds()
{
	//if (!_fdsDirty) return;

	size_t fdsSize = sizeof(struct pollfd)*_devices.size();
	
	struct pollfd* newFds = realloc(_fds, fdsSize);
	if (newFds == NULL) {
		//show log
		YHERROR("out of memory in InputManager::generatePollFds");
		return;
	}

	memset(newFds, 0, fdsSize);
	_fds = newFds;

	int i = 0;
	for (var iter = _devices.begin(); iter != _devices.end();++iter,++i)
	{
		_fds[i].fd = (*iter)->getFd();
		_fds[i].events = POLLIN;
	}

	//_fdsDirty = false;
}
