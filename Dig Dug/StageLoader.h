#ifndef STAGE_LOADER_H
#define STAGE_LOADER_H

#include <string>
#include <rapidjson.h>
#include <document.h>
#include "Stage.h"

namespace DigDug
{
	class StageLoader
	{
    public:
        StageLoader() = default;
        ~StageLoader() = default;

        void LoadStage(const std::string& fieldName, Stage& level);

    private:
        void ReadJsonFile(const std::string& fileName, rapidjson::Document& document);
        int ReadObject(const std::string& fieldName, const std::string& subFieldName, rapidjson::Document& document);

        std::string m_CurrentFileName{};
	};
}

#endif