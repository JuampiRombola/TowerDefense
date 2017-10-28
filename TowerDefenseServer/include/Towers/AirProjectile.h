#ifndef _AIR_PROJECTILE_
#define _AIR_PROJECTILE_



#include "Towers/Projectile.h"

class PathTile;
class AirTower;

class AirProjectile : public Projectile {
	uint _nonFlyingHitPoints;
public:
	AirProjectile(AirTower* origin, PathTile* target, uint flyinghitpoints, uint nonflyingHitpoints);
	~AirProjectile();
	uint _OnImpact();
};

#endif
