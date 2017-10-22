#include <iostream>

#include "Tower.h"
#include "Projectile.h"
#include "GroundTower.h"
#include "SolidGroundTile.h"

GroundTower::GroundTower(uint cooldown_sec, uint range, SolidGroundTile* position, Map* map)
: Tower(cooldown_sec, range, position, map) {}

GroundTower::~GroundTower(){}



void GroundTower::PrintDebug(){

}

Projectile* GroundTower::_BuildProjectile(PathTile* target){
	return new GroundProjectile(_position, target);
}
