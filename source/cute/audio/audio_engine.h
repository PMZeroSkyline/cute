#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H

#include "miniaudio.h"
#include <memory>
#include <iostream>

struct AudioEngine
{
    ma_engine engine;
    ma_result result = MA_ERROR;
    static inline std::shared_ptr<AudioEngine> instance = std::make_shared<AudioEngine>();
    AudioEngine();
    ~AudioEngine();
};

#endif