#include "../../include/Notifications/SpellIsFreeNotification.h"

#include <iostream>

SpellIsFreeNotification::SpellIsFreeNotification( SPELL_TYPE type, std::vector<PlayerProxy*>& tonotify)
: _spelltype(type)

{
	_playersToNotify = tonotify;
}

SpellIsFreeNotification::~SpellIsFreeNotification(){

}

void SpellIsFreeNotification::SetPlayersToNotify(std::vector<PlayerProxy*>* players){
	_playersToNotify = *players;
}

void SpellIsFreeNotification::Notify(){
	for (auto it = _playersToNotify.begin(); it != _playersToNotify.end(); ++it){
		PlayerProxy* p = *it;
		p->SendByte(SPELL_IS_FREE);
		p->SendByte(_spelltype);
	}
	
}