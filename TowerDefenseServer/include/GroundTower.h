#ifndef _GROUND_TOWER_
#define _GROUND_TOWER_

#include "Tower.h"
#include "GroundProjectile.h"
#include "Map.h"

class GroundTower : public Tower {
private:
	GroundProjectile* _Fire();
public:
	GroundTower(unsigned int cooldown_sec, Map* map);
	~GroundTower();
	GroundProjectile* Step();
	void PrintDebug();
};

#endif
