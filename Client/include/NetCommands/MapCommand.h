#ifndef TOWERDEFENSE_MAPCOMMAND_H
#define TOWERDEFENSE_MAPCOMMAND_H


#include "../../../Common/SocketWrapper.h"
#include "NetCommand.h"

class MapCommand : public NetCommand {
private:
    int cmd;
    int tileX;
    int tileY;
public:
    MapCommand(int cmd, int tileX, int tileY);
    void SendCommand(SocketWrapper& socket);
};


#endif //TOWERDEFENSE_MAPCOMMAND_H
