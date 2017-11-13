#ifndef TOWERDEFENSE_PICKED_SPELL_GTKNOTIFICATION_H
#define TOWERDEFENSE_PICKED_SPELL_GTKNOTIFICATION_H


#include "../Lobbies/Lobby.h"
#include "GTKNotification.h"
#include "../../../Common/Protocolo.h"


class PickedSpellGTKNotification : public GTKNotification {
private:
    SPELL_TYPE _spelltype;
    bool _pick;
public:
    PickedSpellGTKNotification(SPELL_TYPE spelltype, bool pick);
    ~PickedSpellGTKNotification();
    void Execute(GTKRunner& runner);
};


#endif
