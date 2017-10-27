#ifndef _GROUND_TOWER_
#define _GROUND_TOWER_



#include "Tower.h"

class SolidGroundTile;
class Map;
class Projectile;

class GroundTower : public Tower {
protected:
	Projectile* _BuildProjectile(PathTile* target);
public:
	GroundTower(uint cooldown_sec, uint range, uint damage, SolidGroundTile* position, Map* map);
	~GroundTower();
	void PrintDebug();
};

#endif
