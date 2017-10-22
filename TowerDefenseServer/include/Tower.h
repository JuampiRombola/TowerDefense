#ifndef _TOWER_
#define _TOWER_

#include "Projectile.h"
#include "SolidGroundTile.h"
#include "Map.h"
#include "PathTile.h"

class Tower {
protected:
	unsigned long long _lastTimeStamp_ms;
	uint _cooldown_sec;
	Map* _map;
	SolidGroundTile* _position;
	uint _range;

	Projectile* _Fire(); 
	bool _CanFire(); 

	virtual Projectile* _BuildProjectile(PathTile* target) = 0;
public:
	Tower(uint cooldown, uint range, SolidGroundTile* position, Map* map);
	virtual ~Tower();
	Projectile* Step(); 
	virtual void PrintDebug() = 0;
};

#endif
