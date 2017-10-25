#ifndef _FIRE_TOWER_
#define _FIRE_TOWER_

#include <memory>

#include "Tower.h"

class SolidGroundTile;
class Map;
class Projectile;

class FireTower : public Tower {
protected:
	std::shared_ptr<Projectile> _BuildProjectile(std::shared_ptr<PathTile> target);
public:
	FireTower(uint cooldown_sec, uint range, uint damage, std::shared_ptr<SolidGroundTile> position, Map* map);
	~FireTower();
	void PrintDebug();
};

#endif
