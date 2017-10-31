#include <iostream>

#include "../../include/EnviormentUnits/Espectro.h"
#include "../../include/Map/PathTile.h"
#include "../../include/ViewModels/UnitVM.h"

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

UnitVM Espectro::GetViewModel(){
	UnitVM vm;
	vm.unitType = uEspectro;
	vm.healthPoints = _healthPoints;
	vm.xPos = _position->GetXPos();
	vm.yPos = _position->GetYPos();
	vm.stepDelay_ms = _GetActualStepDelay();
	vm.id = _id;
	return vm;
}