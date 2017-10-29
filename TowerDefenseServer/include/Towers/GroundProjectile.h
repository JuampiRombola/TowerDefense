#ifndef _GROUND_PROJECTILE_
#define _GROUND_PROJECTILE_

#include "Towers/Projectile.h"

class PathTile;
class GroundTower;
class ProjectileVM;

class GroundProjectile : public Projectile {
protected:
	uint _OnImpact();
public:
	GroundProjectile(GroundTower* tower, PathTile* target, uint hitpoints);
	~GroundProjectile();
	ProjectileVM GetViewModel();
};

#endif
