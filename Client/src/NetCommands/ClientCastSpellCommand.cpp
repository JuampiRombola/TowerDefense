#include "../../include/NetCommands/ClientCastSpellCommand.h"
#include "../../../Common/Protocolo.h"


ClientCastSpellCommand::ClientCastSpellCommand(CAST_SPELL_TYPE type, uint32_t tileX, uint32_t  tileY)
        : _type(type), _tileX(tileX), _tileY(tileY) {}

void ClientCastSpellCommand::SendCommand(SocketWrapper &sock) {
    sock.SendByte(GAME_OPCODE);
    sock.SendByte(CLIENT_CAST_SPELL);
    uint8_t type = _type;
    sock.SendByte(type);
    sock.SendInt32(_tileX);
    sock.SendInt32(_tileY);
}
