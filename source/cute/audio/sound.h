#ifndef SOUND_H
#define SOUND_H

#include "audio_engine.h"

struct Sound
{
    ma_sound sound;
    ma_decoder decoder;
    char *buffer = nullptr;
    ma_result result = MA_ERROR;
    std::string path;
    Sound() = default;
    Sound(const std::string &_path);
    ~Sound();
};

#endif