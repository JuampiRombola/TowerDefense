#ifndef _GAME_CONFIGURATION_
#define _GAME_CONFIGURATION_

#include <string>
#include "yaml-cpp/yaml.h"

class Configuration{
private:
	uint _id;
	std::string _name;
public:
	Configuration(std::string& cfgpath, uint id, std::string cfgname);
	~Configuration();
	const YAML::Node Cfg;
	std::string Name();
	uint Id();
};

#endif
