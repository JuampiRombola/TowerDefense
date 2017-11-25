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
    sock.SendByte(GAME_OPCODE);
    sock.SendByte(TOWER_UPGRADE);
    sock.SendByte(_upgradeType);
    sock.SendInt32(_x);
    sock.SendInt32(_y);
}