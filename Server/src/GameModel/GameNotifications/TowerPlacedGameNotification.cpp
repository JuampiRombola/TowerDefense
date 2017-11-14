
#include <iostream>
#include "../../../include/GameModel/ViewModels/TowerVM.h"
#include "../../../include/GameModel/GameNotifications/TowerPlacedGameNotification.h"
#include "../../../../Common/Protocolo.h"

TowerPlacedGameNotification::TowerPlacedGameNotification(TowerVM& viewmodel, std::vector<PlayerProxy*> playersToNotify)
        : GameNotification(playersToNotify), vm(viewmodel){
}

TowerPlacedGameNotification::~TowerPlacedGameNotification(){

}

void TowerPlacedGameNotification::Notify() {
    for (auto it = _playersToNotify.begin(); it != _playersToNotify.end(); it++) {
        PlayerProxy *p = *it;
        int8_t game = GAME_OPCODE;
        p->sock.Send((char *) &game, 1);
        int8_t opcode = TOWER_PLACED;
        p->sock.Send((char *) &opcode, 1);
        uint32_t x = vm.xPos;
        p->sock.Send((char *) &x, 4);
        uint32_t y = vm.yPos;
        p->sock.Send((char *) &y, 4);
        SPELL_TYPE type;
        switch (vm.type) {
            case Ground:
                type = SPELL_TYPE_GROUND;
                break;
            case Fire:
                type = SPELL_TYPE_FIRE;
                break;
            case Water:
                type = SPELL_TYPE_WATER;
                break;
            case Air:
                type = SPELL_TYPE_AIR;
                break;
        }
        uint8_t spelltype = type;
        p->sock.Send((char *) &spelltype, 1);
    }
}