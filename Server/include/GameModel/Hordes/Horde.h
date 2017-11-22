//
// Created by tino on 21/11/17.
//

#ifndef TOWERDEFENSE_HORDE_H
#define TOWERDEFENSE_HORDE_H


#include <zconf.h>
#include "../EnviormentUnits/EnviormentUnit.h"

class Horde {
private:
    uint _id;
public:
    Horde(uint id);
    ~Horde();
    uint abmonibleAmount;
    uint demonioVerdeAmount;
    uint halconSangrientoAmount;
    uint noMuertoAmount;
    uint hombreCabraAmount;
    uint espectroAmount;
    uint timeBetweenUnits_ms;
    std::vector<EnviormentUnit*> units;
    bool IsFinished();
    uint Id();
    bool finishNotified;
};


#endif //TOWERDEFENSE_HORDE_H
