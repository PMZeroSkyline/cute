#ifndef TIMER_H
#define TIMER_H

#include <chrono>
struct Timer 
{
	std::chrono::high_resolution_clock::time_point start_time_;
    Timer() : start_time_(std::chrono::high_resolution_clock::now()) {}
    void reset();
    float elapsed() const;
};

#endif