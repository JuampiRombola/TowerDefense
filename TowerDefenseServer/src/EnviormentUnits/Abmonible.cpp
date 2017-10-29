#include <iostream>

#include "EnviormentUnits/Abmonible.h"
#include "Map/PathTile.h"
#include "ViewModels/UnitVM.h"

Abmonible::Abmonible(uint id, uint stepDelay, uint healthPoints) : EnviormentUnit(id, stepDelay, healthPoints) {}

Abmonible::~Abmonible()
{
	std::cout << "Abmonible" << GetId() << " IS DEAD!!!\n";
}

void Abmonible::PrintDebug(){
	PathTile* pos = GetPosition();
	if (pos == nullptr)
		std::cout << "Abmonible" << GetId() << " outside map\n";
	else
		std::cout << "Abmonible" << GetId() <<  "@(" << pos->GetXPos() << ", " << pos->GetYPos() << ")\n";
}

bool Abmonible::Flies(){
	return false;
}

UnitVM Abmonible::GetViewModel(){
	UnitVM vm;
	vm.unitType = uAbmonible;
	vm.healthPoints = _healthPoints;
	vm.xPos = _position->GetXPos();
	vm.yPos = _position->GetYPos();
	vm.stepDelay_ms = _GetActualStepDelay();
	vm.id = _id;
	return vm;
}