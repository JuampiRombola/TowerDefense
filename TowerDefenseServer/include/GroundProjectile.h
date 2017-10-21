#ifndef _GROUND_PROJECTILE_
#define _GROUND_PROJECTILE_

#include "Tower.h"
#include "Projectile.h"
#include "PathTile.h"

class GroundProjectile : public Projectile {
public:
	GroundProjectile(PathTile* target);
	~GroundProjectile();
};

#endif
