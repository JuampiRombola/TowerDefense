#include <iostream>

#include "EnviormentUnits/Abmonible.h"

Abmonible::Abmonible(uint id, uint stepDelay, uint healthPoints) : EnviormentUnit(id, stepDelay, healthPoints) {}

Abmonible::~Abmonible()
{
	std::cout << "Abmonible" << GetId() << " IS DEAD!!!\n";
}

void Abmonible::PrintDebug(){
	PathTile* pos = GetPosition();
	if (pos == nullptr)
		std::cout << "Abmonible" << GetId() << " outside map\n";
	else
		std::cout << "Abmonible" << GetId() <<  "@(" << pos->GetXPos() << ", " << pos->GetYPos() << ")\n";
}

bool Abmonible::Flies(){
	return false;
}