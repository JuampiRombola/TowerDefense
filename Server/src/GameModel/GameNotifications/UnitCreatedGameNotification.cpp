//
// Created by tino on 13/11/17.
//

#include <iostream>
#include "../../../include/GameModel/GameNotifications/UnitCreatedGameNotification.h"

UnitCreatedGameNotification::UnitCreatedGameNotification(UnitVM& viewmodel)
: vm(viewmodel)
{

}

UnitCreatedGameNotification::~UnitCreatedGameNotification(){

}

void UnitCreatedGameNotification::Notify(std::vector<PlayerProxy*> playersToNotify){
    for (auto it = playersToNotify.begin(); it != playersToNotify.end(); it++) {
        PlayerProxy *p = *it;
        int8_t game = GAME_OPCODE;
        p->SendByte(game);
        int8_t opcode = UNIT_CREATED;
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
        uint8_t unittype = vm.unitType;
        p->SendByte(unittype);
        std::cout << "unit notification created delay: " << vm.stepDelay_ms << " x: " << x << ", y: " << y 
                  << ", to x: " << tox << ", toy: " << toy <<'\n' <<std::flush;
    }
}