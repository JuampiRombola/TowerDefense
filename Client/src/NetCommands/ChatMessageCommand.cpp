//
// Created by tino on 20/11/17.
//

#include "../../include/NetCommands/ChatMessageCommand.h"
#include "../../../Common/Protocolo.h"


ChatMessageCommand::ChatMessageCommand(std::string &message) : _message(message) {}

ChatMessageCommand::~ChatMessageCommand() {}

void ChatMessageCommand::SendCommand(SocketWrapper &socket) {
    socket.SendByte(IN_GAME_CHAT_MESSAGE);
    socket.SendString(_message);
}