#ifndef TOWERDEFENSE_OTHER_PLAYER_PICKED_SPELL_GTKNOTIFICATION_H
#define TOWERDEFENSE_OTHER_PLAYER_PICKED_SPELL_GTKNOTIFICATION_H


#include "../Lobbies/Lobby.h"
#include "GTKNotification.h"
#include "../../../Common/Protocolo.h"


class OtherPickedSpellGTKNotification : public GTKNotification {
private:
    OtherPlayer& _otherPlayer;
    SPELL_TYPE _spelltype;
    bool _pick;
public:
    OtherPickedSpellGTKNotification(OtherPlayer& otherPlayer, SPELL_TYPE spelltype, bool pick);
    ~OtherPickedSpellGTKNotification();
    void Execute(GTKRunner& runner);
};


#endif
