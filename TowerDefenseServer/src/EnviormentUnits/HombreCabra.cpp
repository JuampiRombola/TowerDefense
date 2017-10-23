#include <iostream>

#include "EnviormentUnits/HombreCabra.h"

HombreCabra::HombreCabra(unsigned int id) : EnviormentUnit(id, 1000, 100) {}

HombreCabra::~HombreCabra()
{
	std::cout << "HombreCabra" << GetId() << " IS DEAD!!!\n";
}

void HombreCabra::PrintDebug(){
	std::shared_ptr<PathTile> pos = GetPosition();
	if (pos.get() == nullptr)
		std::cout << "HombreCabra" << GetId() << " outside map\n";
	else
		std::cout << "HombreCabra" << GetId() <<  "@(" << pos.get()->GetXPos() << ", " << pos.get()->GetYPos() << ")\n";
}

bool HombreCabra::Flies(){
	return false;
}