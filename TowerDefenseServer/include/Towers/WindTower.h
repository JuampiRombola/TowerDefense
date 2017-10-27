#ifndef _WIND_TOWER_
#define _WIND_TOWER_



#include "Tower.h"

class SolidGroundTile;
class Map;
class Projectile;

class WindTower : public Tower {
protected:
	Projectile* _BuildProjectile(PathTile* target);
public:
	WindTower(uint cooldown_sec, uint range, uint damage, SolidGroundTile* position, Map* map);
	~WindTower();
	void PrintDebug();
};

#endif
