//
// Created by tino on 21/11/17.
//

#include "../../../include/GameModel/GameNotifications/HordeUpdateGameNotification.h"
#include "../../../../Common/Protocolo.h"

HordeUpdateGameNotification::HordeUpdateGameNotification(uint hordeId, std::vector<PlayerProxy *> playerToNotify, bool started)
: GameNotification(playerToNotify), _hordeId(hordeId), _started(started)
{

}

HordeUpdateGameNotification::~HordeUpdateGameNotification() {

}
void HordeUpdateGameNotification::Notify() {

    for (auto it = _playersToNotify.begin(); it != _playersToNotify.end(); ++it){
        PlayerProxy* p = *it;
        uint opcode = GAME_OPCODE;
        uint ins = _started ? HORDE_STARTED : HORDE_ENDED;
        p->SendByte(opcode);
        p->SendByte(ins);
        p->SendInt32(_hordeId);
    }
}