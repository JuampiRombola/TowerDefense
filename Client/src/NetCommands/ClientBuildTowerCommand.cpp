#include "../../include/NetCommands/ClientBuildTowerCommand.h"
#include "../../../Common/Protocolo.h"


ClientBuildTowerCommand::ClientBuildTowerCommand(SPELL_TYPE  type, uint32_t  tileX, uint32_t  tileY)
        : _type(type), _tileX(tileX), _tileY(tileY) {}

void ClientBuildTowerCommand::SendCommand(SocketWrapper &sock) {
    uint8_t gameopcode = GAME_OPCODE;
    sock.Send((char*) &gameopcode, 1);

    uint8_t opcode = CLIENT_CREATE_TOWER;
    sock.Send((char*) &opcode, 1);

    sock.Send((char*) &_type, 1);
    sock.Send((char*) &_tileX, 4);
    sock.Send((char*) &_tileY, 4);
}
