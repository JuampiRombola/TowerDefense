#ifndef _BUILD_TOWER_COMMAND_
#define _BUILD_TOWER_COMMAND_

#include "Commands/Command.h"
class Map;

enum TowerType { Ground, Ice, Wind, Fire };

class BuildTowerCommand : public Command {
private:
	unsigned int _xPos;
	unsigned int _yPos;

	TowerType _towerType;
	std::shared_ptr<Tower> _BuildGroundTower(Map* map, std::shared_ptr<SolidGroundTile> tile);
	std::shared_ptr<Tower> _BuildFireTower(Map* map, std::shared_ptr<SolidGroundTile> tile);
	std::shared_ptr<Tower> _BuildIceTower(Map* map, std::shared_ptr<SolidGroundTile> tile);
	std::shared_ptr<Tower> _BuildWindTower(Map* map, std::shared_ptr<SolidGroundTile> tile);
public:
	BuildTowerCommand(TowerType type, unsigned int x, unsigned int y);
	~BuildTowerCommand();
	void Execute(Map* map);
	TowerType GetTowerType();
};

#endif