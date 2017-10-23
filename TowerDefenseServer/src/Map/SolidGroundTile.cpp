#include <iostream>
#include <memory>

#include "Towers/Projectile.h"
#include "Map/SolidGroundTile.h"
#include "Exceptions/SolidGroundAlreadyHasTowerException.h"
#include "Towers/Tower.h"

SolidGroundTile::SolidGroundTile(unsigned int xPos, unsigned int yPos): 
Tile(xPos, yPos), _tower(std::shared_ptr<Tower>()) {}

SolidGroundTile::~SolidGroundTile(){}

char SolidGroundTile::GetSymbol(){
	return 'L';
}

void SolidGroundTile::PlaceTower(std::shared_ptr<Tower> t){
	if (_tower.get() == nullptr && t.get() != nullptr)
		_tower = t;
	else
		throw new SolidGroundAlreadyHasTowerException();
}

bool SolidGroundTile::HasTower(){
	return _tower.get() != nullptr;
}

std::shared_ptr<Projectile> SolidGroundTile::Step(){
	if (_tower.get() != nullptr){
		return (*_tower).Step();
	}
	return std::shared_ptr<Projectile>(nullptr);
}