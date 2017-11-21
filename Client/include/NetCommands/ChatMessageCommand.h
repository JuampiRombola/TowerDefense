//
// Created by tino on 20/11/17.
//

#include "NetCommand.h"

#ifndef TOWERDEFENSE_CHATMESSAGECOMMAND_H
#define TOWERDEFENSE_CHATMESSAGECOMMAND_H


class ChatMessageCommand : public NetCommand {
private:
    std::string _message;
public:
    ChatMessageCommand(std::string& message);
    ~ChatMessageCommand();
    void SendCommand(SocketWrapper& socket);
};


#endif //TOWERDEFENSE_CHATMESSAGECOMMAND_H
