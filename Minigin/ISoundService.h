#ifndef SOUND_SERVICE_INTERFACE_H
#define SOUND_SERVICE_INTERFACE_H

#include <string>

namespace BearBones
{
    class ISoundService
    {
    public:
        virtual ~ISoundService() = default;
        
        virtual void PlaySimple(const std::string& soundName, const float volume) = 0;
        virtual void PauzeSimple() = 0;
        virtual void Play(const std::string& soundName, const float volume) = 0;
        virtual void SetVolume(const std::string& soundName, const float volume)= 0;
        virtual void SetPauze(const std::string& soundName, bool isPauzed) = 0;
    };

    class NullSoundService final : public ISoundService
    {
    public:
        NullSoundService() = default;
        ~NullSoundService() = default;

        void PlaySimple(const std::string& /*soundName*/, const float /*volume*/) override {};
        void PauzeSimple() override {};
        void Play(const std::string& /*soundName*/, const float /*volume*/) override {};
        void SetVolume(const std::string& /*soundName*/, const float /*volume*/) override {};
        void SetPauze(const std::string& /*soundName*/, bool /*isPauzed*/) override {};
    };
}
#endif // SOUND_SERVICE_INTERFACE