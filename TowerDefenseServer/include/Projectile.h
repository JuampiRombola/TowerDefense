#ifndef _PROJECTILE_
#define _PROJECTILE_

#include "PathTile.h"

class Projectile {
private:
	PathTile* _target;
	uint _speed;
	bool _impacted;
 
public:
	Projectile(PathTile* target, uint speed);
	virtual ~Projectile();
	void Step(); 
	void PrintDebug();
	bool Impacted();
};

#endif
