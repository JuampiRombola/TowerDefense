#include <ctime>
#include <iostream>

#include "Towers/GroundTower.h"
#include "Map/SolidGroundTile.h"
#include "Map/PathTile.h"
#include "Commands/CastSpellCommand.h"
#include "Towers/Tower.h"
#include "EnviormentUnits/EnviormentUnit.h"
#include "TowerDefenseGame.h"

CastSpellCommand::CastSpellCommand(Spell spell, unsigned int x, unsigned int y):
 _xPos(x), _yPos(y), _unitId(-1), _spell(spell) {}

CastSpellCommand::CastSpellCommand(Spell spell, uint unitId):
 _xPos(-1), _yPos(-1), _unitId(unitId), _spell(spell) {}

CastSpellCommand::~CastSpellCommand(){}

void CastSpellCommand::Execute(Map* map, TowerDefenseGame* game){
	switch(_spell){
		case Terraforming: _CastTerraforming(map); break;
		case Grieta: _CastGrieta(map); break;
		case Meteorito: _CastMeteorito(map); break;
		case MuroDeFuego: _CastMuroDeFuego(map); break;
		case Congelacion: _CastCongelacion(map, game); break;
		case Ventisca: _CastVentisca(map); break;
		case Tornado: _CastTornado(map); break;
		case Rayos: _CastRayos(map, game); break;
		default: break;
	}
}

void CastSpellCommand::_CastTerraforming(Map* map){
	map->PlaceGroundTile(new SolidGroundTile(_xPos,_yPos));
}
void CastSpellCommand::_CastGrieta(Map* map){
	PathTile* tile = map->GetPathTile(_xPos, _yPos);
	if (tile != NULL){
		tile->Crack(400);
	}
}
void CastSpellCommand::_CastMeteorito(Map* map){
	uint collateralDamageRange = 2;
	uint collateralDamage = 10;
	uint targetDamage = 30;
	PathTile* tile = map->GetPathTile(_xPos, _yPos);
	if (tile != NULL){
		std::vector<PathTile*> tiles = map->GetTilesInRange(tile, collateralDamageRange);
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


}
void CastSpellCommand::_CastMuroDeFuego(Map* map){
	uint fireDuration_sec = 5;
	uint fireDamage = 10;
	PathTile* tile = map->GetPathTile(_xPos, _yPos);
	if (tile != NULL)
		tile->SetOnFire(fireDuration_sec, fireDamage);
}
void CastSpellCommand::_CastCongelacion(Map* map, TowerDefenseGame* game){
	uint freezeDurationSec = 5;
	EnviormentUnit* unit = game->GetUnit(_unitId);
	if (unit != NULL)
		unit->Freeze(freezeDurationSec);
}
void CastSpellCommand::_CastVentisca(Map* map){
	uint ventiscaDamage = 5;
	uint percentSlow = 95;
	uint slowDuration_sec = 4;
	uint ventiscaDuration_sec = 5;
	PathTile* tile = map->GetPathTile(_xPos, _yPos);
	if (tile != NULL)
		tile->Ventisca(ventiscaDamage, ventiscaDuration_sec, slowDuration_sec, percentSlow);
}
void CastSpellCommand::_CastTornado(Map* map){
	uint tornadoMaxDamage = 20;
	uint tornadoDuration_sec = 5;
	PathTile* tile = map->GetPathTile(_xPos, _yPos);
	if (tile != NULL)
		tile->Tornado(tornadoMaxDamage, tornadoDuration_sec);

}
void CastSpellCommand::_CastRayos(Map* map, TowerDefenseGame* game){
	uint rayoMaxDamage = 50;
	EnviormentUnit* unit = game->GetUnit(_unitId);
	if (unit != NULL){
		std::srand(std::time(0));
		uint randomDamage = (uint) std::rand() % rayoMaxDamage;
		unit->GetHit(randomDamage);
	}
}