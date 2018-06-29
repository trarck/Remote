#ifndef RC_DEVICE_DEVICE_H_
#define RC_DEVICE_DEVICE_H_
#include "DeviceMacros.h"

#include <yh/yh.h>
USING_NS_YH;

NS_DEVICE_BEGIN

struct input_event;

class Device:public Ref
{
public:
    enum OpenType
    {
        Read,
        Write,
        ReadWrite
    }

    Device(const std::string& path);
    void open(OpenType type);
    void close();
    int read(struct input_event* event);
    int write(struct input_event* event);

	inline int getFd()
	{
		return _fd;
	}

	inline std::string& getPath() 
	{
		return _path;
	}

protected:    
    std::string _path;
    int _fd;
    
}

NS_DEVICE_END

#endif // RC_DEVICE_DEVICE_H_