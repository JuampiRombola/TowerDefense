#include <iostream>
#include <cmath>

#include "Towers/Projectile.h"
#include "Map/PathTile.h"
#include "Map/SolidGroundTile.h"
#include "Towers/Tower.h"

Projectile::Projectile(Tower* origin, PathTile* target, uint speed, uint hitpoints) :
 _speed(speed), _impacted(false), _distance(0), 
 _distanceCovered(0), _origin(origin), _hitPoints(hitpoints), _target(target)
{
	uint dx = abs(origin->GetPosition()->GetXPos() - target->GetXPos());
	uint dy = abs(origin->GetPosition()->GetYPos() - target->GetYPos());
	uint temp = (dx*dx) + (dy*dy);
	double sq = sqrt(temp);
	_distance = floor(sq) * 10;
	std::cout << "PROJECTILE CREATED DISTANCE: " << _distance << ", SPEED: " << _speed << "\n" << std::flush;
}

Projectile::~Projectile(){}


void Projectile::Step(){
	_distanceCovered += _speed;
	if (_distanceCovered >= _distance && !_impacted){

		double exp = _OnImpact();

		_origin->AddExperience(exp);

		_impacted = true;

		std::cout << "PROJECTILE LANDED\n" << std::flush;
	}
}

void Projectile::PrintDebug(){
	
}

bool Projectile::Impacted(){
	return _impacted;
}