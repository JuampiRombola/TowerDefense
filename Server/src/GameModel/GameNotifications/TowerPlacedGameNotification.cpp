
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
        p->SendByte(game);
        int8_t opcode = TOWER_PLACED;
        p->SendByte(opcode);
        uint32_t x = vm.xPos;
        p->SendInt32(x);
        uint32_t y = vm.yPos;
        p->SendInt32(y);
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
        p->SendByte(spelltype);
    }
}