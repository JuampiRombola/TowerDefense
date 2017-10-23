#ifndef _GROUND_PROJECTILE_
#define _GROUND_PROJECTILE_

#include <memory>

#include "Towers/Projectile.h"

class PathTile;
class SolidGroundTile;

class GroundProjectile : public Projectile {
public:
	GroundProjectile(std::shared_ptr<SolidGroundTile> origin, std::shared_ptr<PathTile> target, uint hitpoints);
	~GroundProjectile();
	void _OnImpact();
};

#endif
