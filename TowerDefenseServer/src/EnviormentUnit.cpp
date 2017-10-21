#include <iostream>

#include "PathTile.h"
#include "EnviormentUnit.h"
#include "NonPlacedUnitCannotStep.h"
#include "IncompletePathException.h"

EnviormentUnit::EnviormentUnit(unsigned int id) : _id(id), _position(NULL) {


}

EnviormentUnit::~EnviormentUnit(){

}

void EnviormentUnit::Step(){
	if (_position == NULL)
		throw new NonPlacedUnitCannotStep();
	
	_position->UnitLeave(this);
	_position = _position->Next();

	if (_position == NULL)
		throw new IncompletePathException();

	_position->UnitEnter(this);
}

PathTile* EnviormentUnit::GetPosition(){
	return _position;
}

void EnviormentUnit::SetPosition(PathTile* pos){
	_position = pos;
}
unsigned int EnviormentUnit::GetId(){
	return _id;
}

