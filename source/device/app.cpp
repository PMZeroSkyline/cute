#include "app.h"


void App::update_timer()
{
    if (!timer)
    {
        timer = std::make_shared<HiResTimer>();
    }
    float elapsed = timer->elapsed();
    delta_time = elapsed - time;
    time = elapsed;
}
void App::update() 
{
    update_timer();
    window->reset_input();
    poll_events();
};