#ifndef _WATER_PROJECTILE_
#define _WATER_PROJECTILE_



#include "../Towers/Projectile.h"

class PathTile;
class WaterTower;
class ProjectileVM;

class WaterProjectile : public Projectile {
private:
	uint _slowDuration_sec;
	uint _slowPercent;
protected:
	double _OnImpact();
public:
	WaterProjectile(WaterTower* origin, PathTile* target,
					uint hitpoints, uint slowDuration_sec, uint slowPercent, uint speed_ms);
	~WaterProjectile();
	ProjectileVM GetViewModel();
};

#endif
