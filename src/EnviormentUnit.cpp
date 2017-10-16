#include <iostream>
#include "EnviormentUnit.h"

EnviormentUnit::EnviormentUnit(unsigned int id) : _id(id), _position(NULL) {


}

EnviormentUnit::~EnviormentUnit(){

}

void EnviormentUnit::Step(){
	if (_position != NULL)
		_position = _position->Next();
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

