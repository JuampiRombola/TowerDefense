#ifndef _GROUND_PROJECTILE_
#define _GROUND_PROJECTILE_

#include "Tower.h"
#include "Projectile.h"
#include "PathTile.h"
#include "SolidGroundTile.h"

class GroundProjectile : public Projectile {
public:
	GroundProjectile(SolidGroundTile* origin, PathTile* target);
	~GroundProjectile();
};

#endif
