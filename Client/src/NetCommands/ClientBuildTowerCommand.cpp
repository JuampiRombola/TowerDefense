#include "../../include/NetCommands/ClientBuildTowerCommand.h"
#include "../../../Common/Protocolo.h"


ClientBuildTowerCommand::ClientBuildTowerCommand(SPELL_TYPE  type, uint32_t  tileX, uint32_t  tileY)
        : _type(type), _tileX(tileX), _tileY(tileY) {}

void ClientBuildTowerCommand::SendCommand(SocketWrapper &sock) {
    uint8_t gameopcode = GAME_OPCODE;
    sock.SendByte(gameopcode);
    uint8_t opcode = CLIENT_CREATE_TOWER;
    sock.SendByte(opcode);
    sock.SendByte(_type);
    sock.SendInt32(_tileX);
    sock.SendInt32(_tileY);
}
