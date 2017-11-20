//
// Created by tino on 20/11/17.
//

#include "NetCommand.h"

#ifndef TOWERDEFENSE_LOADMAPCOMMAND_H
#define TOWERDEFENSE_LOADMAPCOMMAND_H


class LoadMapCommand : public NetCommand {

public:
    LoadMapCommand();
    ~LoadMapCommand();
    void SendCommand(SocketWrapper& sock);
};


#endif //TOWERDEFENSE_LOADMAPCOMMAND_H