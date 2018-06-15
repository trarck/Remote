#ifndef YH_DEVICEMACROS_H_
#define YH_DEVICEMACROS_H_

#ifdef __cplusplus

#define NS_DEVICE_BEGIN                     namespace device {
#define NS_DEVICE_END                       }
#define USING_NS_DEVICE                     using namespace device

#else

#define NS_DEVICE_BEGIN                     
#define NS_DEVICE_END                       
#define USING_NS_DEVICE

#endif
	
#endif //YH_DEVICEMACROS_H_