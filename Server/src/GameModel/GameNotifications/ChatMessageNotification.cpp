//
// Created by tino on 20/11/17.
//

#include "../../../include/GameModel/GameNotifications/ChatMessageNotification.h"
#include "../../../../Common/Protocolo.h"

ChatMessageNotification::ChatMessageNotification(std::string& message, PlayerProxy& player)
:  _player(player), _message(message)
{

}
ChatMessageNotification::~ChatMessageNotification() {

}
void ChatMessageNotification::Notify(std::vector<PlayerProxy *> playersToNotify) {
    uint8_t opcode = IN_GAME_CHAT_MESSAGE;
    uint32_t playerChattingId = _player.GUID();
    for (auto it = playersToNotify.begin(); it != playersToNotify.end(); ++it){
        (*it)->SendByte(opcode);
        (*it)->SendInt32(playerChattingId);
        (*it)->SendString(_message);
    }
}