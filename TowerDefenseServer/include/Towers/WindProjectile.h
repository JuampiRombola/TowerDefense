#ifndef _WIND_PROJECTILE_
#define _WIND_PROJECTILE_

#include <memory>

#include "Towers/Projectile.h"

class PathTile;
class WindTower;

class WindProjectile : public Projectile {
public:
	WindProjectile(WindTower* origin, std::shared_ptr<PathTile> target, uint hitpoints);
	~WindProjectile();
	uint _OnImpact();
};

#endif
