#include <ctime>
#include <iostream>

#include "../../include/Towers/GroundTower.h"
#include "../../include/Map/SolidGroundTile.h"
#include "../../include/Map/PathTile.h"
#include "../../include/Commands/CastSpellCommand.h"
#include "../../include/Towers/Tower.h"
#include "../../include/EnviormentUnits/EnviormentUnit.h"
#include "../../include/TowerDefenseGame.h"
#include "../../include/ViewModels/CommandVM.h"

CastSpellCommand::CastSpellCommand(Spell spell, uint x, uint y):
 _xPos(x), _yPos(y), _unitId(-1), _spell(spell) {}

CastSpellCommand::CastSpellCommand(Spell spell, uint unitId):
 _xPos(-1), _yPos(-1), _unitId(unitId), _spell(spell) {}

CastSpellCommand::~CastSpellCommand(){}

bool CastSpellCommand::Execute(Map* map, TowerDefenseGame* game){
	switch(_spell){
		case Terraforming: return _CastTerraforming(map);
		case Grieta: return _CastGrieta(map);
		case Meteorito: return _CastMeteorito(map);
		case MuroDeFuego: return _CastMuroDeFuego(map);
		case Congelacion: return _CastCongelacion(map, game);
		case Ventisca: return _CastVentisca(map);
		case Tornado: return _CastTornado(map);
		case Rayos: return _CastRayos(map, game);
		default: return false;
	}
}

bool CastSpellCommand::_CastTerraforming(Map* map){
	SolidGroundTile* tile = map->GetSolidGroundTile(_xPos, _yPos);
	if (tile != nullptr)
		return false;

	map->PlaceGroundTile(new SolidGroundTile(_xPos,_yPos));
	return true;
}

bool CastSpellCommand::_CastGrieta(Map* map){
	PathTile* tile = map->GetPathTile(_xPos, _yPos);
	if (tile != nullptr){
		tile->Crack(400);
		return true;
	}
	return false;
}

bool CastSpellCommand::_CastMeteorito(Map* map){
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

bool CastSpellCommand::_CastMuroDeFuego(Map* map){
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

bool CastSpellCommand::_CastVentisca(Map* map){
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

bool CastSpellCommand::_CastTornado(Map* map){
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

}