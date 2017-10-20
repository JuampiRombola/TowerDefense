#include <iostream>
#include <algorithm>

#include "UnitIsNotOnThisTileException.h"
#include "UnitIsAlreadyOnThisTileException.h"
#include "EnviormentUnit.h"
#include "PathTile.h"

PathTile::PathTile(unsigned int xPos, unsigned int yPos) 
: Tile(xPos, yPos), _next(NULL), _units() {}

PathTile::~PathTile(){}


char PathTile::GetSymbol(){
	return 'P';
}

PathTile* PathTile::Next(){
	return _next;
}

void PathTile::SetNextTile(PathTile* tile){
	_next = tile;
}

bool PathTile::CanSpawn(){
	return _canSpawn;
}

void PathTile::SetCanSpawn(){
	_canSpawn = true;
}

void PathTile::Place(EnviormentUnit* unit){
	auto it = std::find(_units.begin(), _units.end(), unit);
	if (it == _units.end())
		_units.push_back(unit);
	else
		throw new UnitIsAlreadyOnThisTileException();

}

void PathTile::UnitEnter(EnviormentUnit* unit){
	std::cout << " pathtile: enter \n";
	auto it = std::find(_units.begin(), _units.end(), unit);
	if (it == _units.end())
		_units.push_back(unit);
	else 
		throw new UnitIsAlreadyOnThisTileException();
}


void PathTile::UnitLeave(EnviormentUnit* unit){
	std::cout << " pathtile: leave \n";
	auto it = std::find(_units.begin(), _units.end(), unit);
	if (it != _units.end())
		_units.erase(it);
	else
		throw new UnitIsNotOnThisTileException();
}

bool PathTile::HasAnyUnit(){
	return _units.begin() != _units.end();
}