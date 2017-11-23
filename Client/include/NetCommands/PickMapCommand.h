//
// Created by tino on 23/11/17.
//

#ifndef TOWERDEFENSE_PICKMAPCOMMAND_H
#define TOWERDEFENSE_PICKMAPCOMMAND_H


#include <zconf.h>
#include "NetCommand.h"

class PickMapCommand : public NetCommand {
private:
    uint _mapId;
public:
    PickMapCommand(uint mapid);
    ~PickMapCommand();
    void SendCommand(SocketWrapper& sock);

};


#endif //TOWERDEFENSE_PICKMAPCOMMAND_H
