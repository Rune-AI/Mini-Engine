#pragma once
#include "ISoundService.h"
#include <memory>

class SDLSoundSystem final : public ISoundService
{
public:
    SDLSoundSystem(int channelCount = 8);
    ~SDLSoundSystem();

    void Play(const std::string& soundName, const float volume) override;

private:
    class SDLSoundSystemImpl; // Forward declaration of the implementation class
    std::unique_ptr<SDLSoundSystemImpl> m_pImpl; // Pointer to the implementation

    void Stop();
};