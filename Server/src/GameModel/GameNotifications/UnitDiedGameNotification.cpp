
#include <iostream>
#include "../../../include/GameModel/ViewModels/TowerVM.h"
#include "../../../include/GameModel/GameNotifications/UnitDiedGameNotification.h"
#include "../../../../Common/Protocolo.h"

UnitDiedGameNotification::UnitDiedGameNotification(UnitVM& viewmodel, std::vector<PlayerProxy*> playersToNotify)
        : GameNotification(playersToNotify), vm(viewmodel){
}

UnitDiedGameNotification::~UnitDiedGameNotification(){

}

void UnitDiedGameNotification::Notify() {
    for (auto it = _playersToNotify.begin(); it != _playersToNotify.end(); it++) {
        PlayerProxy *p = *it;
        int8_t game = GAME_OPCODE;
        p->SendByte(game);
        int8_t opcode = UNIT_DIED;
        p->SendByte(opcode);
        uint32_t unitid = vm.id;
        p->SendInt32(unitid);
    }
}