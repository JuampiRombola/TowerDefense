#ifndef _ICE_TOWER_
#define _ICE_TOWER_


#include "yaml-cpp/yaml.h"
#include "Tower.h"
#include "Commands/UpgradeTowerCommand.h"


class SolidGroundTile;
class Map;
class Projectile;

class WaterTower : public Tower {
protected:
	Projectile* _BuildProjectile(PathTile* target);
public:
	WaterTower(uint cooldown_sec, uint range, uint damage, SolidGroundTile* position, Map* map);
	~WaterTower();
	void PrintDebug();
	bool Upgrade(const YAML::Node& cfg, UpgradeType type);
};

#endif
