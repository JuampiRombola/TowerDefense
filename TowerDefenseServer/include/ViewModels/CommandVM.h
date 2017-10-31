#ifndef _COMMANDVM_
#define _COMMANDVM_

#include "../Commands/BuildTowerCommand.h"
#include "../Commands/CastSpellCommand.h"
#include "../Commands/UpgradeTowerCommand.h"

enum CommandType { BuildTower, UpgradeTower, CastSpell }; 

struct CommandVM {
  CommandType type;

  Spell spellType;
  UpgradeType upgradeType;
  TowerType towerType;
  int xPos;
  int yPos;
  int unitId;
};

#endif