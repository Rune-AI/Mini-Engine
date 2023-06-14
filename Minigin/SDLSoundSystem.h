#ifndef SOUND_SERVICE_H
#define SOUND_SERVICE_H

#include "ISoundService.h"
#include <memory>

namespace BearBones
{
    class SDLSoundSystemImpl;

    class SDLSoundSystem final : public ISoundService
    {
    public:
        SDLSoundSystem(int channelCount = 4);
        ~SDLSoundSystem() = default;

        void Play(const std::string& soundName, const float volume) override;
        void SetVolume(const std::string& soundName, const float volume) override;
        void SetPauze(const std::string& soundName, bool isPauzed) override;

    private:
        
        std::unique_ptr<SDLSoundSystemImpl> m_pImpl;

        void HaltService();
    };
}
#endif // SOUND_SERVICE_H
