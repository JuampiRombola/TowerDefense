#ifndef _TOWERVM_
#define _TOWERVM_

#include "Commands/BuildTowerCommand.h"

struct TowerVM {
	TowerType type;
	uint xPos;
	uint yPos;
	uint experience;
	uint level;
};

#endif