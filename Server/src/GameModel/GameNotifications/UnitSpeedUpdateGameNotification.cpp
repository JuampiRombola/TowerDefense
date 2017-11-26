
#include <iostream>
#include "../../../include/GameModel/ViewModels/UnitVM.h"
#include "../../../include/GameModel/GameNotifications/UnitSpeedUpdateGameNotification.h"
#include "../../../../Common/Protocolo.h"

UnitSpeedUpdateGameNotification::UnitSpeedUpdateGameNotification(uint unitId, uint stepDelay_ms)
: _unitId(unitId), _stepDelay_ms(stepDelay_ms)
{

}


UnitSpeedUpdateGameNotification::~UnitSpeedUpdateGameNotification(){

}

void UnitSpeedUpdateGameNotification::Notify(std::vector<PlayerProxy*> playersToNotify){
    for (auto it = playersToNotify.begin(); it != playersToNotify.end(); it++) {
        PlayerProxy *p = *it;
        p->SendByte(GAME_OPCODE);
        p->SendByte(UNIT_SPEED_UPDATE);
        p->SendInt32(_unitId);
        p->SendInt32(_stepDelay_ms);
    }
}