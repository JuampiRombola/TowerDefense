#ifndef _GROUND_PROJECTILE_
#define _GROUND_PROJECTILE_

#include <memory>

#include "Tower.h"
#include "Projectile.h"
#include "PathTile.h"
#include "SolidGroundTile.h"

class GroundProjectile : public Projectile {
public:
	GroundProjectile(std::shared_ptr<SolidGroundTile> origin, std::shared_ptr<PathTile> target, uint hitpoints);
	~GroundProjectile();
	void _OnImpact();
};

#endif
