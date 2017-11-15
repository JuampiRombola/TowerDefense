
#include <iostream>
#include "../../../include/GameModel/ViewModels/UnitVM.h"
#include "../../../include/GameModel/GameNotifications/UnitPositionGameNotification.h"
#include "../../../../Common/Protocolo.h"

UnitPositionGameNotification::UnitPositionGameNotification(UnitVM& viewmodel, std::vector<PlayerProxy*> playersToNotify)
        : GameNotification(playersToNotify), vm(viewmodel){

}


UnitPositionGameNotification::~UnitPositionGameNotification(){

}

void UnitPositionGameNotification::Notify(){
    for (auto it = _playersToNotify.begin(); it != _playersToNotify.end(); it++) {
        PlayerProxy *p = *it;
        int8_t game = GAME_OPCODE;
        p->SendByte(game);
        int8_t opcode = UNIT_POSITION_UPDATE;
        p->SendByte(opcode);
        uint32_t unitID = vm.id;
        p->SendInt32(unitID);
        uint32_t x = vm.xPos;
        p->SendInt32(x);
        uint32_t y = vm.yPos;
        p->SendInt32(y);
        uint32_t tox = vm.nextXpos;
        p->SendInt32(tox);
        uint32_t toy = vm.nextYpos;
        p->SendInt32(toy);
        uint32_t delay_ms = vm.stepDelay_ms;
        p->SendInt32(delay_ms);
        std::cout << "unit position noti x: " << x << ", y: " << y << ", to x: " << tox << ", toy: " << toy <<'\n' <<std::flush;
    }
}