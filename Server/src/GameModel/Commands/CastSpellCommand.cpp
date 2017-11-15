#include <ctime>
#include <iostream>

#include "../../../include/GameModel/Towers/GroundTower.h"
#include "../../../include/GameModel/Map/SolidGroundTile.h"
#include "../../../include/GameModel/Map/PathTile.h"
#include "../../../include/GameModel/Commands/CastSpellCommand.h"
#include "../../../include/GameModel/Towers/Tower.h"
#include "../../../include/GameModel/EnviormentUnits/EnviormentUnit.h"
#include "../../../include/GameModel/TowerDefenseGame.h"
#include "../../../include/GameModel/ViewModels/CommandVM.h"
#include "../../../include/GameModel/GameNotifications/SpellCastedGameNotification.h"

CastSpellCommand::CastSpellCommand(CAST_SPELL_TYPE spell, uint x, uint y):
 _xPos(x), _yPos(y), _unitId(-1), _spell(spell) {}

CastSpellCommand::CastSpellCommand(CAST_SPELL_TYPE spell, uint unitId):
 _xPos(-1), _yPos(-1), _unitId(unitId), _spell(spell) {}

CastSpellCommand::~CastSpellCommand(){}

bool CastSpellCommand::Execute(Map* map, TowerDefenseGame* game, ThreadSafeQueue<GameNotification*>& notifications){
	switch(_spell){
		case SPELL_TERRAFORMING: return _CastTerraforming(map, game);
		case SPELL_GRIETA: return _CastGrieta(map, game);
		case SPELL_METEORITO: return _CastMeteorito(map, game);
		case SPELL_FIREWALL: return _CastMuroDeFuego(map, game);
		case SPELL_CONGELACION: return _CastCongelacion(map, game);
		case SPELL_VENTISCA: return _CastVentisca(map, game);
		case SPELL_TORNADO: return _CastTornado(map, game);
		case SPELL_RAYO: return _CastRayos(map, game);
		default: return false;
	}
}

bool CastSpellCommand::_CastTerraforming(Map* map, TowerDefenseGame* game){
	SolidGroundTile* tile = map->GetSolidGroundTile(_xPos, _yPos);
	if (tile != nullptr)
		return false;
	map->PlaceGroundTile(new SolidGroundTile(_xPos,_yPos));
	game->notifications.Queue(new SpellCastedGameNotification(SPELL_TERRAFORMING, _xPos, _yPos,0,  game->GetPlayers() ));
	return true;
}

bool CastSpellCommand::_CastGrieta(Map* map, TowerDefenseGame* game){
	PathTile* tile = map->GetPathTile(_xPos, _yPos);
	if (tile != nullptr){
		uint32_t time_ms = game->GameCfg->Cfg["spells"]["grieta"]["duration_sec"].as<uint>();
		time_ms *= 1000;
		tile->Crack(time_ms);
		game->notifications.Queue(new SpellCastedGameNotification(SPELL_GRIETA, _xPos, _yPos, time_ms,  game->GetPlayers() ));
		return true;
	}
	return false;
}

bool CastSpellCommand::_CastMeteorito(Map* map, TowerDefenseGame* game){
	uint collateralDamageRange = game->GameCfg->Cfg["spells"]["meteorito"]["collateral_range"].as<uint>();
	uint collateralDamage = game->GameCfg->Cfg["spells"]["meteorito"]["collateral_damage"].as<uint>();
	uint targetDamage = game->GameCfg->Cfg["spells"]["meteorito"]["damage"].as<uint>();
	PathTile* tile = map->GetPathTile(_xPos, _yPos);
	if (tile != nullptr){
		std::vector<PathTile*> tiles = map->GetPathTilesInRange(tile, collateralDamageRange);
		std::vector<EnviormentUnit*> unitsInTargetTile = tile->GetUnits();
		for (auto it = unitsInTargetTile.begin(); it != unitsInTargetTile.end(); ++it){
			(*it)->GetHit(targetDamage);
		}

		for (auto it = tiles.begin(); it != tiles.end(); ++it){
			if (*it != tile){
				std::vector<EnviormentUnit*> units = (*it)->GetUnits();
				for (auto unitIt = units.begin(); unitIt != units.end(); ++unitIt){
					(*unitIt)->GetHit(collateralDamage);
				}
			}
		}
		game->notifications.Queue(new SpellCastedGameNotification(SPELL_METEORITO, _xPos, _yPos, 1500,  game->GetPlayers() ));
		return true;
	}
	return false;
}

bool CastSpellCommand::_CastMuroDeFuego(Map* map, TowerDefenseGame* game){
	uint fireDuration_sec = game->GameCfg->Cfg["spells"]["meteorito"]["damage"].as<uint>();
	uint fireDamage = game->GameCfg->Cfg["spells"]["meteorito"]["damage"].as<uint>();
	PathTile* tile = map->GetPathTile(_xPos, _yPos);
	if (tile != nullptr){
		tile->SetOnFire(fireDuration_sec * 1000, fireDamage);
		game->notifications.Queue(new SpellCastedGameNotification(SPELL_FIREWALL, _xPos, _yPos, fireDuration_sec * 1000,  game->GetPlayers() ));
		return true;
	}
	return false;
}

bool CastSpellCommand::_CastCongelacion(Map* map, TowerDefenseGame* game){
	uint freezeDurationSec = game->GameCfg->Cfg["spells"]["congelacion"]["duration_sec"].as<uint>();
	EnviormentUnit* unit = nullptr;
	PathTile* tile = map->GetPathTile(_xPos, _yPos);
	if (tile == nullptr)
		return false;

	std::vector<EnviormentUnit*> unitsInTile = tile->GetUnits();

	if (unitsInTile.size() == 0)
		return false;

	unit = *(unitsInTile.begin());

	if (unit != nullptr){
		unit->Freeze(freezeDurationSec);
		game->notifications.Queue(new SpellCastedGameNotification(SPELL_CONGELACION, _xPos, _yPos, freezeDurationSec * 1000,  game->GetPlayers() ));
		return true;
	}
	return false;
}

bool CastSpellCommand::_CastVentisca(Map* map, TowerDefenseGame* game){
	uint ventiscaDamage = game->GameCfg->Cfg["spells"]["ventisca"]["damage"].as<uint>();
	uint percentSlow = game->GameCfg->Cfg["spells"]["ventisca"]["slow_percent"].as<uint>();
	uint slowDuration_sec = game->GameCfg->Cfg["spells"]["ventisca"]["slow_duration_sec"].as<uint>();
	uint ventiscaDuration_sec = game->GameCfg->Cfg["spells"]["ventisca"]["duration_sec"].as<uint>();
	PathTile* tile = map->GetPathTile(_xPos, _yPos);
	if (tile != nullptr){
		tile->Ventisca(ventiscaDamage, ventiscaDuration_sec, slowDuration_sec, percentSlow);
		game->notifications.Queue(new SpellCastedGameNotification(SPELL_VENTISCA, _xPos, _yPos, ventiscaDuration_sec * 1000,  game->GetPlayers() ));
		return true;
	}
	return false;
}

bool CastSpellCommand::_CastTornado(Map* map, TowerDefenseGame* game){
	uint tornadoMaxDamage = game->GameCfg->Cfg["spells"]["tornado"]["max_damage"].as<uint>();;
	uint tornadoDuration_sec = game->GameCfg->Cfg["spells"]["tornado"]["duration_sec"].as<uint>();;
	PathTile* tile = map->GetPathTile(_xPos, _yPos);
	if (tile != nullptr){
		tile->Tornado(tornadoMaxDamage, tornadoDuration_sec);
		game->notifications.Queue(new SpellCastedGameNotification(SPELL_TORNADO, _xPos, _yPos, tornadoDuration_sec * 1000,  game->GetPlayers() ));
		return true;
	}
	return false;
}

bool CastSpellCommand::_CastRayos(Map* map, TowerDefenseGame* game){
	uint rayoMaxDamage = game->GameCfg->Cfg["spells"]["rayos"]["max_damage"].as<uint>();
	EnviormentUnit* unit = nullptr;
	PathTile* tile = map->GetPathTile(_xPos, _yPos);
	if (tile == nullptr)
		return false;

	std::vector<EnviormentUnit*> unitsInTile = tile->GetUnits();

	if (unitsInTile.size() == 0)
		return false;

	unit = *(unitsInTile.begin());
	if (unit != nullptr){
		std::srand(std::time(0));
		uint randomDamage = (uint) std::rand() % rayoMaxDamage;
		unit->GetHit(randomDamage);
		game->notifications.Queue(new SpellCastedGameNotification(SPELL_RAYO, _xPos, _yPos, 2000,  game->GetPlayers() ));
		return true;
	}
	return false;
}


/*
CommandVM CastSpellCommand::GetViewModel(){
	CommandVM vm;
	vm.type = CastSpell;
	vm.spellType = _spell;

	if (_unitId == -1){
		vm.xPos = _xPos;
		vm.yPos = _yPos;
	} else {
		vm.unitId = _unitId;
	}
	return vm;

}*/