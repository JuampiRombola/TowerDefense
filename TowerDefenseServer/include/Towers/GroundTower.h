#ifndef _GROUND_TOWER_
#define _GROUND_TOWER_

#include "yaml-cpp/yaml.h"
#include "Tower.h"
#include "Commands/UpgradeTowerCommand.h"

class SolidGroundTile;
class Map;
class Projectile;
class TowerVM;

class GroundTower : public Tower {
protected:
	Projectile* _BuildProjectile(PathTile* target);
public:
	GroundTower(uint cooldown_sec, uint range, uint damage, SolidGroundTile* position, Map* map);
	~GroundTower();
	void PrintDebug();
	bool Upgrade(const YAML::Node& cfg, UpgradeType type);
	TowerVM GetViewModel();
};

#endif
