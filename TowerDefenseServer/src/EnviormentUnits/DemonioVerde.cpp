#include <iostream>

#include "../../include/EnviormentUnits/DemonioVerde.h"
#include "../../include/Map/PathTile.h"
#include "../../include/ViewModels/UnitVM.h"

DemonioVerde::DemonioVerde(uint id, uint stepDelay, uint healthPoints) : EnviormentUnit(id, stepDelay, healthPoints) {}

DemonioVerde::~DemonioVerde()
{
	std::cout << "DemonioVerde" << GetId() << " IS DEAD!!!\n";
}

void DemonioVerde::PrintDebug(){
	PathTile* pos = GetPosition();
	if (pos == nullptr)
		std::cout << "DemonioVerde" << GetId() << " outside map\n";
	else
		std::cout << "DemonioVerde" << GetId() <<  "@(" << pos->GetXPos() << ", " << pos->GetYPos() << ")\n";
}

bool DemonioVerde::Flies(){
	return false;
}

UnitVM DemonioVerde::GetViewModel(){
	UnitVM vm;
	vm.unitType = uDemonioVerde;
	vm.healthPoints = _healthPoints;
	vm.xPos = _position->GetXPos();
	vm.yPos = _position->GetYPos();
	vm.stepDelay_ms = _GetActualStepDelay();
	vm.id = _id;
	return vm;
}