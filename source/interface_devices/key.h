#ifndef KEY_H
#define KEY_H

struct Key
{
    bool up = false;
    bool down = false;
    bool pressing = false;

    void recv(bool press);
    void update(bool press);
    void reset();
};

#endif