#include <iostream>
#include <fstream>

#include "../include/GameConfiguration.h"
#include "../include/yaml-cpp/yaml.h"

GameConfiguration::GameConfiguration(std::string& cfgpath) : Cfg(std::move(YAML::LoadFile(cfgpath)))
{
		//std::cout << "ctor: " << Cfg["towers"]["ground"]["range"] << "\n" << std::flush;

}

GameConfiguration::~GameConfiguration()
{

}