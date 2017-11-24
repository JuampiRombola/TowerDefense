#ifndef _TOWERVM_
#define _TOWERVM_

#include "../Commands/BuildTowerCommand.h"

struct TowerVM {
	TowerType type;
	uint xPos;
	uint yPos;
	uint experience;
	uint level;
	uint nonFlyingDamage;
	uint range;
	uint collateral_damage;
	uint collateral_range;
	uint projectile_ms_over_tile;
	uint slow_percent;
	uint slow_seconds;
	uint damage;
	uint exp_required_for_range_upgrade;
	uint exp_required_for_damage_upgrade;
	uint exp_required_for_collateral_range_upgrade;
	uint exp_required_for_slow_upgrade;
};

#endif