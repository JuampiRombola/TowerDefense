//
// Created by tino on 21/11/17.
//

#include "../../../include/GameModel/GameNotifications/TowerGainedExperienceGameNotification.h"
#include "../../../../Common/Protocolo.h"

TowerGainedExperienceGameNotification::TowerGainedExperienceGameNotification(uint x, uint y, uint exp)
: _x(x), _y(y), _exp(exp){

}

TowerGainedExperienceGameNotification::~TowerGainedExperienceGameNotification() {

}

void TowerGainedExperienceGameNotification::Notify(std::vector<PlayerProxy *> playersToNotify) {
    uint8_t gameopcode = GAME_OPCODE;
    uint8_t expopcode = TOWER_GAINED_EXP;
    for (auto it = playersToNotify.begin(); it != playersToNotify.end(); ++it){
        PlayerProxy* p = *it;
        p->SendByte(gameopcode);
        p->SendByte(expopcode);
        p->SendInt32(_x);
        p->SendInt32(_y);
        p->SendInt32(_exp);
    }
}