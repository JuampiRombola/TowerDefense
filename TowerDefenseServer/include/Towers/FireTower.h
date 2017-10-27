#ifndef _FIRE_TOWER_
#define _FIRE_TOWER_



#include "Tower.h"

class SolidGroundTile;
class Map;
class Projectile;

class FireTower : public Tower {
protected:
	uint _collateralDamage;
	uint _collateralRange;
	Projectile* _BuildProjectile(PathTile* target);
public:
	FireTower(uint cooldown_sec, uint range, uint damage, 
		SolidGroundTile* position, Map* map, uint collateralDamange, uint collateralRange);
	~FireTower();
	void PrintDebug();
};

#endif
