//
// Created by tino on 21/11/17.
//

#include "../../../include/GameModel/GameNotifications/HordeUpdateGameNotification.h"
#include "../../../../Common/Protocolo.h"

HordeUpdateGameNotification::HordeUpdateGameNotification(uint hordeId, bool started)
:  _hordeId(hordeId), _started(started)
{

}

HordeUpdateGameNotification::~HordeUpdateGameNotification() {

}
void HordeUpdateGameNotification::Notify(std::vector<PlayerProxy *> playersToNotify) {

    for (auto it = playersToNotify.begin(); it != playersToNotify.end(); ++it){
        PlayerProxy* p = *it;
        uint opcode = GAME_OPCODE;
        uint ins = _started ? HORDE_STARTED : HORDE_ENDED;
        p->SendByte(opcode);
        p->SendByte(ins);
        p->SendInt32(_hordeId);
    }
}