#ifndef _GROUND_TOWER_
#define _GROUND_TOWER_

#include "Tower.h"
#include "SolidGroundTile.h"
#include "GroundProjectile.h"
#include "Map.h"

class GroundTower : public Tower {
protected:
	Projectile* _BuildProjectile(PathTile* target);
public:
	GroundTower(uint cooldown_sec, uint range, SolidGroundTile* position, Map* map);
	~GroundTower();
	void PrintDebug();
};

#endif
