#ifndef _FIRE_TOWER_
#define _FIRE_TOWER_

#include "Tower.h"
#include "yaml-cpp/yaml.h"
#include "../Commands/UpgradeTowerCommand.h"

class SolidGroundTile;
class Map;
class Projectile;
class TowerVM;

class FireTower : public Tower {
protected:
	uint _collateralDamage;
	uint _collateralRange;
	Projectile* _BuildProjectile(PathTile* target);
public:
	FireTower(uint cooldown_ms, uint range, uint damage, 
		SolidGroundTile* position, Map* map, uint collateralDamange, uint collateralRange, ThreadSafeQueue<GameNotification*>& notifications);
	~FireTower();
	void PrintDebug();
	bool Upgrade(const YAML::Node& cfg, UpgradeType type);
	TowerVM GetViewModel();
};

#endif
