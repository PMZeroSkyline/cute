#ifndef CONSOLE_WINDOW_H
#define CONSOLE_WINDOW_H
#include "editor_window.h"
#include <vector>
#include <string>
struct ConsoleWindow : EditorWindow
{
    std::vector<std::string> lines;
    char input_buffer[256];
    void draw() override;
    void execute(const std::string cmd);
};

#endif