#ifndef _GAME_CONFIGURATION_
#define _GAME_CONFIGURATION_

#include <string>
#include "yaml-cpp/yaml.h"

class GameConfiguration{
private:

public:
	GameConfiguration(std::string& cfgpath);
	~GameConfiguration();
	const YAML::Node Cfg;
};

#endif
