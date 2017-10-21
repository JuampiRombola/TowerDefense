#ifndef _GROUND_TOWER_
#define _GROUND_TOWER_

#include "Tower.h"

class GroundTower : public Tower {
private:
	 void _Fire();
public:
	GroundTower(unsigned int cooldown_sec);
	~GroundTower();
	void Step();

};

#endif
