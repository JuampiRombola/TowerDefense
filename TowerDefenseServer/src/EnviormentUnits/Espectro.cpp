#include <iostream>

#include "EnviormentUnits/Espectro.h"

Espectro::Espectro(unsigned int id) : EnviormentUnit(id, 5000, 100) {}

Espectro::~Espectro()
{
	std::cout << "Espectro" << GetId() << " IS DEAD!!!\n";
}

void Espectro::PrintDebug(){
	std::shared_ptr<PathTile> pos = GetPosition();
	if (pos.get() == nullptr)
		std::cout << "Espectro" << GetId() << " outside map\n";
	else
		std::cout << "Espectro" << GetId() <<  "@(" << pos.get()->GetXPos() << ", " << pos.get()->GetYPos() << ")\n";
}

bool Espectro::Flies(){
	return true;
}