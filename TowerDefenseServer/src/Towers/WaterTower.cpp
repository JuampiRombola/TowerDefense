#include <iostream>


#include "yaml-cpp/yaml.h"
#include "Towers/Tower.h"
#include "Towers/Projectile.h"
#include "Towers/WaterTower.h"
#include "Map/SolidGroundTile.h"
#include "Towers/WaterProjectile.h"
#include "Commands/UpgradeTowerCommand.h"


WaterTower::WaterTower(uint cooldown_sec, uint range, uint damage, SolidGroundTile* position, Map* map)
: Tower(cooldown_sec, range, damage, position, map) {}

WaterTower::~WaterTower(){}



void WaterTower::PrintDebug(){

}

Projectile* WaterTower::_BuildProjectile(PathTile* target){
	return new WaterProjectile(this, target, 10);
}

bool WaterTower::Upgrade(const YAML::Node& cfg, UpgradeType type){
	return false;
}