#include <iostream>
#include "StructureTile.h"

StructureTile::StructureTile(){}

StructureTile::~StructureTile(){}

bool StructureTile::AcceptsStructures(){
	return true;
}

bool StructureTile::IsPath(){
	return false;
}

char StructureTile::GetSymbol(){
	return 'L';
}