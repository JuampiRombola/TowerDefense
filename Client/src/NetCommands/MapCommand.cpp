#include "../../include/NetCommands/MapCommand.h"


MapCommand::MapCommand(int cmd, int tileX, int tileY) : cmd(cmd), tileX
        (tileX), tileY(tileY) {}

void MapCommand::SendCommand(SocketWrapper &sock) {
    sock.Send((char*) &cmd, 1);
    sock.Send((char*) &tileX, 4);
    sock.Send((char*) &tileY, 4);
}
