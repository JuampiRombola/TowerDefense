#include <iostream>
#include <cmath>

#include "../../../include/GameModel/ViewModels/TowerVM.h"
#include "../../../include/GameModel/Commands/BuildTowerCommand.h"
#include <yaml-cpp/yaml.h>
#include "../../../include/GameModel/Towers/Tower.h"
#include "../../../include/GameModel/Towers/Projectile.h"
#include "../../../include/GameModel/Towers/WaterTower.h"
#include "../../../include/GameModel/Map/SolidGroundTile.h"
#include "../../../include/GameModel/Towers/WaterProjectile.h"
#include "../../../include/GameModel/Commands/UpgradeTowerCommand.h"


WaterTower::WaterTower(uint cooldown_sec, uint range, uint damage,
					   uint slowPercent, uint slowDuration_sec, SolidGroundTile* position, Map* map,
						uint projectile_ms_over_tile)
: Tower(cooldown_sec, range, damage, position, map, projectile_ms_over_tile), _slowPercent(slowPercent), _slowDuration_sec(slowDuration_sec) {}

WaterTower::~WaterTower(){}



void WaterTower::PrintDebug(){

}

Projectile* WaterTower::_BuildProjectile(PathTile* target){
	return new WaterProjectile(this, target, _damage, _slowDuration_sec, _slowPercent, _projectile_ms_over_tile);
}

bool WaterTower::Upgrade(const YAML::Node& cfg, UpgradeType type){
	switch (type){
		case Range:
			{
				uint rangeIncrease = cfg["towers"]["water"]["upgrade_range_increase"].as<uint>();
				uint mult = cfg["towers"]["water"]["upgrade_range_mult"].as<uint>();
				double base = cfg["towers"]["water"]["upgrade_range_base"].as<double>();
				double expRequired = pow(base, _upgradeLevel);
				expRequired *= mult;
				if (_experience >= expRequired){
					_experience -= expRequired;
					_range += rangeIncrease;
					_upgradeLevel++;
					std::cout << "watertower range Upgraded\n" << std::flush;
					return true;
				}
				std::cout << "watertower needs more xp to Upgrade range\n" << std::flush;
			}
		break;
		case Damage:
			{
				uint damageIncrease = cfg["towers"]["water"]["upgrade_damage_increase"].as<uint>();
				uint mult = cfg["towers"]["water"]["upgrade_damage_mult"].as<uint>();
				double base = cfg["towers"]["water"]["upgrade_damage_base"].as<double>();
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
			{
				if (_slowPercent >= 100)
					return false;
				uint slowPercentIncrease = cfg["towers"]["water"]["upgrade_slow_percent_increase"].as<uint>();
				uint slowDurationIncrease_sec = cfg["towers"]["water"]["upgrade_slow_duration_sec_increase"].as<uint>();
				uint mult = cfg["towers"]["water"]["upgrade_slow_mult"].as<uint>();
				double base = cfg["towers"]["water"]["upgrade_slow_base"].as<double>();
				double expRequired = pow(base, _upgradeLevel);
				expRequired *= mult;
				if (_experience > expRequired){
					_experience -= expRequired;
					_slowPercent += slowPercentIncrease;
					_slowDuration_sec += slowDurationIncrease_sec;
					_upgradeLevel++;
					return true;
				}		
			}
	}

	return false;
}

TowerVM WaterTower::GetViewModel(){
	TowerVM vm;
	vm.type = Water;
	vm.xPos = _position->GetXPos();
	vm.yPos = _position->GetYPos();
	vm.experience = _experience;
	vm.level = _upgradeLevel;
	return vm;
}

