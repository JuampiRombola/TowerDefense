#ifndef _GROUND_PROJECTILE_
#define _GROUND_PROJECTILE_

#include <memory>

#include "Towers/Projectile.h"

class PathTile;
class GroundTower;

class GroundProjectile : public Projectile {
public:
	GroundProjectile(GroundTower* tower, std::shared_ptr<PathTile> target, uint hitpoints);
	~GroundProjectile();
	uint _OnImpact();
};

#endif
