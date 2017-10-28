#include <iostream>

#include "EnviormentUnits/HombreCabra.h"

HombreCabra::HombreCabra(uint id, uint stepDelay, uint healthPoints) : EnviormentUnit(id, stepDelay, healthPoints) {}

HombreCabra::~HombreCabra()
{
	std::cout << "HombreCabra" << GetId() << " IS DEAD!!!\n";
}

void HombreCabra::PrintDebug(){
	PathTile* pos = GetPosition();
	if (pos == nullptr)
		std::cout << "HombreCabra" << GetId() << " outside map\n";
	else
		std::cout << "HombreCabra" << GetId() <<  "@(" << pos->GetXPos() << ", " << pos->GetYPos() << ")\n";
}

bool HombreCabra::Flies(){
	return false;
}