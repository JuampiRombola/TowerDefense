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
    sock.Send((char*)&gameopcode, 1);
    sock.Send((char*)&opcode, 1);
    sock.Send((char*)&type, 1);
    sock.Send((char*)&_x, 4);
    sock.Send((char*)&_y, 4);
}