#include <iostream>

#include "../../include/Towers/GroundTower.h"
#include "../../include/Towers/WaterTower.h"
#include "../../include/Towers/AirTower.h"
#include "../../include/Towers/FireTower.h"
#include "../../include/Map/SolidGroundTile.h"
#include "../../include/Commands/BuildTowerCommand.h"
#include "../../include/Towers/Tower.h"
#include "../../include/TowerDefenseGame.h"
#include <yaml-cpp/yaml.h>
#include "../../include/ViewModels/CommandVM.h"


BuildTowerCommand::BuildTowerCommand(TowerType type, uint x, uint y):
 _xPos(x), _yPos(y), _towerType(type) {}

BuildTowerCommand::~BuildTowerCommand(){}

bool BuildTowerCommand::Execute(Map* map, TowerDefenseGame* game){
	SolidGroundTile* tile = map->GetSolidGroundTile(_xPos ,_yPos);
	if (tile != nullptr && !tile->HasTower()){
		Tower* t = nullptr;

		switch(_towerType){
			case Ground:
				t = _BuildGroundTower(map, tile, game->GameCfg.Cfg, game->notifications);
				break;
			case Air:
				t = _BuildAirTower(map, tile, game->GameCfg.Cfg, game->notifications);
				break;
			case Water:
				t = _BuildWaterTower(map, tile, game->GameCfg.Cfg, game->notifications);
				break;
			case Fire:
				t = _BuildFireTower(map, tile, game->GameCfg.Cfg, game->notifications);
				break;
		}

		if (t != nullptr){
			tile->PlaceTower(t);
			std::cout << "TOWER PLACED\n" << std::flush;
			return true;
		}
	}
	return false;
}

Tower* BuildTowerCommand::_BuildGroundTower(Map* map, SolidGroundTile* tile,
											const YAML::Node& cfg,
											ThreadSafeQueue<GameNotification
											*>& notifications){
	uint cooldown_sec = cfg["towers"]["ground"]["cooldown_sec"].as<uint>();
	uint range = cfg["towers"]["ground"]["range"].as<uint>();
	uint damage = cfg["towers"]["ground"]["damage"].as<uint>();
	return new GroundTower(cooldown_sec * 1000, range, damage, tile, map, notifications);
}

Tower* BuildTowerCommand::_BuildFireTower(Map* map, SolidGroundTile* tile, const YAML::Node& cfg, ThreadSafeQueue<GameNotification*>& notifications){
	uint damage = cfg["towers"]["fire"]["damage"].as<uint>();
	uint cooldown_sec = cfg["towers"]["fire"]["cooldown_sec"].as<uint>();
	uint range = cfg["towers"]["fire"]["range"].as<uint>();
	uint collateralRange = cfg["towers"]["fire"]["collateral_range"].as<uint>();
	uint collateralDamage = cfg["towers"]["fire"]["collateral_damage"].as<uint>();
	return new FireTower(cooldown_sec * 1000, range, damage, tile, map,
						 collateralDamage, collateralRange, notifications);
}

Tower* BuildTowerCommand::_BuildWaterTower(Map* map, SolidGroundTile* tile, const YAML::Node& cfg, ThreadSafeQueue<GameNotification*>& notifications){
	uint cooldown_sec = cfg["towers"]["water"]["cooldown_sec"].as<uint>();
	uint range = cfg["towers"]["water"]["range"].as<uint>();
	uint damage = cfg["towers"]["water"]["damage"].as<uint>();
	uint slowPercent = cfg["towers"]["water"]["slow_percent"].as<uint>();
	uint slowDuration_sec = cfg["towers"]["water"]["slow_duration_sec"].as<uint>();
	return new WaterTower(cooldown_sec * 1000, range, damage, slowPercent,
						  slowDuration_sec, tile, map, notifications);
}

Tower* BuildTowerCommand::_BuildAirTower(Map* map, SolidGroundTile* tile, const YAML::Node& cfg, ThreadSafeQueue<GameNotification*>& notifications){
	uint cooldown_sec = cfg["towers"]["air"]["cooldown_sec"].as<uint>();
	uint range = cfg["towers"]["air"]["range"].as<uint>();
	uint flyingTargetDamage = cfg["towers"]["air"]["flying_target_damage"].as<uint>();
	uint nonFlyingTargetDamage = cfg["towers"]["air"]["non_flying_target_damage"].as<uint>();
	return new AirTower(cooldown_sec * 1000, range, flyingTargetDamage,
						nonFlyingTargetDamage, tile, map, notifications);
}

CommandVM BuildTowerCommand::GetViewModel(){
	CommandVM vm;
	vm.type = BuildTower;
	vm.towerType = _towerType;
	vm.xPos = _xPos;
	vm.yPos = _yPos;
	return vm;
}