//
// Created by tino on 21/11/17.
//

#include "../../../include/GameModel/Hordes/Horde.h"


Horde::Horde(uint id)
:  _id(id), abmonibleAmount(0),
 demonioVerdeAmount(0),
 halconSangrientoAmount(0),
 noMuertoAmount(0),
 hombreCabraAmount(0),
 espectroAmount(0),
 timeBetweenUnits_ms(0),
   finishNotified(false){}

Horde::~Horde() {

}

uint Horde::Id(){
    return _id;
}

bool Horde::IsFinished() {
    bool itis = true;
    itis &= hombreCabraAmount == 0;
    itis &= abmonibleAmount == 0;
    itis &= halconSangrientoAmount == 0;
    itis &= espectroAmount == 0;
    itis &= noMuertoAmount == 0;
    itis &= demonioVerdeAmount == 0;
    
    for (auto it = units.begin(); it != units.end(); ++it){
        itis &= !(*it)->IsAlive();
    }
    return itis;
}
