#ifndef _GROUND_TOWER_
#define _GROUND_TOWER_

#include <memory>

#include "Tower.h"

class SolidGroundTile;
class Map;
class Projectile;

class GroundTower : public Tower {
protected:
	std::shared_ptr<Projectile> _BuildProjectile(std::shared_ptr<PathTile> target);
public:
	GroundTower(uint cooldown_sec, uint range, uint damage, std::shared_ptr<SolidGroundTile> position, Map* map);
	~GroundTower();
	void PrintDebug();
};

#endif
