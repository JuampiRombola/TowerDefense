#ifndef _ICE_PROJECTILE_
#define _ICE_PROJECTILE_



#include "Towers/Projectile.h"

class PathTile;
class IceTower;

class IceProjectile : public Projectile {
public:
	IceProjectile(IceTower* origin, PathTile* target, uint hitpoints);
	~IceProjectile();
	uint _OnImpact();
};

#endif
