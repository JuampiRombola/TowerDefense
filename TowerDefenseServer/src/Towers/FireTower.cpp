#include <iostream>

#include "Towers/Tower.h"
#include "Towers/Projectile.h"
#include "Towers/FireTower.h"
#include "Map/SolidGroundTile.h"
#include "Towers/FireProjectile.h"
#include "yaml-cpp/yaml.h"
#include "Commands/UpgradeTowerCommand.h"

FireTower::FireTower(uint cooldown_ms, uint range, uint damage, 
	SolidGroundTile* position, Map* map, uint collateralDamage, uint collateralRange)
: Tower(cooldown_ms, range, damage, position, map), _collateralDamage(collateralDamage), _collateralRange(collateralRange) {}

FireTower::~FireTower(){}



void FireTower::PrintDebug(){

}

Projectile* FireTower::_BuildProjectile(PathTile* target){
	return new FireProjectile(this, target, _damage, _collateralRange, _collateralDamage);
}

bool FireTower::Upgrade(const YAML::Node& cfg, UpgradeType type){
	return false;
}