#include "key.h"

void Key::recv(bool press)
{
    pressing = press;
    
    if (pressing)
        down = true;
    else
        up = true;
}
void Key::update(bool press)
{
    if (pressing != press)
        recv(press);
}
void Key::reset()
{
    up = false;
    down = false;
}