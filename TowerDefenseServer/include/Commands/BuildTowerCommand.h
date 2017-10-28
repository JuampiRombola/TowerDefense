#ifndef _BUILD_TOWER_COMMAND_
#define _BUILD_TOWER_COMMAND_

#include "Commands/Command.h"
#include "yaml-cpp/yaml.h"

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
	Tower* _BuildGroundTower(Map* map, SolidGroundTile* tile, const YAML::Node& cfg);
	Tower* _BuildFireTower(Map* map, SolidGroundTile* tile, const YAML::Node& cfg);
	Tower* _BuildWaterTower(Map* map, SolidGroundTile* tile, const YAML::Node& cfg);
	Tower* _BuildAirTower(Map* map, SolidGroundTile* tile, const YAML::Node& cfg);
public:
	BuildTowerCommand(TowerType type, uint x, uint y);
	~BuildTowerCommand();
	bool Execute(Map* map, TowerDefenseGame* game);
	TowerType GetTowerType();
};

#endif