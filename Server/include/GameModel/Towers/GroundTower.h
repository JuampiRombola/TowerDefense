#ifndef _GROUND_TOWER_
#define _GROUND_TOWER_

#include "yaml-cpp/yaml.h"
#include "Tower.h"
#include "../Commands/UpgradeTowerCommand.h"

class SolidGroundTile;
class Map;
class Projectile;
class TowerVM;

class GroundTower : public Tower {
protected:
	Projectile* _BuildProjectile(PathTile* target);
public:
	GroundTower(uint cooldown_sec, uint range, uint damage, SolidGroundTile* position, Map* map,
	uint projectile_ms_over_tile, ThreadSafeQueue<GameNotification*>& notifications);
	~GroundTower();
	void PrintDebug();
	bool Upgrade(UpgradeType type);
	TowerVM GetViewModel();
};

#endif
