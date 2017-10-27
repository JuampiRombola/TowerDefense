#include <iostream>



#include "Towers/Tower.h"
#include "Towers/Projectile.h"
#include "Towers/WindTower.h"
#include "Map/SolidGroundTile.h"
#include "Towers/WindProjectile.h"

WindTower::WindTower(uint cooldown_sec, uint range, uint damage, SolidGroundTile* position, Map* map)
: Tower(cooldown_sec, range, damage, position, map) {}

WindTower::~WindTower(){}



void WindTower::PrintDebug(){

}

Projectile* WindTower::_BuildProjectile(PathTile* target){
	return new WindProjectile(this, target, _damage);
}
