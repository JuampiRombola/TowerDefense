//
// Created by tino on 23/11/17.
//

#include "../../include/NetCommands/PickMapCommand.h"
#include "../../../Common/Protocolo.h"

PickMapCommand::PickMapCommand(uint mapid) : _mapId(mapid) {}

PickMapCommand::~PickMapCommand() {}

void PickMapCommand::SendCommand(SocketWrapper &sock) {
    sock.SendByte(PICK_MAP);
    sock.SendInt32(_mapId);
}