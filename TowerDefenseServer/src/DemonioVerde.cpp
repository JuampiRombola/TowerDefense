#include <iostream>

#include "DemonioVerde.h"

DemonioVerde::DemonioVerde(unsigned int id) : EnviormentUnit(id) {}

DemonioVerde::~DemonioVerde(){}

void DemonioVerde::PrintDebug(){
	PathTile* pos = GetPosition();
	if (pos == NULL)
		std::cout << "DemonioVerde" << GetId() << " outside map\n";
	else
		std::cout << "DemonioVerde" << GetId() <<  "@(" << pos->GetXPos() << ", " << pos->GetYPos() << ")\n";
}