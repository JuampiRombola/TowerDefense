#ifndef _PROJECTILE_
#define _PROJECTILE_

#include <memory>

#include "Map/PathTile.h"
#include "Map/SolidGroundTile.h"

class Projectile {
private:
	uint _speed;
	bool _impacted;
 	uint _distance;
 	uint _distanceCovered;
protected:
 	uint _hitPoints;
	std::shared_ptr<PathTile> _target;
	virtual void _OnImpact() = 0;
public:
	Projectile(std::shared_ptr<SolidGroundTile> origin, 
		std::shared_ptr<PathTile> target, uint speed, uint hitpoints);
	virtual ~Projectile();
	void Step(); 
	void PrintDebug();
	bool Impacted();
	
};

#endif
