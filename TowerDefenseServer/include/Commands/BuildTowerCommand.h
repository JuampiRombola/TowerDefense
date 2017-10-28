#ifndef _BUILD_TOWER_COMMAND_
#define _BUILD_TOWER_COMMAND_

#include "Commands/Command.h"
class Map;
class TowerDefenseGame;
class Tower;
class SolidGroundTile;

enum TowerType { Ground, Ice, Wind, Fire };

class BuildTowerCommand : public Command {
private:
	unsigned int _xPos;
	unsigned int _yPos;

	BuildTowerCommand( const BuildTowerCommand& );
    const BuildTowerCommand& operator=( const BuildTowerCommand& );

	TowerType _towerType;
	Tower* _BuildGroundTower(Map* map, SolidGroundTile* tile);
	Tower* _BuildFireTower(Map* map, SolidGroundTile* tile);
	Tower* _BuildIceTower(Map* map, SolidGroundTile* tile);
	Tower* _BuildWindTower(Map* map, SolidGroundTile* tile);
public:
	BuildTowerCommand(TowerType type, unsigned int x, unsigned int y);
	~BuildTowerCommand();
	void Execute(Map* map, TowerDefenseGame* game);
	TowerType GetTowerType();
};

#endif