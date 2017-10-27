#ifndef _PROJECTILE_
#define _PROJECTILE_



#include "Map/PathTile.h"

class Tower;


class Projectile {
private:
	uint _speed;
	bool _impacted;
 	uint _distance;
 	uint _distanceCovered;
protected:
	Tower* _origin;
 	uint _hitPoints;
	PathTile* _target;

	virtual uint _OnImpact() = 0;
public:
	Projectile(Tower* origin, PathTile* target, uint speed, uint hitpoints);
	virtual ~Projectile();
	void Step(); 
	void PrintDebug();
	bool Impacted();
	
};

#endif
