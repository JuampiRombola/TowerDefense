#include "../../include/NetCommands/NewTowerCommand.h"

NewTowerCommand::NewTowerCommand(std::string towerElement, int tileX, int tileY)
        : towerElement(towerElement), tileX(tileX), tileY(tileY) {}

void NewTowerCommand::SendCommand(SocketWrapper &sock) {
    uint8_t opcode = NEW_TOWER;
    sock.Send((char*) &opcode, 1);
    uint8_t element = getElementCodeFromKey();
    sock.Send((char*) &element, 1);
    sock.Send((char*) &tileX, 4);
    sock.Send((char*) &tileY, 4);
}

uint8_t NewTowerCommand::getElementCodeFromKey() {
    /*if (towerElement == FIRE_TOWER_KEY)
        return FIRE_TOWER;
    else if (towerElement == WATER_TOWER_KEY)
        return WATER_TOWER;
    else if (towerElement == EARTH_TOWER_KEY)
        return EARTH_TOWER;
    else if (towerElement == AIR_TOWER_KEY)
        return AIR_TOWER;*/
}