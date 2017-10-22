#include <iostream>
#include <cmath>

#include "Projectile.h"
#include "PathTile.h"

Projectile::Projectile(SolidGroundTile* origin, PathTile* target, uint speed) :
_target(target), _speed(speed), _impacted(false), _distance(0), _distanceCovered(0)
{
	uint dx = abs(origin->GetXPos() - target->GetXPos());
	uint dy = abs(origin->GetYPos() - target->GetYPos());
	uint temp = (dx*dx) + (dy*dy);
	double sq = sqrt(temp);
	_distance = floor(sq) * 10;
	std::cout << "PROJECTILE DISTANCE " << _distance << "\n" << std::flush;
}

Projectile::~Projectile(){}


void Projectile::Step(){
	_distanceCovered += _speed;
	if (_distanceCovered >= _distance && !_impacted){

		std::cout << "HIT TARGET TILE\n";
		//std::vector<EnviormentUnit*> units = _target->GetUnits();
		//for (auto it = units.begin(); it != units.end(); ++it)
		//	this->_Hit();
		_impacted = true;
	}
}

void Projectile::PrintDebug(){
	
}

bool Projectile::Impacted(){
	return _impacted;
}