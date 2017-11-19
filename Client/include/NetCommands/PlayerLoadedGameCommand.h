//
// Created by tino on 19/11/17.
//

#ifndef TOWERDEFENSE_PLAYERLOADEDGAMECOMMAND_H
#define TOWERDEFENSE_PLAYERLOADEDGAMECOMMAND_H


#include "NetCommand.h"

class PlayerLoadedGameCommand : public NetCommand {
public:
    PlayerLoadedGameCommand();
    ~PlayerLoadedGameCommand();
    void SendCommand(SocketWrapper& sock);
};


#endif //TOWERDEFENSE_PLAYERLOADEDGAMECOMMAND_H

