
#include "../../../include/GameModel/GameNotifications/GameOverGameNotification.h"
#include "../../../../Common/Protocolo.h"

GameOverGameNotification::
GameOverGameNotification(bool playersWon)
        :  _playersWon(playersWon)
{

}

GameOverGameNotification::~GameOverGameNotification(){

}

void GameOverGameNotification::Notify(std::vector<PlayerProxy*> playersToNotify) {
    for (auto it = playersToNotify.begin(); it != playersToNotify.end(); it++) {
        PlayerProxy *p = *it;
        int8_t game = GAME_OPCODE;
        p->SendByte(game);
        int8_t opcode = _playersWon ? GAME_WON : GAME_OVER;
        p->SendByte(opcode);
    }
}