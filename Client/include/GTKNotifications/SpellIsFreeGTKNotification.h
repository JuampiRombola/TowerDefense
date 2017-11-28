//
// Created by tino on 27/11/17.
//

#ifndef TOWERDEFENSE_SPELLISFREEGTKNOTIFICATION_H
#define TOWERDEFENSE_SPELLISFREEGTKNOTIFICATION_H


#include "GTKNotification.h"
#include "../../../Common/Protocolo.h"

class SpellIsFreeGTKNotification : public GTKNotification {
private:
    SPELL_TYPE _spelltype;
public:
    SpellIsFreeGTKNotification(SPELL_TYPE type);
    ~SpellIsFreeGTKNotification();
    void Execute(GTKmmRunner& runner);
};


#endif //TOWERDEFENSE_SPELLISFREEGTKNOTIFICATION_H
