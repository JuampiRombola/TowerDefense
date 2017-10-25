#ifndef _FIRE_PROJECTILE_
#define _FIRE_PROJECTILE_

#include <memory>

#include "Towers/Projectile.h"

class PathTile;
class FireTower;

class FireProjectile : public Projectile {
public:
	FireProjectile(FireTower* origin, std::shared_ptr<PathTile> target, uint hitpoints);
	~FireProjectile();
	uint _OnImpact();
};

#endif
