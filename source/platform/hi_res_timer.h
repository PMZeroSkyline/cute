#ifndef HI_RES_TIMER_H
#define HI_RES_TIMER_H

#include <chrono>
struct HiResTimer 
{
	std::chrono::high_resolution_clock::time_point start_time_;
    HiResTimer() : start_time_(std::chrono::high_resolution_clock::now()) {}
    void reset();
    float elapsed() const;
};

#endif