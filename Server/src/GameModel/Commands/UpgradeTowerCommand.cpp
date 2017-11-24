#include <iostream>

#include "../../../include/GameModel/Commands/UpgradeTowerCommand.h"
#include "../../../include/GameModel/TowerDefenseGame.h"
#include "../../../include/GameModel/Towers/Tower.h"
#include "../../../include/GameModel/Map/Map.h"
#include <yaml-cpp/yaml.h>
#include "../../../include/GameModel/ViewModels/CommandVM.h"
#include "../../../include/GameModel/GameNotifications/TowerUpgradedGameNotification.h"


UpgradeTowerCommand::UpgradeTowerCommand(uint x, uint y, UpgradeType type):
 _xPos(x), _yPos(y), _type(type) {}

UpgradeTowerCommand::~UpgradeTowerCommand(){}

bool UpgradeTowerCommand::Execute(Map* map, TowerDefenseGame* game, ThreadSafeQueue<GameNotification*>& notifications){
	SolidGroundTile* tile = map->GetSolidGroundTile(_xPos ,_yPos);
	if (tile == nullptr)
		return false;

	Tower* t = tile->GetTower();
	if (t == nullptr)
		return false;

	if (t->Upgrade(_type)){
		TowerVM vm = t->GetViewModel();
		game->notifications.Queue(new TowerUpgradedGameNotification(vm));
	}

	return false;
}
