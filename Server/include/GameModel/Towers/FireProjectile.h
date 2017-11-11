#ifndef _FIRE_PROJECTILE_
#define _FIRE_PROJECTILE_

#include "../Towers/Projectile.h"

class PathTile;
class FireTower;
class ProjectileVM;

class FireProjectile : public Projectile {
private:
	uint _collateralRange;
	uint _collateralDamage;
protected:
	double _OnImpact();
public:
	FireProjectile(FireTower* origin, PathTile* target, 
		uint hitpoints, uint collateralRange, uint collateralDamage);
	~FireProjectile();
	ProjectileVM GetViewModel();
};

#endif
