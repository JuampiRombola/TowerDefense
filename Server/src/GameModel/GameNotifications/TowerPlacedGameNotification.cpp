
#include <iostream>
#include "../../../include/GameModel/ViewModels/TowerVM.h"
#include "../../../include/GameModel/GameNotifications/TowerPlacedGameNotification.h"
#include "../../../../Common/Protocolo.h"

TowerPlacedGameNotification::TowerPlacedGameNotification(TowerVM& viewmodel)
        : GameNotification(), vm(viewmodel){
}

TowerPlacedGameNotification::~TowerPlacedGameNotification(){

}

void TowerPlacedGameNotification::Notify(std::vector<PlayerProxy*> playersToNotify) {
    for (auto it = playersToNotify.begin(); it != playersToNotify.end(); it++) {
        PlayerProxy *p = *it;
        p->SendByte(GAME_OPCODE);
        p->SendByte(TOWER_PLACED);
        p->SendInt32(vm.xPos);
        p->SendInt32(vm.yPos);
        p->SendInt32(vm.tower_placement_cooldown_sec);
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
        p->SendByte(type);
    }
}