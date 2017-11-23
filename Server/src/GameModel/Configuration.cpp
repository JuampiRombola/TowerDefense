#include <iostream>
#include <fstream>

#include "../../include/GameModel/Configuration.h"
#include <yaml-cpp/yaml.h>

Configuration::Configuration(std::string& cfgpath, uint id, std::string cfgName)
        : _id(id), _name(cfgName), Cfg(std::move(YAML::LoadFile(cfgpath)))
{
		//std::cout << "ctor: " << Cfg["towers"]["ground"]["range"] << "\n" << std::flush;

}

Configuration::~Configuration()
{

}

std::string Configuration::Name(){
    return _name;
}
uint Configuration::Id(){
    return _id;
}