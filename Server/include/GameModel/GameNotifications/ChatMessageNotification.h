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
    ChatMessageNotification(std::string& message, PlayerProxy& player);
    ~ChatMessageNotification();
    void Notify(std::vector<PlayerProxy *> playersToNotify);
};


#endif //TOWERDEFENSE_CHATMESSAGENOTIFICATION_H
