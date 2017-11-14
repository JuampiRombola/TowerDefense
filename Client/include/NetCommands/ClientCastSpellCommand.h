#ifndef TOWERDEFENSE_CAST_SPELL_COMMAND_H
#define TOWERDEFENSE_CAST_SPELL_COMMAND_H


#include "../../../Common/SocketWrapper.h"
#include "NetCommand.h"
#include "../../../Common/Protocolo.h"

class ClientCastSpellCommand : public NetCommand {
private:
    CAST_SPELL_TYPE _type;
    uint32_t _tileX;
    uint32_t _tileY;
public:
    ClientCastSpellCommand(CAST_SPELL_TYPE  type, uint32_t  tileX, uint32_t  tileY);
    void SendCommand(SocketWrapper& socket);
};


#endif
