#include "audio_engine.h"
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

AudioEngine::AudioEngine()
{
    result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS)
        std::cout << "failed to initialize audio engine." << std::endl;
}
AudioEngine::~AudioEngine()
{
    ma_engine_uninit(&engine);
}