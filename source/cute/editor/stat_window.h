#ifndef STATUS_WINDOW_H
#define STATUS_WINDOW_H
#include "editor_window.h"
struct StatWindow : EditorWindow
{
    void draw() override;
};
#endif