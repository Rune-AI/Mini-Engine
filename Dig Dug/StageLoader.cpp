#include "StageLoader.h"
#include <istreamwrapper.h>
#include <fstream>
#include <iostream>

void DigDug::StageLoader::LoadStage(const std::string& fileName, Stage& stage)
{
	rapidjson::Document document{};
	ReadJsonFile(fileName, document);

	stage.name = document["name"].GetString();
	stage.rows = document["rows"].GetInt();
	stage.cols = document["cols"].GetInt();

	assert(document["rocks"].IsArray());
	for (rapidjson::Value::ConstValueIterator itr = document["rocks"].Begin(); itr != document["rocks"].End(); ++itr)
	{
		const rapidjson::Value& attribute = *itr;
		assert(attribute.IsObject()); // each attribute is an object
		Position pos{};
		for (rapidjson::Value::ConstMemberIterator itr2 = attribute.MemberBegin(); itr2 != attribute.MemberEnd(); ++itr2)
		{
			if (itr2->name == "row")
			{
				pos.row = itr2->value.GetInt();
			}
			else if (itr2->name == "col")
			{
				pos.col = itr2->value.GetInt();
			}
		}
		stage.rocks.emplace_back(pos);
	}

	assert(document["pookas"].IsArray());
	for (rapidjson::Value::ConstValueIterator itr = document["pookas"].Begin(); itr != document["pookas"].End(); ++itr)
	{
		const rapidjson::Value& attribute = *itr;
		assert(attribute.IsObject()); // each attribute is an object
			Position pos{};
		for (rapidjson::Value::ConstMemberIterator itr2 = attribute.MemberBegin(); itr2 != attribute.MemberEnd(); ++itr2)
		{
			if (itr2->name == "row")
			{
				pos.row = itr2->value.GetInt();
			}
			else if (itr2->name == "col")
			{
				pos.col = itr2->value.GetInt();
			}
		}
			stage.pookas.emplace_back(pos);
	}

	assert(document["fygars"].IsArray());
	for (rapidjson::Value::ConstValueIterator itr = document["fygars"].Begin(); itr != document["fygars"].End(); ++itr)
	{
		const rapidjson::Value& attribute = *itr;
		assert(attribute.IsObject()); // each attribute is an object
			Position pos{};
		for (rapidjson::Value::ConstMemberIterator itr2 = attribute.MemberBegin(); itr2 != attribute.MemberEnd(); ++itr2)
		{
			if (itr2->name == "row")
			{
				pos.row = itr2->value.GetInt();
			}
			else if (itr2->name == "col")
			{
				pos.col = itr2->value.GetInt();
			}
		}
			stage.fygars.emplace_back(pos);
	}

	assert(document["groundIds"].IsArray());
	for (rapidjson::Value::ConstValueIterator itr = document["groundIds"].Begin(); itr != document["groundIds"].End(); ++itr)
	{
		const rapidjson::Value& attribute = *itr;
		assert(attribute.IsInt()); // each attribute is an object

		stage.groundStates.emplace_back(attribute.GetInt());
		attribute.GetInt();
	}
}

void DigDug::StageLoader::ReadJsonFile(const std::string& fileName, rapidjson::Document& document)
{
	std::ifstream ifs{ fileName };
	std::string jsonData((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	document.Parse(jsonData.c_str());

	if (document.HasParseError())
	{
		std::cout << "Error  : " << document.GetParseError() << '\n'
			<< "Offset : " << document.GetErrorOffset() << '\n';
	}
}
