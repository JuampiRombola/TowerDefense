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
	return true;
}

bool CastSpellCommand::_CastGrieta(Map* map, TowerDefenseGame* game){
	PathTile* tile = map->GetPathTile(_xPos, _yPos);
	if (tile != nullptr){
		tile->Crack(400);
		return true;
	}
	return false;
}

bool CastSpellCommand::_CastMeteorito(Map* map, TowerDefenseGame* game){
	uint collateralDamageRange = 2;
	uint collateralDamage = 10;
	uint targetDamage = 30;
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
	}
	return true;
}

bool CastSpellCommand::_CastMuroDeFuego(Map* map, TowerDefenseGame* game){
	uint fireDuration_sec = 5;
	uint fireDamage = 10;
	PathTile* tile = map->GetPathTile(_xPos, _yPos);
	if (tile != nullptr){
		tile->SetOnFire(fireDuration_sec, fireDamage);
		return true;
	}
	return false;
}

bool CastSpellCommand::_CastCongelacion(Map* map, TowerDefenseGame* game){
	uint freezeDurationSec = 5;
	EnviormentUnit* unit = game->GetUnit(_unitId);
	if (unit != nullptr){
		unit->Freeze(freezeDurationSec);
		return true;
	}
	return false;
}

bool CastSpellCommand::_CastVentisca(Map* map, TowerDefenseGame* game){
	uint ventiscaDamage = 5;
	uint percentSlow = 95;
	uint slowDuration_sec = 4;
	uint ventiscaDuration_sec = 5;
	PathTile* tile = map->GetPathTile(_xPos, _yPos);
	if (tile != nullptr){
		tile->Ventisca(ventiscaDamage, ventiscaDuration_sec, slowDuration_sec, percentSlow);
		return true;
	}
	return false;
}

bool CastSpellCommand::_CastTornado(Map* map, TowerDefenseGame* game){
	uint tornadoMaxDamage = 20;
	uint tornadoDuration_sec = 5;
	PathTile* tile = map->GetPathTile(_xPos, _yPos);
	if (tile != nullptr){
		tile->Tornado(tornadoMaxDamage, tornadoDuration_sec);
		return true;
	}
	return false;
}

bool CastSpellCommand::_CastRayos(Map* map, TowerDefenseGame* game){
	uint rayoMaxDamage = 50;
	EnviormentUnit* unit = game->GetUnit(_unitId);
	if (unit != nullptr){
		std::srand(std::time(0));
		uint randomDamage = (uint) std::rand() % rayoMaxDamage;
		unit->GetHit(randomDamage);
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