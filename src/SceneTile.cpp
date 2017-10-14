#include <iostream>
#include "SceneTile.h"

SceneTile::SceneTile(){}

SceneTile::~SceneTile(){}

bool SceneTile::AcceptsStructures(){
	return false;
}

bool SceneTile::IsPath(){
	return false;
}

char SceneTile::GetSymbol(){
	return 'S';
}
