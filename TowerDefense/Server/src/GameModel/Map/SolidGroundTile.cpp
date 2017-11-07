#include <iostream>


#include "../../../include/GameModel/Towers/Projectile.h"
#include "../../../include/GameModel/Map/SolidGroundTile.h"
#include "../../../include/GameModel/Exceptions/SolidGroundAlreadyHasTowerException.h"
#include "../../../include/GameModel/Towers/Tower.h"

SolidGroundTile::SolidGroundTile(uint xPos, uint yPos): 
Tile(xPos, yPos), _tower(nullptr) {}

SolidGroundTile::~SolidGroundTile()
{
	if (_tower != nullptr)
		delete _tower;
}

char SolidGroundTile::GetSymbol(){
	return 'L';
}

void SolidGroundTile::PlaceTower(Tower* t){
	if (t == nullptr)
		return;

	if (_tower == nullptr)
		_tower = t;
	else
		throw SolidGroundAlreadyHasTowerException();
}

Tower* SolidGroundTile::GetTower(){
	return _tower;
}

bool SolidGroundTile::HasTower(){
	return _tower != nullptr;
}

Projectile* SolidGroundTile::Step(){
	if (_tower != nullptr){
		return _tower->Step();
	}
	return nullptr;
}