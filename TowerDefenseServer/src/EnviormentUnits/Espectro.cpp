#include <iostream>

#include "EnviormentUnits/Espectro.h"

Espectro::Espectro(uint id, uint stepDelay, uint healthPoints) : EnviormentUnit(id, stepDelay, healthPoints) {}

Espectro::~Espectro()
{
	std::cout << "Espectro" << GetId() << " IS DEAD!!!\n";
}

void Espectro::PrintDebug(){
	PathTile* pos = GetPosition();
	if (pos == nullptr)
		std::cout << "Espectro" << GetId() << " outside map\n";
	else
		std::cout << "Espectro" << GetId() <<  "@(" << pos->GetXPos() << ", " << pos->GetYPos() << ")\n";
}

bool Espectro::Flies(){
	return true;
}