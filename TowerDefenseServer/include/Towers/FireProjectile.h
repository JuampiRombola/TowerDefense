#ifndef _FIRE_PROJECTILE_
#define _FIRE_PROJECTILE_

#include <memory>

#include "Towers/Projectile.h"

class PathTile;
class SolidGroundTile;

class FireProjectile : public Projectile {
public:
	FireProjectile(std::shared_ptr<SolidGroundTile> origin, std::shared_ptr<PathTile> target, uint hitpoints);
	~FireProjectile();
	void _OnImpact();
};

#endif
