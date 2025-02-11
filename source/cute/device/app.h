#ifndef DESKTOP_H
#define DESKTOP_H

#include "window.h"
#include "platform/hi_res_timer.h"
struct App
{
    std::shared_ptr<Window> window = nullptr;
    std::shared_ptr<HiResTimer> timer = nullptr;
    float time = 0.f;
    float delta_time = 0.f;
    static inline std::shared_ptr<App> instance = nullptr;
    App();
    virtual ~App();
    bool is_running();
    void poll_events();
    void update_timer();
    void update();
};

#endif