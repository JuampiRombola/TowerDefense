#ifndef _WIND_TOWER_
#define _WIND_TOWER_

#include <memory>

#include "Tower.h"

class SolidGroundTile;
class Map;
class Projectile;

class WindTower : public Tower {
protected:
	std::shared_ptr<Projectile> _BuildProjectile(std::shared_ptr<PathTile> target);
public:
	WindTower(uint cooldown_sec, uint range, uint damage, std::shared_ptr<SolidGroundTile> position, Map* map);
	~WindTower();
	void PrintDebug();
};

#endif
