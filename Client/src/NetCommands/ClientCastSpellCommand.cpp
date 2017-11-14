#include "../../include/NetCommands/ClientCastSpellCommand.h"
#include "../../../Common/Protocolo.h"


ClientCastSpellCommand::ClientCastSpellCommand(CAST_SPELL_TYPE type, uint32_t tileX, uint32_t  tileY)
        : _type(type), _tileX(tileX), _tileY(tileY) {}

void ClientCastSpellCommand::SendCommand(SocketWrapper &sock) {
    uint8_t gameopcode = GAME_OPCODE;
    sock.Send((char*) &gameopcode, 1);
    uint8_t opcode = CLIENT_CAST_SPELL;
    sock.Send((char*) &opcode, 1);
    uint8_t type = _type;
    sock.Send((char*) &type, 1);
    sock.Send((char*) &_tileX, 4);
    sock.Send((char*) &_tileY, 4);
}
