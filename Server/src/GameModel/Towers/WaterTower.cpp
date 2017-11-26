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
						uint projectile_ms_over_tile, ThreadSafeQueue<GameNotification*>& notifications)
: Tower(cooldown_sec, range, damage, position, map, projectile_ms_over_tile, notifications), _slowPercent(slowPercent), _slowDuration_sec(slowDuration_sec) {}

WaterTower::~WaterTower(){}



void WaterTower::PrintDebug(){

}

Projectile* WaterTower::_BuildProjectile(PathTile* target){
	return new WaterProjectile(this, target, _damage, _slowDuration_sec, _slowPercent, _projectile_ms_over_tile);
}

bool WaterTower::Upgrade(UpgradeType type){
	switch (type){
		case Range:
			{
				uint rangeIncrease = (*cfg)["towers"]["water"]["upgrade_range_increase"].as<uint>();
				uint mult = (*cfg)["towers"]["water"]["upgrade_range_mult"].as<uint>();
				double base = (*cfg)["towers"]["water"]["upgrade_range_base"].as<double>();
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
				uint damageIncrease = (*cfg)["towers"]["water"]["upgrade_damage_increase"].as<uint>();
				uint mult = (*cfg)["towers"]["water"]["upgrade_damage_mult"].as<uint>();
				double base = (*cfg)["towers"]["water"]["upgrade_damage_base"].as<double>();
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
				uint slowPercentIncrease = (*cfg)["towers"]["water"]["upgrade_slow_percent_increase"].as<uint>();
				uint slowDurationIncrease_sec = (*cfg)["towers"]["water"]["upgrade_slow_duration_sec_increase"].as<uint>();
				uint mult = (*cfg)["towers"]["water"]["upgrade_slow_mult"].as<uint>();
				double base = (*cfg)["towers"]["water"]["upgrade_slow_base"].as<double>();
				double expRequired = pow(base, _upgradeLevel);
				expRequired *= mult;
				if (_experience > expRequired){
					_experience -= expRequired;
					_slowPercent += slowPercentIncrease;
					if (_slowPercent > 100)
						_slowPercent = 100;
					_slowDuration_sec += slowDurationIncrease_sec;
					_upgradeLevel++;
					return true;
				}		
			}
	}

	return false;
}


TowerType WaterTower::GetTowerType(){
	return Water;
}

TowerVM WaterTower::GetViewModel(){
	TowerVM vm;
	vm.type = GetTowerType();
	vm.xPos = _position->GetXPos();
	vm.yPos = _position->GetYPos();
	vm.experience = _experience;
	vm.level = _upgradeLevel;
	vm.collateral_range = -1;
	vm.collateral_damage = -1;
	vm.nonFlyingDamage = -1;
	vm.range = _range;
	vm.projectile_ms_over_tile = _projectile_ms_over_tile;
	vm.slow_percent = _slowPercent;
	vm.slow_seconds = _slowDuration_sec;
	vm.damage = _damage;

	uint damagemult = (*cfg)["towers"]["water"]["upgrade_damage_mult"].as<uint>();
	uint rangemult = (*cfg)["towers"]["water"]["upgrade_range_mult"].as<uint>();
	uint slowmult = (*cfg)["towers"]["water"]["upgrade_slow_mult"].as<uint>();
	double slowbase = (*cfg)["towers"]["water"]["upgrade_slow_base"].as<double>();
	double damagebase = (*cfg)["towers"]["water"]["upgrade_damage_base"].as<double>();
	double rangebase = (*cfg)["towers"]["water"]["upgrade_range_base"].as<double>();
	vm.exp_required_for_damage_upgrade = floor(pow(damagebase, _upgradeLevel) * damagemult);
	vm.exp_required_for_slow_upgrade = floor(pow(slowbase, _upgradeLevel) * slowmult);
	vm.exp_required_for_range_upgrade = floor(pow(rangebase, _upgradeLevel) * rangemult);
	vm.exp_required_for_collateral_range_upgrade = 0xFFFFFFFF;

	return vm;
}

