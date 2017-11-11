#ifndef _PROJECTILE_
#define _PROJECTILE_



#include "../Map/PathTile.h"

struct ProjectileVM;
class Tower;


class Projectile {
protected:
	uint _speed;
	bool _impacted;
 	uint _distance;
 	uint _distanceCovered;
	Tower* _origin;
 	uint _hitPoints;
	PathTile* _target;

	virtual double _OnImpact() = 0;
public:
	Projectile(Tower* origin, PathTile* target, uint speed, uint hitpoints);
	virtual ~Projectile();
	void Step(); 
	void PrintDebug();
	bool Impacted();
	virtual ProjectileVM GetViewModel() = 0;
	
};

#endif
