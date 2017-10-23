#ifndef _BUILD_TOWER_COMMAND_
#define _BUILD_TOWER_COMMAND_

#include "Command.h"
#include "Map.h"

enum TowerType { Ground, Ice, Air, Fire };

class BuildTowerCommand : public Command {
private:
	unsigned int _xPos;
	unsigned int _yPos;

	TowerType _towerType;
	void _BuildGroundTower(Map* map);
	void _BuildFireTower();
	void _BuildIceTower();
	void _BuildAirTower();
public:
	BuildTowerCommand(TowerType type, unsigned int x, unsigned int y);
	~BuildTowerCommand();
	void Execute(Map* map);
	TowerType GetTowerType();
};

#endif