//
// Created by tino on 11/11/17.
//

#ifndef TOWERDEFENSE_LOGINSUCCESSGTKNOTIFICATION_H
#define TOWERDEFENSE_LOGINSUCCESSGTKNOTIFICATION_H

#include "GTKNotification.h"
#include "../Lobbies/Lobby.h"

class LogInSuccessGtkNotification : public GTKNotification{
private:
    std::string _myname;
    std::vector<Lobby*> _lobbies;
public:
    LogInSuccessGtkNotification(std::vector<Lobby*>& lobbies, std::string myname);
    ~LogInSuccessGtkNotification();
    void Execute(GTKmmRunner& runner);
};


#endif //TOWERDEFENSE_LOGINSUCCESSGTKNOTIFICATION_H
