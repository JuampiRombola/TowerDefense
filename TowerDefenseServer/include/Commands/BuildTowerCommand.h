#ifndef _BUILD_TOWER_COMMAND_
#define _BUILD_TOWER_COMMAND_

#include "../Commands/Command.h"
#include "yaml-cpp/yaml.h"

#include "../ThreadSafeQueue.h"
#include "../GameNotifications/GameNotification.h"

#ifndef __GAME_NOTIFICATION_QUEUE__2
#define __GAME_NOTIFICATION_QUEUE__2
template class ThreadSafeQueue<GameNotification*>;
#endif


class Map;
class TowerDefenseGame;
class Tower;
class SolidGroundTile;

enum TowerType { Ground, Water, Air, Fire };

class BuildTowerCommand : public Command {
private:
	uint _xPos;
	uint _yPos;

	TowerType _towerType;
	Tower* _BuildGroundTower(Map* map, SolidGroundTile* tile, const
	YAML::Node& cfg, ThreadSafeQueue<GameNotification*>& notifications);
	Tower* _BuildFireTower(Map* map, SolidGroundTile* tile, const YAML::Node& cfg, ThreadSafeQueue<GameNotification*>& notifications);
	Tower* _BuildWaterTower(Map* map, SolidGroundTile* tile, const YAML::Node& cfg, ThreadSafeQueue<GameNotification*>& notifications);
	Tower* _BuildAirTower(Map* map, SolidGroundTile* tile, const YAML::Node& cfg, ThreadSafeQueue<GameNotification*>& notifications);
public:
	BuildTowerCommand(TowerType type, uint x, uint y);
	~BuildTowerCommand();
	bool Execute(Map* map, TowerDefenseGame* game);
	TowerType GetTowerType();
	CommandVM GetViewModel();
};

#endif