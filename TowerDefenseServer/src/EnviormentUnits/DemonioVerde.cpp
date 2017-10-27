#include <iostream>

#include "EnviormentUnits/DemonioVerde.h"

DemonioVerde::DemonioVerde(unsigned int id) : EnviormentUnit(id, 1000, 100) {}

DemonioVerde::~DemonioVerde()
{
	std::cout << "DemonioVerde" << GetId() << " IS DEAD!!!\n";
}

void DemonioVerde::PrintDebug(){
	PathTile* pos = GetPosition();
	if (pos == nullptr)
		std::cout << "DemonioVerde" << GetId() << " outside map\n";
	else
		std::cout << "DemonioVerde" << GetId() <<  "@(" << pos->GetXPos() << ", " << pos->GetYPos() << ")\n";
}

bool DemonioVerde::Flies(){
	return false;
}