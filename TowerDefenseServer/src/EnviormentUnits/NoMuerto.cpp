#include <iostream>

#include "EnviormentUnits/NoMuerto.h"

NoMuerto::NoMuerto(unsigned int id) : EnviormentUnit(id, 1000, 100) {}

NoMuerto::~NoMuerto()
{
	std::cout << "NoMuerto" << GetId() << " IS DEAD!!!\n";
}

void NoMuerto::PrintDebug(){
	std::shared_ptr<PathTile> pos = GetPosition();
	if (pos.get() == nullptr)
		std::cout << "NoMuerto" << GetId() << " outside map\n";
	else
		std::cout << "NoMuerto" << GetId() <<  "@(" << pos.get()->GetXPos() << ", " << pos.get()->GetYPos() << ")\n";
}

bool NoMuerto::Flies(){
	return false;
}