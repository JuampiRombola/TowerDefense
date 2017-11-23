//
// Created by tino on 23/11/17.
//

#include "../../include/NetCommands/PickMapCommand.h"
#include "../../../Common/Protocolo.h"

PickMapCommand::PickMapCommand(uint mapid) : _mapId(mapid) {}

PickMapCommand::~PickMapCommand() {}

void PickMapCommand::SendCommand(SocketWrapper &sock) {
    uint8_t op = PICK_MAP;
    sock.Send((char*) &op, 1);
    sock.Send((char*) &_mapId, 4);
}