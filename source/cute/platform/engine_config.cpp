#include "engine_config.h"

#ifdef WIN_OS
#include <Windows.h>
#endif


#ifdef WIN_OS
extern "C" {
    int AmdPowerXpressRequestHighPerformance = 1;
    DWORD NvOptimusEnablement = 0x00000001;
}
#endif