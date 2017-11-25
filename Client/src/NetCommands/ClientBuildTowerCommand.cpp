#include "../../include/NetCommands/ClientBuildTowerCommand.h"
#include "../../../Common/Protocolo.h"


ClientBuildTowerCommand::ClientBuildTowerCommand(SPELL_TYPE  type, uint32_t  tileX, uint32_t  tileY)
        : _type(type), _tileX(tileX), _tileY(tileY) {}

void ClientBuildTowerCommand::SendCommand(SocketWrapper &sock) {
    sock.SendByte(GAME_OPCODE);
    sock.SendByte(CLIENT_CREATE_TOWER);
    sock.SendByte(_type);
    sock.SendInt32(_tileX);
    sock.SendInt32(_tileY);
}
