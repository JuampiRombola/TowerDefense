#include <iostream>

#include "EnviormentUnits/Abmonible.h"

Abmonible::Abmonible(unsigned int id) : EnviormentUnit(id, 1000, 100) {}

Abmonible::~Abmonible()
{
	std::cout << "Abmonible" << GetId() << " IS DEAD!!!\n";
}

void Abmonible::PrintDebug(){
	std::shared_ptr<PathTile> pos = GetPosition();
	if (pos.get() == nullptr)
		std::cout << "Abmonible" << GetId() << " outside map\n";
	else
		std::cout << "Abmonible" << GetId() <<  "@(" << pos.get()->GetXPos() << ", " << pos.get()->GetYPos() << ")\n";
}

bool Abmonible::Flies(){
	return false;
}