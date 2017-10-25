#ifndef _ICE_PROJECTILE_
#define _ICE_PROJECTILE_

#include <memory>

#include "Towers/Projectile.h"

class PathTile;
class IceTower;

class IceProjectile : public Projectile {
public:
	IceProjectile(IceTower* origin, std::shared_ptr<PathTile> target, uint hitpoints);
	~IceProjectile();
	uint _OnImpact();
};

#endif
