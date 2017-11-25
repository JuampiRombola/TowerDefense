#include <iostream>
#include <cmath>

#include "../../../include/GameModel/Towers/Tower.h"
#include "../../../include/GameModel/Towers/Projectile.h"
#include "../../../include/GameModel/Towers/GroundTower.h"
#include "../../../include/GameModel/Map/SolidGroundTile.h"
#include "../../../include/GameModel/Towers/GroundProjectile.h"
#include <yaml-cpp/yaml.h>
#include "../../../include/GameModel/Commands/UpgradeTowerCommand.h"
#include "../../../include/GameModel/Commands/BuildTowerCommand.h"
#include "../../../include/GameModel/ViewModels/TowerVM.h"


GroundTower::GroundTower(uint cooldown_sec, uint range,
						 uint damage, SolidGroundTile* position, Map* map,
						uint projectile_ms_over_tile, ThreadSafeQueue<GameNotification*>& notifications)
: Tower(cooldown_sec, range, damage, position, map, projectile_ms_over_tile, notifications) {}

GroundTower::~GroundTower(){}



void GroundTower::PrintDebug(){

}

Projectile* GroundTower::_BuildProjectile(PathTile* target){
	return new GroundProjectile(this, target, _damage, _projectile_ms_over_tile);
}

bool GroundTower::Upgrade(UpgradeType type){
	switch (type){
		case Range:
			{
				uint rangeIncrease = (*cfg)["towers"]["ground"]["upgrade_range_increase"].as<uint>();
				uint mult = (*cfg)["towers"]["ground"]["upgrade_range_mult"].as<uint>();
				double base = (*cfg)["towers"]["ground"]["upgrade_range_base"].as<double>();
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
				uint damageIncrease = (*cfg)["towers"]["ground"]["upgrade_damage_increase"].as<uint>();
				uint mult = (*cfg)["towers"]["ground"]["upgrade_damage_mult"].as<uint>();
				double base = (*cfg)["towers"]["ground"]["upgrade_damage_base"].as<double>();
				double expRequired = pow(base, _upgradeLevel);
				expRequired *= mult;
				if (_experience > expRequired){
					_experience -= expRequired;
					_damage += damageIncrease;
					_upgradeLevel++;
					std::cout << "groundtower Damage Upgraded\n" << std::flush;
					return true;
				}
				std::cout << "groundtower needs more xp to Upgrade Damage\n" << std::flush;

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
	vm.experience = floor(_experience);
	vm.level = _upgradeLevel;
	vm.collateral_range = -1;
	vm.collateral_damage = -1;
	vm.nonFlyingDamage = -1;
	vm.range = _range;
	vm.projectile_ms_over_tile = _projectile_ms_over_tile;
	vm.slow_percent = -1;
	vm.slow_seconds = -1;
	vm.damage = _damage;
	uint damagemult = (*cfg)["towers"]["ground"]["upgrade_damage_mult"].as<uint>();
	uint rangemult = (*cfg)["towers"]["ground"]["upgrade_range_mult"].as<uint>();

	double damagebase = (*cfg)["towers"]["ground"]["upgrade_damage_base"].as<double>();
	double rangebase = (*cfg)["towers"]["ground"]["upgrade_range_base"].as<double>();
	vm.exp_required_for_damage_upgrade = floor(pow(damagebase, _upgradeLevel) * damagemult);
	vm.exp_required_for_range_upgrade = floor(pow(rangebase, _upgradeLevel) * rangemult);
	vm.exp_required_for_collateral_range_upgrade = 0xFFFFFFFF;
	vm.exp_required_for_slow_upgrade = 0xFFFFFFFF;
	return vm;
}