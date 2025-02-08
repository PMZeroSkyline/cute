#ifndef DESKTOP_H
#define DESKTOP_H

#include "../app.h"


struct DesktopApp : App
{
    DesktopApp();
    ~DesktopApp() override;
    
    bool is_running() override;
    void poll_events() override;
};

#endif