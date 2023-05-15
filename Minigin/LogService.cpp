#include "LogService.h"
#include <iostream>

LogService::LogService(ISoundService* soundService)
    : m_soundService{ soundService }
{
    std::cout << "Logging system created\n";
}

LogService::~LogService()
{
    std::cout << "Logging system destroyed\n";
    delete m_soundService;
}

void LogService::Play(const std::string& soundName, const float volume)
{
    std::cout << "Playing sound: " << soundName << " at volume: " << volume << '\n';
    m_soundService->Play(soundName, volume);
}