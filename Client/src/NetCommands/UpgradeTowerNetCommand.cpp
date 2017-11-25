//
// Created by tino on 21/11/17.
//

#include "../../include/NetCommands/UpgradeTowerNetCommand.h"

UpgradeTowerNetCommand::UpgradeTowerNetCommand(uint x, uint y, UpgradeType upgradeType)
: _x(x), _y(y), _upgradeType(upgradeType){

}

UpgradeTowerNetCommand::~UpgradeTowerNetCommand() {

}

void UpgradeTowerNetCommand::SendCommand(SocketWrapper &sock) {
    uint8_t opcode = TOWER_UPGRADE;
    uint8_t gameopcode = GAME_OPCODE;
    uint8_t type = _upgradeType;
    sock.SendByte(gameopcode);
    sock.SendByte(opcode);
    sock.SendByte(type);
    sock.SendInt32(_x);
    sock.SendInt32(_y);
}