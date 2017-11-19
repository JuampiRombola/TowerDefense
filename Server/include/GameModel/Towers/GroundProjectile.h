#ifndef _GROUND_PROJECTILE_
#define _GROUND_PROJECTILE_

#include "../Towers/Projectile.h"

class PathTile;
class GroundTower;
class ProjectileVM;

class GroundProjectile : public Projectile {
protected:
	double _OnImpact();
public:
	GroundProjectile(GroundTower* tower, PathTile* target, uint hitpoints, uint speed_ms);
	~GroundProjectile();
	ProjectileVM GetViewModel();
};

#endif
