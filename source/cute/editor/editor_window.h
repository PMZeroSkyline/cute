#ifndef DEBUG_WINDOW_H
#define DEBUG_WINDOW_H

struct EditorWindow
{
    bool open = false;
    EditorWindow() = default;
    virtual ~EditorWindow() = default;
    virtual void draw() = 0;
};
#endif