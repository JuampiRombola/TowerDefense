//
// Created by tino on 20/11/17.
//

#include "../../../include/GameModel/GameNotifications/ChatMessageNotification.h"
#include "../../../../Common/Protocolo.h"

ChatMessageNotification::ChatMessageNotification(std::string& message, PlayerProxy& player, std::vector<PlayerProxy *> playersToNotify)
: GameNotification(playersToNotify), _player(player), _message(message)
{

}
ChatMessageNotification::~ChatMessageNotification() {

}
void ChatMessageNotification::Notify() {
    uint8_t opcode = IN_GAME_CHAT_MESSAGE;
    uint32_t playerChattingId = _player.GUID();
    for (auto it = _playersToNotify.begin(); it != _playersToNotify.end(); ++it){
        (*it)->SendByte(opcode);
        (*it)->SendInt32(playerChattingId);
        (*it)->SendString(_message);
    }
}