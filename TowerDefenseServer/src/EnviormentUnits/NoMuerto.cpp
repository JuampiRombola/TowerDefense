#include <iostream>

#include "EnviormentUnits/NoMuerto.h"
#include "Map/PathTile.h"
#include "ViewModels/UnitVM.h"

NoMuerto::NoMuerto(uint id, uint stepDelay, uint healthPoints) : EnviormentUnit(id, stepDelay, healthPoints) {}

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

UnitVM NoMuerto::GetViewModel(){
	UnitVM vm;
	vm.unitType = uNoMuerto;
	vm.healthPoints = _healthPoints;
	vm.xPos = _position->GetXPos();
	vm.yPos = _position->GetYPos();
	vm.stepDelay_ms = _GetActualStepDelay();
	vm.id = _id;
	return vm;
}