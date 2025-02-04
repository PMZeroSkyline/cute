#ifndef PLATFORM_DETECTION_H
#define PLATFORM_DETECTION_H

#if defined(_WIN32) || defined(_WIN64)
    #define WIN_OS
#elif defined(__APPLE__)
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE
        #define I_OS
    #elif TARGET_OS_MAC
        #define MAC_OS
    #else
        #define UNKNOWN_OS
    #endif
#elif defined(__ANDROID__)
    #define ANDROID_OS
#else
    #define UNKNOWN_OS
#endif


#endif