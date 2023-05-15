#pragma once
#include <string>

class ISoundService
{
public:
    virtual ~ISoundService() = default;
    virtual void Play(const std::string& soundName, const float volume) = 0;
};

class NullSoundService final : public ISoundService
{
public:
    NullSoundService() = default;
    ~NullSoundService() = default;

    // funky trick
    void Play(const std::string& /*soundName*/, const float /*volume*/) override {};
};
