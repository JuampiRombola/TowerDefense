#include "../../include/NetCommands/MapCommand.h"


MapCommand::MapCommand(int cmd, int tileX, int tileY) : cmd(cmd), tileX
        (tileX), tileY(tileY) {}

void MapCommand::SendCommand(SocketWrapper &sock) {
    sock.Send((char*) &cmd, sizeof(int));
    sock.Send((char*) &tileX, sizeof(int));
    sock.Send((char*) &tileY, sizeof(int));
}
