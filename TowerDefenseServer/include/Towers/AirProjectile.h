#ifndef _AIR_PROJECTILE_
#define _AIR_PROJECTILE_



#include "Towers/Projectile.h"

class PathTile;
class AirTower;

class AirProjectile : public Projectile {
private:
	uint _nonFlyingHitPoints;
protected:
	double _OnImpact();
public:
	AirProjectile(AirTower* origin, PathTile* target, uint flyinghitpoints, uint nonflyingHitpoints);
	~AirProjectile();
	ProjectileVM GetViewModel();
};

#endif
