#include "sound.h"

Sound::Sound(const std::string &_path) : path(_path)
{
    result = ma_decoder_init_file(path.c_str(), NULL, &decoder);
    if (result != MA_SUCCESS)
    {
        std::cout << "failed to decoder " << path << std::endl;
        return;
    }
    result = ma_sound_init_from_data_source(&AudioEngine::instance->engine, &decoder, 0, NULL, &sound);
    if (result != MA_SUCCESS)
    {
        std::cout << "failed to init sound " << path << std::endl;
        return;
    }
}
Sound::~Sound()
{
    ma_sound_uninit(&sound);
    ma_decoder_uninit(&decoder);
    if (buffer)
    {
        free(buffer);
        buffer = nullptr;
    }
}