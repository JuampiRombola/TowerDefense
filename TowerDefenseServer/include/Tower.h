#ifndef _TOWER_
#define _TOWER_

#include "Projectile.h"
#include "Map.h"

class Tower {
protected:
	unsigned long long _lastTimeStamp_ms;
	unsigned int _cooldown_sec;

	Map* _map;

	virtual Projectile* _Fire() = 0; 
	bool _CanFire(); 
public:
	Tower(unsigned int cooldown, Map* map);
	virtual ~Tower();
	virtual Projectile* Step() = 0; 
	virtual void PrintDebug() = 0;
};

#endif
