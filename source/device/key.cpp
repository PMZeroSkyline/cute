#include "key.h"

void Key::set(bool press)
{
    pressing = press;

    if (pressing)
        down = true;
    else
        up = true;
}
void Key::reset()
{
    up = false;
    down = false;
}
void Key::update(bool press)
{
    if (pressing != press)
        set(press);
}