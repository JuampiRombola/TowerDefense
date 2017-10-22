#ifndef _BUILD_TOWER_COMMAND_
#define _BUILD_TOWER_COMMAND_

#include "Command.h"

enum TowerType { Ground, Ice, Air, Fire };

class BuildTowerCommand : public Command {
private:
	TowerType _towerType;
public:
	BuildTowerCommand(TowerType type);
	virtual ~BuildTowerCommand();
	void Execute();
	TowerType GetTowerType();
};

#endif