#ifndef KEY_H
#define KEY_H

struct Key
{
    bool up = false;
    bool down = false;
    bool pressing = false;

    void set(bool press);
    void reset();
    void update(bool press);
};

#endif