#ifndef _PROJECTILE_
#define _PROJECTILE_



#include "../Map/PathTile.h"

struct ProjectileVM;
class Tower;


class Projectile {
protected:
	uint _ms_over_tile;
	bool _impacted;
 	uint _distance;
 	unsigned long long _lastTimeStamp_ms;
	Tower* _origin;
 	uint _hitPoints;
	PathTile* _target;

	virtual double _OnImpact() = 0;
public:
	Projectile(Tower* origin, PathTile* target, uint projectile_ms_over_tile, uint hitpoints);
	virtual ~Projectile();
	void Step(); 
	void PrintDebug();
	bool Impacted();
	virtual ProjectileVM GetViewModel() = 0;
	
};

#endif
