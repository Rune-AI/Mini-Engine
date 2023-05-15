#pragma once
#include "ISoundService.h"

class LogService final : public ISoundService
{
public:
    LogService(ISoundService* soundService);
    ~LogService();

    void Play(const std::string& soundName, const float volume) override;

private:
    ISoundService* m_soundService;
};