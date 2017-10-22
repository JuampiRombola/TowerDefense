#ifndef _PROJECTILE_
#define _PROJECTILE_

#include "PathTile.h"
#include "SolidGroundTile.h"

class Projectile {
private:
	PathTile* _target;
	uint _speed;
	bool _impacted;
 	uint _distance;
 	uint _distanceCovered;

public:
	Projectile(SolidGroundTile* origin, PathTile* target, uint speed);
	virtual ~Projectile();
	void Step(); 
	void PrintDebug();
	bool Impacted();
};

#endif
