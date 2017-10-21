#include <iostream>

#include "Tower.h"
#include "Projectile.h"
#include "GroundTower.h"

GroundTower::GroundTower(unsigned int cooldown_sec, Map* map)
: Tower(cooldown_sec, map) {}

GroundTower::~GroundTower(){}

GroundProjectile* GroundTower::Step(){
	if (_CanFire())
		return _Fire();
	return NULL;
}

GroundProjectile* GroundTower::_Fire(){
	return NULL;
}

void GroundTower::PrintDebug(){

}