#ifndef _ICE_PROJECTILE_
#define _ICE_PROJECTILE_

#include <memory>

#include "Towers/Projectile.h"

class PathTile;
class SolidGroundTile;

class IceProjectile : public Projectile {
public:
	IceProjectile(std::shared_ptr<SolidGroundTile> origin, std::shared_ptr<PathTile> target, uint hitpoints);
	~IceProjectile();
	void _OnImpact();
};

#endif
