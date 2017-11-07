#include <iostream>

#include "../../../include/GameModel/EnviormentUnits/HombreCabra.h"
#include "../../../include/GameModel/Map/PathTile.h"
#include "../../../include/GameModel/ViewModels/UnitVM.h"

HombreCabra::HombreCabra(uint id, uint stepDelay, uint healthPoints, ThreadSafeQueue<GameNotification*>& notifications) 
: EnviormentUnit(id, stepDelay, healthPoints, notifications) {}

HombreCabra::~HombreCabra()
{
	std::cout << "HombreCabra" << GetId() << " IS DEAD!!!\n";
}

void HombreCabra::PrintDebug(){
	return;
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
	if (_position->next != nullptr){
		vm.nextXpos = _position->next->GetXPos();
		vm.nextYpos = _position->next->GetYPos();
	} else{
		vm.nextYpos = -1;
		vm.nextXpos = -1;
	}
	vm.stepDelay_ms = _GetActualStepDelay();
	vm.id = _id;
	return vm;
}