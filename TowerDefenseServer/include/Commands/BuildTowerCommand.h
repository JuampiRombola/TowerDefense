#ifndef _BUILD_TOWER_COMMAND_
#define _BUILD_TOWER_COMMAND_

#include "Commands/Command.h"
class Map;

enum TowerType { Ground, Ice, Air, Fire };

class BuildTowerCommand : public Command {
private:
	unsigned int _xPos;
	unsigned int _yPos;

	TowerType _towerType;
	void _BuildGroundTower(Map* map);
	void _BuildFireTower(Map* map);
	void _BuildIceTower(Map* map);
	void _BuildAirTower(Map* map);
public:
	BuildTowerCommand(TowerType type, unsigned int x, unsigned int y);
	~BuildTowerCommand();
	void Execute(Map* map);
	TowerType GetTowerType();
};

#endif