#ifndef _PROJECTILE_
#define _PROJECTILE_

#include <memory>

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
	std::shared_ptr<PathTile> _target;

	virtual uint _OnImpact() = 0;
public:
	Projectile(Tower* origin, std::shared_ptr<PathTile> target, uint speed, uint hitpoints);
	virtual ~Projectile();
	void Step(); 
	void PrintDebug();
	bool Impacted();
	
};

#endif
