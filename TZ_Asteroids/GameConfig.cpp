#include "GameConfig.h"
#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

void GameConfig::Initialize(int argc, char *argv[])
{
	map<string, string> arguments;
	for (int i = 1; i < argc; ++i)
	{
		arguments[argv[i]] = argv[++i];
	}
	map<string, string>::iterator it;
	const char* delim = "x";
	std::vector<std::string> out;
	char* token;
	for (auto it = arguments.begin(); it != arguments.end(); ++it)
	{
		if (strcmp((it->first).c_str(), "-window") == 0)
		{
			char *cstr = &(it->second)[0];
			token = strtok(cstr, delim);
			while (token != nullptr)
			{
				out.push_back(std::string(token));
				token = strtok(nullptr, delim);
			}

			if (out.size() == 2)
			{
				windowWidth = stoi(out[0]);
				windowHeight = stoi(out[1]);
			}
			out.clear();
		}
		if (strcmp((it->first).c_str(), "-map") == 0)
		{
			char *cstr = &(it->second)[0];
			token = strtok(cstr, delim);
			while (token != nullptr)
			{
				out.push_back(std::string(token));
				token = strtok(nullptr, delim);
			}

			if (out.size() == 2)
			{
				mapWidth = stoi(out[0]);
				mapHeight = stoi(out[1]);
			}
			out.clear();
		}
		if (strcmp((it->first).c_str(), "-num_asteroids") == 0)
		{
			numAsteroids = stoi(it->second);
		}
		if (strcmp((it->first).c_str(), "-num_ammo") == 0)
		{
			numAmmo = stoi(it->second);
		}
		if (strcmp((it->first).c_str(), "-ability_probability") == 0)
		{
			abilityProbability = stof(it->second);
		}
	}
}
