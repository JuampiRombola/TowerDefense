#include <iostream>
#include <cmath>
#include <memory>

#include "Projectile.h"
#include "PathTile.h"

Projectile::Projectile(std::shared_ptr<SolidGroundTile> origin, std::shared_ptr<PathTile> target, uint speed, uint hitpoints) :
 _speed(speed), _impacted(false), _distance(0), 
 _distanceCovered(0), _hitPoints(hitpoints), _target(target)
{
	uint dx = abs(origin->GetXPos() - target->GetXPos());
	uint dy = abs(origin->GetYPos() - target->GetYPos());
	uint temp = (dx*dx) + (dy*dy);
	double sq = sqrt(temp);
	_distance = floor(sq) * 10;
	std::cout << "PROJECTILE CREATED DISTANCE: " << _distance << ", SPEED: " << _speed << "\n" << std::flush;
}

Projectile::~Projectile(){}


void Projectile::Step(){
	_distanceCovered += _speed;
	if (_distanceCovered >= _distance && !_impacted){

		_OnImpact();

		_impacted = true;

		std::cout << "PROJECTILE LANDED\n" << std::flush;
	}
}

void Projectile::PrintDebug(){
	
}

bool Projectile::Impacted(){
	return _impacted;
}