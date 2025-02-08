#ifndef APP_H
#define APP_H

#include "window.h"
#include "platform/hi_res_timer.h"

struct App
{
    static inline std::shared_ptr<App> instance = nullptr;

    std::shared_ptr<Window> window = nullptr;
    
    std::shared_ptr<HiResTimer> timer = nullptr;
    float time = 0.f;
    float delta_time = 0.f;

    virtual ~App() = default;
    virtual bool is_running() = 0;
    virtual void poll_events() = 0;
    void update_timer();
    void update();
};

#endif