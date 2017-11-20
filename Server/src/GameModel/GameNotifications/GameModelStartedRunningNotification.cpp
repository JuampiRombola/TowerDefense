//
// Created by tino on 19/11/17.
//

#include "../../../include/GameModel/GameNotifications/GameModelStartedRunningNotification.h"
#include "../../../../Common/Protocolo.h"


GameModelStartedRunningNotification::
GameModelStartedRunningNotification(std::vector<PlayerProxy *> playersToNotify)
: GameNotification(playersToNotify){

}

GameModelStartedRunningNotification::~GameModelStartedRunningNotification() {}

void GameModelStartedRunningNotification::Notify() {
    for (auto it = _playersToNotify.begin(); it != _playersToNotify.end(); it++) {
        PlayerProxy *p = *it;
        int8_t game = GAME_MODEL_STARTED_RUNNING;
        p->SendByte(game);
    }
}