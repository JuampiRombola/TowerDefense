#include <iostream>



#include "Towers/Tower.h"
#include "Towers/Projectile.h"
#include "Towers/FireTower.h"
#include "Map/SolidGroundTile.h"
#include "Towers/FireProjectile.h"

FireTower::FireTower(uint cooldown_sec, uint range, uint damage, 
	SolidGroundTile* position, Map* map, uint collateralDamage, uint collateralRange)
: Tower(cooldown_sec, range, damage, position, map), _collateralDamage(collateralDamage), _collateralRange(collateralRange) {}

FireTower::~FireTower(){}



void FireTower::PrintDebug(){

}

Projectile* FireTower::_BuildProjectile(PathTile* target){
	return new FireProjectile(this, target, _damage, _collateralRange, _collateralDamage);
}
