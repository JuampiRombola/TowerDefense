//
// Created by tino on 19/11/17.
//

#include "../../../include/GameModel/GameNotifications/GameModelStartedRunningNotification.h"
#include "../../../../Common/Protocolo.h"


GameModelStartedRunningNotification::
GameModelStartedRunningNotification()
{

}

GameModelStartedRunningNotification::~GameModelStartedRunningNotification() {}

void GameModelStartedRunningNotification::Notify(std::vector<PlayerProxy *> playersToNotify) {
    for (auto it = playersToNotify.begin(); it != playersToNotify.end(); it++) {
        PlayerProxy *p = *it;
        int8_t game = GAME_MODEL_STARTED_RUNNING;
        p->SendByte(game);
    }
}