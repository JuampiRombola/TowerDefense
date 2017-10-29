#ifndef _WATER_PROJECTILE_
#define _WATER_PROJECTILE_



#include "Towers/Projectile.h"

class PathTile;
class WaterTower;
class ProjectileVM;

class WaterProjectile : public Projectile {
protected:
	uint _OnImpact();
public:
	WaterProjectile(WaterTower* origin, PathTile* target, uint hitpoints);
	~WaterProjectile();
	ProjectileVM GetViewModel();
};

#endif
