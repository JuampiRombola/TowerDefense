#ifndef TOWERDEFENSE_OTHER_PLAYER_PICKED_SPELL_GTKNOTIFICATION_H
#define TOWERDEFENSE_OTHER_PLAYER_PICKED_SPELL_GTKNOTIFICATION_H


#include "../Lobbies/Lobby.h"
#include "GTKNotification.h"
#include "../../../Common/Protocolo.h"


class PickSpellGTKNotification : public GTKNotification {
private:
    uint _pguid;
    SPELL_TYPE _spelltype;
public:
    PickSpellGTKNotification(uint pguid, SPELL_TYPE spelltype);
    ~PickSpellGTKNotification();
    void Execute(GTKmmRunner& runner);
};


#endif
