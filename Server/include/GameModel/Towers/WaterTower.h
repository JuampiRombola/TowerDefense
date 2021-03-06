#ifndef _ICE_TOWER_
#define _ICE_TOWER_


#include "yaml-cpp/yaml.h"
#include "Tower.h"
#include "../Commands/UpgradeTowerCommand.h"


class SolidGroundTile;
class Map;
class Projectile;
class TowerVM;

class WaterTower : public Tower {
protected:
	uint _slowPercent;
	uint _slowDuration_sec;
	Projectile* _BuildProjectile(PathTile* target);
public:
	WaterTower(uint cooldown_sec, uint range, uint damage, uint slowPercent, uint slowDuration_sec,
	 SolidGroundTile* position, Map* map, uint projectile_ms_over_tile, ThreadSafeQueue<GameNotification*>& notifications);
	~WaterTower();
	void PrintDebug();
	bool Upgrade(UpgradeType type);
	TowerVM GetViewModel();
	TowerType GetTowerType();
};

#endif
