#include <iostream>
#include <cmath>

#include "../../include/Towers/Tower.h"
#include "../../include/Towers/Projectile.h"
#include "../../include/Towers/GroundTower.h"
#include "../../include/Map/SolidGroundTile.h"
#include "../../include/Towers/GroundProjectile.h"
#include <yaml-cpp/yaml.h>
#include "../../include/Commands/UpgradeTowerCommand.h"
#include "../../include/Commands/BuildTowerCommand.h"
#include "../../include/ViewModels/TowerVM.h"


GroundTower::GroundTower(uint cooldown_sec, uint range, uint damage,
						 SolidGroundTile* position, Map* map,
						 ThreadSafeQueue<GameNotification*>& notis)
: Tower(cooldown_sec, range, damage, position, map, notis) {}

GroundTower::~GroundTower(){}



void GroundTower::PrintDebug(){

}

Projectile* GroundTower::_BuildProjectile(PathTile* target){
	return new GroundProjectile(this, target, 10);
}

bool GroundTower::Upgrade(const YAML::Node& cfg, UpgradeType type){
	switch (type){
		case Range:
			{
				uint rangeIncrease = cfg["towers"]["ground"]["upgrade_range_increase"].as<uint>();
				uint mult = cfg["towers"]["ground"]["upgrade_range_mult"].as<uint>();
				double base = cfg["towers"]["ground"]["upgrade_range_base"].as<double>();
				double expRequired = pow(base, _upgradeLevel);
				expRequired *= mult;
				if (_experience >= expRequired){
					_experience -= expRequired;
					_range += rangeIncrease;
					_upgradeLevel++;
					std::cout << "groundtower range Upgraded\n" << std::flush;
					return true;
				}
				std::cout << "groundtower needs more xp to Upgrade range\n" << std::flush;
			}
		break;
		case Damage:
			{
				uint damageIncrease = cfg["towers"]["ground"]["upgrade_damage_increase"].as<uint>();
				uint mult = cfg["towers"]["ground"]["upgrade_damage_mult"].as<uint>();
				double base = cfg["towers"]["ground"]["upgrade_damage_base"].as<double>();
				double expRequired = pow(base, _upgradeLevel);
				expRequired *= mult;
				if (_experience > expRequired){
					_experience -= expRequired;
					_damage += damageIncrease;
					_upgradeLevel++;
					return true;
				}		
			}
			break;
		case CollateralRange:
			return false;
		case Slow:
			return false; 
	}
	return false;
}

TowerVM GroundTower::GetViewModel(){
	TowerVM vm;
	vm.type = Ground;
	vm.xPos = _position->GetXPos();
	vm.yPos = _position->GetYPos();
	vm.experience = _experience;
	vm.level = _upgradeLevel;
	return vm;
}