#ifndef SOUND_SERVICE_H
#define SOUND_SERVICE_H

#include "ISoundService.h"
#include <memory>

namespace BearBones
{
    //class SDLSoundSystemImpl;

    class SDLSoundSystem final : public ISoundService
    {
    public:
        SDLSoundSystem(int channelCount = 4);
        ~SDLSoundSystem() = default;

        void PlaySimple(const std::string& soundName, const float volume) override;
        void PauzeSimple() override;
        void Play(const std::string& soundName, const float volume) override;
        void SetVolume(const std::string& soundName, const float volume) override;
        void SetPauze(const std::string& soundName, bool isPauzed) override;

    private:
        class Impl;
        std::unique_ptr<Impl> m_pImpl;

        void HaltService();
    };
}
#endif // SOUND_SERVICE_H
