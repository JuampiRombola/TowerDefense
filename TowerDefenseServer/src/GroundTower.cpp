#include <iostream>

#include "Tower.h"
#include "GroundTower.h"

GroundTower::GroundTower(unsigned int cooldown_sec)
: Tower(cooldown_sec) {}

GroundTower::~GroundTower(){}

void GroundTower::Step(){
	if (_CanFire())
		_Fire();

}

void GroundTower::_Fire(){

}

