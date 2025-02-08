#include "hi_res_timer.h"

void HiResTimer::reset() 
{
    start_time_ = std::chrono::high_resolution_clock::now();
}
float HiResTimer::elapsed() const 
{
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::duration<float>>(end_time - start_time_);
    return duration.count();
}