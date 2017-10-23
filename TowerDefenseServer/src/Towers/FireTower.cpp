#include <iostream>

#include <memory>

#include "Towers/Tower.h"
#include "Towers/Projectile.h"
#include "Towers/FireTower.h"
#include "Map/SolidGroundTile.h"
#include "Towers/FireProjectile.h"

FireTower::FireTower(uint cooldown_sec, uint range, std::shared_ptr<SolidGroundTile> position, Map* map)
: Tower(cooldown_sec, range, position, map) {}

FireTower::~FireTower(){}



void FireTower::PrintDebug(){

}

std::shared_ptr<Projectile> FireTower::_BuildProjectile(std::shared_ptr<PathTile> target){
	return std::shared_ptr<Projectile>(new FireProjectile(_position, target, 10));
}
