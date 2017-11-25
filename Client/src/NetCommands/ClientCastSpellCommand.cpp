#include "../../include/NetCommands/ClientCastSpellCommand.h"
#include "../../../Common/Protocolo.h"


ClientCastSpellCommand::ClientCastSpellCommand(CAST_SPELL_TYPE type, uint32_t tileX, uint32_t  tileY)
        : _type(type), _tileX(tileX), _tileY(tileY) {}

void ClientCastSpellCommand::SendCommand(SocketWrapper &sock) {
    uint8_t gameopcode = GAME_OPCODE;
    uint8_t opcode = CLIENT_CAST_SPELL;
    sock.SendByte(gameopcode);
    sock.SendByte(opcode);
    uint8_t type = _type;
    sock.SendByte(type);
    sock.SendInt32(_tileX);
    sock.SendInt32(_tileY);
}
