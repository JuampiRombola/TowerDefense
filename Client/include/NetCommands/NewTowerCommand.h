#ifndef TOWERDEFENSE_NEWTOWERCOMMAND_H
#define TOWERDEFENSE_NEWTOWERCOMMAND_H

#include "NetCommand.h"
#include "../../../Common/Protocolo.h"
#include "../../View/Model/ViewConstants.h"

class NewTowerCommand : public NetCommand {
private:
    std::string towerElement;
    int tileX;
    int tileY;
    uint8_t getElementCodeFromKey();
public:
    NewTowerCommand(std::string towerElement, int tileX, int tileY);
    void SendCommand(SocketWrapper &sock);
};


#endif //TOWERDEFENSE_NEWTOWERCOMMAND_H
