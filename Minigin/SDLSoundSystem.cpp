#include "SDLSoundSystem.h"
#include <SDL_mixer.h>
#include <cassert>
#include "ResourceManager.h"
#include <mutex>

class BearBones::SDLSoundSystem::Impl
{
public:
    Impl(int channelCount);
    ~Impl();

    void PlaySimple(const std::string& soundName, const float volume);
    void PauzeSimple();
    void Play(const std::string& soundName, const float volume);
    void SetVolume(const std::string& soundName, const float volume);
    void SetPauze(const std::string& soundName, const bool isPauzed);
    
    void HaltService();

private:
    void SoundPlayLoop();

    struct PlaySound
    {
        std::string soundName;
        float volume;
        bool isPlaying;
        bool isDirty;
        int channel;
    };

    bool m_isHaltCalled;
    std::mutex m_queueMutex;
    std::condition_variable m_queueCondition;


    // ring buffer
    int m_head;
    int m_tail;

    // song queue
    static const int m_maxPending = 16;
    PlaySound m_pendingSounds[m_maxPending];
    int m_numPendingSounds;

    
};


BearBones::SDLSoundSystem::SDLSoundSystem(int channelCount)
    : m_pImpl(std::make_unique<Impl>(channelCount))
{
}

void BearBones::SDLSoundSystem::PlaySimple(const std::string& soundName, const float volume)
{
    m_pImpl->PlaySimple(soundName, volume);
}

void BearBones::SDLSoundSystem::PauzeSimple()
{
    m_pImpl->PauzeSimple();
}

void BearBones::SDLSoundSystem::Play(const std::string& soundName, const float volume)
{
    m_pImpl->Play(soundName, volume);
}

void BearBones::SDLSoundSystem::SetVolume(const std::string& soundName, const float volume)
{
    m_pImpl->SetVolume(soundName, volume);
}

void BearBones::SDLSoundSystem::SetPauze(const std::string& soundName, bool isPauzed)
{
    m_pImpl->SetPauze(soundName, isPauzed);
}

void BearBones::SDLSoundSystem::HaltService()
{
    m_pImpl->HaltService();
}

BearBones::SDLSoundSystem::Impl::Impl(int channelCount)
    : m_isHaltCalled{false}
{
    m_head = 0;
    m_tail = 0;

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, channelCount, 2048);
    //Mix_ReserveChannels(channelCount);

    /*std::thread soundThread(&Impl::SoundPlayLoop, this);
    soundThread.detach();*/
}

BearBones::SDLSoundSystem::Impl::~Impl()
{
}

void BearBones::SDLSoundSystem::Impl::PlaySimple(const std::string& soundName, const float /*volume*/)
{
    std::string SoundPath = ResourceManager::GetInstance().LoadSound(soundName);
    auto resource = Mix_LoadMUS(SoundPath.c_str());
    Mix_PlayMusic(resource, 0);
}

void BearBones::SDLSoundSystem::Impl::PauzeSimple()
{

	Mix_PauseMusic();
}

void BearBones::SDLSoundSystem::Impl::Play(const std::string& soundName, const float volume)
{
    {
        std::unique_lock<std::mutex> lock(m_queueMutex);

        // If sound already pending, merge
        for (int i = m_head; i != m_tail;
            i = (i + 1) % m_maxPending)
        {
            if (m_pendingSounds[i].soundName == soundName)
            {
                // Use the larger of the two volumes.
                m_pendingSounds[i].volume = std::max(volume, m_pendingSounds[i].volume);

                // Don't need to enqueue.
                return;
            }
        }


        // Add to the end of the list.
        assert((m_tail + 1) % m_maxPending != m_head);


        m_pendingSounds[m_tail].soundName = soundName;
        m_pendingSounds[m_tail].volume = volume;
        m_pendingSounds[m_tail].isPlaying = true;

        m_tail = (m_tail + 1) % m_maxPending; 
    }
    m_queueCondition.notify_one();


    
}

void BearBones::SDLSoundSystem::Impl::SetVolume(const std::string& /*soundName*/, const float /*volume*/)
{

}

void BearBones::SDLSoundSystem::Impl::SetPauze(const std::string& /*soundName*/, const bool /*isPauzed*/)
{
}

void BearBones::SDLSoundSystem::Impl::HaltService()
{
    m_isHaltCalled = true;
}

void BearBones::SDLSoundSystem::Impl::SoundPlayLoop()
{
    while (true)
    {
        if (m_isHaltCalled) break;

        // If there are no pending requests, do nothing.
        if (m_head == m_tail) continue;

        std::string SoundPath = ResourceManager::GetInstance().LoadSound(m_pendingSounds[m_head].soundName);
        auto resource = Mix_LoadWAV(SoundPath.c_str());
        auto channel = Mix_PlayChannel( -1, resource, 0);
        
        if (channel == -1) continue;
        m_pendingSounds[m_head].channel = channel;
        int adjustedVolume = int(m_pendingSounds[m_head].volume * MIX_MAX_VOLUME);
        Mix_Volume(channel, adjustedVolume);

        m_head = (m_head + 1) % m_maxPending;


        // updating sound logic
        // this will ignore sounds that are outside of the pending queue but might still be playing
        for (size_t i = 0; i < m_maxPending; i++)
        {
            if (m_pendingSounds[i].isDirty)
            {
                if (m_pendingSounds[i].isPlaying)
                {
                    Mix_PlayChannel(m_pendingSounds[i].channel, resource, 0);
                }
                else
                {
                    Mix_Pause(m_pendingSounds[i].channel);
                }
            }

        }
    }

    Mix_CloseAudio();
}
