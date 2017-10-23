#ifndef _WIND_PROJECTILE_
#define _WIND_PROJECTILE_

#include <memory>

#include "Towers/Projectile.h"

class PathTile;
class SolidGroundTile;

class WindProjectile : public Projectile {
public:
	WindProjectile(std::shared_ptr<SolidGroundTile> origin, std::shared_ptr<PathTile> target, uint hitpoints);
	~WindProjectile();
	void _OnImpact();
};

#endif
