
#include <iostream>
#include "../../../include/GameModel/ViewModels/TowerVM.h"
#include "../../../include/GameModel/GameNotifications/UnitDiedGameNotification.h"
#include "../../../../Common/Protocolo.h"

UnitDiedGameNotification::UnitDiedGameNotification(UnitVM& viewmodel)
        : vm(viewmodel){
}

UnitDiedGameNotification::~UnitDiedGameNotification(){

}

void UnitDiedGameNotification::Notify(std::vector<PlayerProxy*> playersToNotify) {
    for (auto it = playersToNotify.begin(); it != playersToNotify.end(); it++) {
        PlayerProxy *p = *it;
        int8_t game = GAME_OPCODE;
        p->SendByte(game);
        int8_t opcode = UNIT_DIED;
        p->SendByte(opcode);
        uint32_t unitid = vm.id;
        p->SendInt32(unitid);
    }
}