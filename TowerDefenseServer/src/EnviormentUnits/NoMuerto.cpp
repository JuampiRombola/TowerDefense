#include <iostream>

#include "EnviormentUnits/NoMuerto.h"

NoMuerto::NoMuerto(unsigned int id) : EnviormentUnit(id, 1000, 100) {}

NoMuerto::~NoMuerto()
{
	std::cout << "NoMuerto" << GetId() << " IS DEAD!!!\n";
}

void NoMuerto::PrintDebug(){
	PathTile* pos = GetPosition();
	if (pos == nullptr)
		std::cout << "NoMuerto" << GetId() << " outside map\n";
	else
		std::cout << "NoMuerto" << GetId() <<  "@(" << pos->GetXPos() << ", " << pos->GetYPos() << ")\n";
}

bool NoMuerto::Flies(){
	return false;
}