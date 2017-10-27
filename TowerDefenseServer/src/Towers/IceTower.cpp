#include <iostream>



#include "Towers/Tower.h"
#include "Towers/Projectile.h"
#include "Towers/IceTower.h"
#include "Map/SolidGroundTile.h"
#include "Towers/IceProjectile.h"

IceTower::IceTower(uint cooldown_sec, uint range, uint damage, SolidGroundTile* position, Map* map)
: Tower(cooldown_sec, range, damage, position, map) {}

IceTower::~IceTower(){}



void IceTower::PrintDebug(){

}

Projectile* IceTower::_BuildProjectile(PathTile* target){
	return new IceProjectile(this, target, 10);
}
