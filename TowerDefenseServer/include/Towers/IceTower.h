#ifndef _ICE_TOWER_
#define _ICE_TOWER_



#include "Tower.h"

class SolidGroundTile;
class Map;
class Projectile;

class IceTower : public Tower {
protected:
	Projectile* _BuildProjectile(PathTile* target);
public:
	IceTower(uint cooldown_sec, uint range, uint damage, SolidGroundTile* position, Map* map);
	~IceTower();
	void PrintDebug();
};

#endif
