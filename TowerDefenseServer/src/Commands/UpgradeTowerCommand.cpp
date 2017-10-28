#include <iostream>

#include "Commands/UpgradeTowerCommand.h"
#include "Towers/Tower.h"
#include <Map/Map.h>
#include "yaml-cpp/yaml.h"


UpgradeTowerCommand::UpgradeTowerCommand(uint x, uint y, UpgradeType type):
 _xPos(x), _yPos(y), _type(type) {}

UpgradeTowerCommand::~UpgradeTowerCommand(){}

bool UpgradeTowerCommand::Execute(Map* map, const YAML::Node& cfg){
	SolidGroundTile* tile = map->GetSolidGroundTile(_xPos ,_yPos);
	if (tile == nullptr)
		return false;

	Tower* t = tile->GetTower();
	if (t != nullptr)
		return t->Upgrade(cfg, _type);

	return false;
}