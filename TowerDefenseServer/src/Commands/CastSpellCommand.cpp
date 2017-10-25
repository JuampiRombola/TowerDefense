#include <memory>
#include <iostream>

#include "Towers/GroundTower.h"
#include "Map/SolidGroundTile.h"
#include "Map/PathTile.h"
#include "Commands/CastSpellCommand.h"
#include "Towers/Tower.h"

CastSpellCommand::CastSpellCommand(Spell spell, unsigned int x, unsigned int y):
 _xPos(x), _yPos(y), _unitId(-1), _spell(spell) {}

CastSpellCommand::CastSpellCommand(Spell spell, uint unitId):
 _xPos(-1), _yPos(-1), _unitId(unitId), _spell(spell) {}

CastSpellCommand::~CastSpellCommand(){}

void CastSpellCommand::Execute(Map* map){
	switch(_spell){
		case Terraforming: _CastTerraforming(map); break;
		case Grieta: _CastGrieta(map); break;
		case Meteorito: _CastMeteorito(map); break;
		case MuroDeFuego: _CastMuroDeFuego(map); break;
		case Congelacion: _CastCongelacion(map); break;
		case Ventisca: _CastVentisca(map); break;
		case Tornado: _CastTornado(map); break;
		case Rayos: _CastRayos(map); break;
		default: break;
	}
}

void CastSpellCommand::_CastTerraforming(Map* map){

}
void CastSpellCommand::_CastGrieta(Map* map){
	std::shared_ptr<PathTile> tile = map->GetPathTile(_xPos, _yPos);
	if (tile != std::shared_ptr<PathTile>(nullptr)){
		tile->Crack(4);
	}
}
void CastSpellCommand::_CastMeteorito(Map* map){

}
void CastSpellCommand::_CastMuroDeFuego(Map* map){

}
void CastSpellCommand::_CastCongelacion(Map* map){

}
void CastSpellCommand::_CastVentisca(Map* map){

}
void CastSpellCommand::_CastTornado(Map* map){

}
void CastSpellCommand::_CastRayos(Map* map){

}