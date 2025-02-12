#ifndef STATUS_WINDOW_H
#define STATUS_WINDOW_H
#include "editor_window.h"
struct StatusWindow : EditorWindow
{
    void draw() override;
};
#endif