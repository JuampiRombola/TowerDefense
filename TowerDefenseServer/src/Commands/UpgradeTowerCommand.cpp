#include <iostream>

#include "../../include/Commands/UpgradeTowerCommand.h"
#include "../../include/TowerDefenseGame.h"
#include "../../include/Towers/Tower.h"
#include "../../include/Map/Map.h"
#include <yaml-cpp/yaml.h>
#include "../../include/ViewModels/CommandVM.h"


UpgradeTowerCommand::UpgradeTowerCommand(uint x, uint y, UpgradeType type):
 _xPos(x), _yPos(y), _type(type) {}

UpgradeTowerCommand::~UpgradeTowerCommand(){}

bool UpgradeTowerCommand::Execute(Map* map, TowerDefenseGame* game){
	SolidGroundTile* tile = map->GetSolidGroundTile(_xPos ,_yPos);
	if (tile == nullptr)
		return false;

	Tower* t = tile->GetTower();
	if (t != nullptr)
		return t->Upgrade(game->GameCfg.Cfg, _type);

	return false;
}

CommandVM UpgradeTowerCommand::GetViewModel(){
	CommandVM vm;
	vm.type = UpgradeTower;
	vm.upgradeType = _type;
	vm.xPos = _xPos;
	vm.yPos = _yPos;
	return vm;
}