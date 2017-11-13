//
// Created by tino on 13/11/17.
//

#include "../../../include/GameModel/GameNotifications/UnitCreatedGameNotification.h"

UnitCreatedGameNotification::UnitCreatedGameNotification(UnitVM& viewmodel, std::vector<PlayerProxy*> playersToNotify)
: GameNotification(playersToNotify)
{

}

UnitCreatedGameNotification::~UnitCreatedGameNotification(){

}

void UnitCreatedGameNotification::Notify(){
    for (auto it = _playersToNotify.begin(); it != _playersToNotify.end(); it++) {
        PlayerProxy *p = *it;
        int8_t game = GAME_OPCODE;
        p->sock.Send((char *) &game, 1);
        int8_t opcode = UNIT_CREATED;
        p->sock.Send((char *) &opcode, 1);
        uint32_t unitID = vm.id;
        p->sock.Send((char *) &unitID, 4);
        uint32_t x = vm.xPos;
        p->sock.Send((char *) &x, 4);
        uint32_t y = vm.yPos;
        p->sock.Send((char *) &y, 4);
        uint32_t tox = vm.nextXpos;
        p->sock.Send((char *) &tox, 4);
        uint32_t toy = vm.nextYpos;
        p->sock.Send((char *) &toy, 4);
        uint32_t delay_ms = vm.stepDelay_ms;
        p->sock.Send((char *) &delay_ms, 4);
        uint8_t spelltype = vm.unitType;
        p->sock.Send((char*) &spelltype, 1);
    }
}