
#include <iostream>
#include "../../../include/GameModel/GameNotifications/UnitFrozenGameNotification.h"
#include "../../../../Common/Protocolo.h"

UnitFrozenGameNotification::UnitFrozenGameNotification(uint unitId, uint freeze_time_ms)
: _unitId(unitId), _freeze_time_ms(freeze_time_ms)
{

}


UnitFrozenGameNotification::~UnitFrozenGameNotification(){

}

void UnitFrozenGameNotification::Notify(std::vector<PlayerProxy*> playersToNotify){
    for (auto it = playersToNotify.begin(); it != playersToNotify.end(); it++) {
        PlayerProxy *p = *it;
        p->SendByte(GAME_OPCODE);
        p->SendByte(UNIT_FROZEN);
        p->SendInt32(_unitId);
        p->SendInt32(_freeze_time_ms);
    }
}