//
// Created by tino on 21/11/17.
//

#ifndef TOWERDEFENSE_UPGRADETOWERCOMMAND_H
#define TOWERDEFENSE_UPGRADETOWERCOMMAND_H

#include "../../../Common/Protocolo.h"
#include "NetCommand.h"

class UpgradeTowerNetCommand : public NetCommand {
private:
    uint _x;
    uint _y;
    UpgradeType _upgradeType;
public:
    UpgradeTowerNetCommand(uint x, uint y, UpgradeType upgradeType );
    ~UpgradeTowerNetCommand();
    void SendCommand(SocketWrapper& sock);
};


#endif //TOWERDEFENSE_UPGRADETOWERCOMMAND_H
