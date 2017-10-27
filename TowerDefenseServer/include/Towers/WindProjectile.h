#ifndef _WIND_PROJECTILE_
#define _WIND_PROJECTILE_



#include "Towers/Projectile.h"

class PathTile;
class WindTower;

class WindProjectile : public Projectile {
public:
	WindProjectile(WindTower* origin, PathTile* target, uint hitpoints);
	~WindProjectile();
	uint _OnImpact();
};

#endif
