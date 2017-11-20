//
// Created by tino on 20/11/17.
//

#ifndef TOWERDEFENSE_CHATMESSAGENOTIFICATION_H
#define TOWERDEFENSE_CHATMESSAGENOTIFICATION_H

#include "../../PlayerProxy.h"
#include "GameNotification.h"

class ChatMessageNotification : public GameNotification {
private:
    PlayerProxy& _player;
    std::string _message;
public:
    ChatMessageNotification(std::string& message, PlayerProxy& player, std::vector<PlayerProxy*> playersToNotify);
    ~ChatMessageNotification();
    void Notify();
};


#endif //TOWERDEFENSE_CHATMESSAGENOTIFICATION_H
