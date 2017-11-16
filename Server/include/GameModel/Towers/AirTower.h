#ifndef _AIR_TOWER_
#define _AIR_TOWER_

#include "../Commands/UpgradeTowerCommand.h"
#include "yaml-cpp/yaml.h"
#include "Tower.h"

class SolidGroundTile;
class Map;
class TowerVM;
class Projectile;

class AirTower : public Tower {
private:
	uint _nonFlyingDamage;
protected:
	Projectile* _BuildProjectile(PathTile* target);
public:
	AirTower(uint cooldown_sec, uint range, uint damage,
			 uint nonFlyingDamage, SolidGroundTile* position, Map* map,
			uint projectile_ms_over_tile);
	~AirTower();
	void PrintDebug();
	bool Upgrade(const YAML::Node& cfg, UpgradeType type);
	TowerVM GetViewModel();
};

#endif
