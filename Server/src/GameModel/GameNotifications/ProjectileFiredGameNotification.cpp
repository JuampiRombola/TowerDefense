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
        p->sock.Send((char *) &game, 1);
        int8_t opcode = PROJECTILE_FIRED;
        p->sock.Send((char *) &opcode, 1);
        uint32_t x = vm.fromXpos;
        p->sock.Send((char *) &x, 4);
        uint32_t y = vm.fromYpos;
        p->sock.Send((char *) &y, 4);
        uint32_t tox = vm.toXpos;
        p->sock.Send((char *) &tox, 4);
        uint32_t toy = vm.toYpos;
        p->sock.Send((char *) &toy, 4);
        uint32_t delay_ms = 500;
        p->sock.Send((char *) &delay_ms, 4);
        uint8_t spelltype = vm.type;
        p->sock.Send((char*) &spelltype, 1);
    }
}