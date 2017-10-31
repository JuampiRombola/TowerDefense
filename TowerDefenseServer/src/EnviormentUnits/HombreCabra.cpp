#include <iostream>

#include "../../include/EnviormentUnits/HombreCabra.h"
#include "../../include/Map/PathTile.h"
#include "../../include/ViewModels/UnitVM.h"

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

UnitVM HombreCabra::GetViewModel(){
	UnitVM vm;
	vm.unitType = uHombreCabra;
	vm.healthPoints = _healthPoints;
	vm.xPos = _position->GetXPos();
	vm.yPos = _position->GetYPos();
	vm.stepDelay_ms = _GetActualStepDelay();
	vm.id = _id;
	return vm;
}