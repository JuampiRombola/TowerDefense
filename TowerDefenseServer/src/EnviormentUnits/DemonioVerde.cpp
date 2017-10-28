#include <iostream>

#include "EnviormentUnits/DemonioVerde.h"

DemonioVerde::DemonioVerde(uint id, uint stepDelay, uint healthPoints) : EnviormentUnit(id, stepDelay, healthPoints) {}

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