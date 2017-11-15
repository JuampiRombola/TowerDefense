
#include "../../../include/GameModel/GameNotifications/GameOverGameNotification.h"
#include "../../../../Common/Protocolo.h"

GameOverGameNotification::GameOverGameNotification(std::vector<PlayerProxy*> playersToNotify) : GameNotification(playersToNotify)
{

}

GameOverGameNotification::~GameOverGameNotification(){

}

void GameOverGameNotification::Notify() {
    for (auto it = _playersToNotify.begin(); it != _playersToNotify.end(); it++) {
        PlayerProxy *p = *it;
        int8_t game = GAME_OPCODE;
        p->SendByte(game);
        int8_t opcode = GAME_OVER;
        p->SendByte(opcode);
    }
}