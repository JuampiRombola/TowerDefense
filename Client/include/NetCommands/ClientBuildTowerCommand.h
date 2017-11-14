#ifndef TOWERDEFENSE_MAPCOMMAND_H
#define TOWERDEFENSE_MAPCOMMAND_H


#include "../../../Common/SocketWrapper.h"
#include "NetCommand.h"
#include "../../../Common/Protocolo.h"

class ClientBuildTowerCommand : public NetCommand {
private:
    SPELL_TYPE _type;
    uint32_t _tileX;
    uint32_t _tileY;
public:
    ClientBuildTowerCommand(SPELL_TYPE  type, uint32_t  tileX, uint32_t  tileY);
    void SendCommand(SocketWrapper& socket);
};


#endif //TOWERDEFENSE_MAPCOMMAND_H
