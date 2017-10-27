#ifndef _FIRE_PROJECTILE_
#define _FIRE_PROJECTILE_

#include "Towers/Projectile.h"

class PathTile;
class FireTower;

class FireProjectile : public Projectile {
private:
	uint _collateralRange;
	uint _collateralDamage;
public:
	FireProjectile(FireTower* origin, PathTile* target, 
		uint hitpoints, uint collateralRange, uint collateralDamage);
	~FireProjectile();
	uint _OnImpact();
};

#endif
