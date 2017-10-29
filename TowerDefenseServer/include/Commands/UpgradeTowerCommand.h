#ifndef _UPGRADE_TOWER_COMMAND_
#define _UPGRADE_TOWER_COMMAND_

#include "Commands/Command.h"
#include "yaml-cpp/yaml.h"

class Map;
class TowerDefenseGame;

enum UpgradeType { Range, Damage, CollateralRange, Slow };

class UpgradeTowerCommand : public Command {
private:
	uint _xPos;
	uint _yPos;
	UpgradeType _type;
public:
	UpgradeTowerCommand(uint x, uint y, UpgradeType type);
	~UpgradeTowerCommand();
	bool Execute(Map* map, TowerDefenseGame* game);
	CommandVM GetViewModel();
};

#endif