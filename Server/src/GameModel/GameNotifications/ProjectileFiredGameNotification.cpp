//
// Created by tino on 13/11/17.
//

#include "../../../include/GameModel/GameNotifications/ProjectileFiredGameNotification.h"
#include "../../../../Common/Protocolo.h"

ProjectileFiredGameNotification::ProjectileFiredGameNotification(ProjectileVM vm, std::vector<PlayerProxy*> playersToNotify)
: GameNotification(playersToNotify), vm(vm){

}

ProjectileFiredGameNotification::~ProjectileFiredGameNotification() {

}

void ProjectileFiredGameNotification::Notify(){
    for (auto it = _playersToNotify.begin(); it != _playersToNotify.end(); it++) {
        PlayerProxy *p = *it;
        int8_t game = GAME_OPCODE;
        p->SendByte(game);
        int8_t opcode = PROJECTILE_FIRED;
        p->SendByte(opcode);
        uint32_t x = vm.fromXpos;
        p->SendInt32(x);
        uint32_t y = vm.fromYpos;
        p->SendInt32(y);
        uint32_t tox = vm.toXpos;
        p->SendInt32(tox);
        uint32_t toy = vm.toYpos;
        p->SendInt32(toy);
        uint32_t delay_ms = 500;
        p->SendInt32(delay_ms);
        uint8_t spelltype = vm.type;
        p->SendByte(spelltype);
    }
}