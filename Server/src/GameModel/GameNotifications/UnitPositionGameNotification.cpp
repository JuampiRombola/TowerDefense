
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
        p->sock.Send((char *) &game, 1);
        int8_t opcode = UNIT_POSITION_UPDATE;
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
    }
}