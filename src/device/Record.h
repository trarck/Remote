#ifndef RC_DEVICE_RECORD_H_
#define RC_DEVICE_RECORD_H_
#include "DeviceMacros.h"

#include <string>
#include <vector>

NS_DEVICE_BEGIN

struct input_event;

class Record
{
public:
    Record();
    
    ~Record();
    
    void Init();
    
protected:
    std::vector<Device*> _devices;
    
    
}

NS_DEVICE_END

#endif // RC_DEVICE_RECORD_H_