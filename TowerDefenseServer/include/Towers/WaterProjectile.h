#ifndef _WATER_PROJECTILE_
#define _WATER_PROJECTILE_



#include "Towers/Projectile.h"

class PathTile;
class WaterTower;

class WaterProjectile : public Projectile {
public:
	WaterProjectile(WaterTower* origin, PathTile* target, uint hitpoints);
	~WaterProjectile();
	uint _OnImpact();
};

#endif
