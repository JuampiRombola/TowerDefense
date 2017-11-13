#include "../../include/Notifications/PlayerPickedSpellNotification.h"
#include "../../include/Lobbies/Lobby.h"
#include <iostream>

PlayerPickedSpellNotification::PlayerPickedSpellNotification(PlayerProxy& player, Lobby &lobby, SPELL_TYPE spelltype)
: _player(player), _spelltype(spelltype), _lobby(lobby) {
}

PlayerPickedSpellNotification::~PlayerPickedSpellNotification(){

}

void PlayerPickedSpellNotification::SetPlayersToNotify(std::vector<PlayerProxy*>* players){

}

void PlayerPickedSpellNotification::Notify(){
	std::vector<PlayerProxy*> players = _lobby.GetOtherPlayersInLobby();
	for (auto it = players.begin(); it != players.end(); ++it){
		PlayerProxy* p = *it;
		if (p == &_player){
			uint8_t ins = PICK_SPELL;
			p->sock.Send((char*) &ins, 1);
			uint8_t spell = _spelltype;
			p->sock.Send((char*) &spell, 1);
		} else {
			uint32_t playerguid = _player.GUID();
			uint8_t ins = PLAYER_PICKED_SPELL;
			p->sock.Send((char*) &ins, 1);
			uint8_t spell = _spelltype;
			p->sock.Send((char*) &spell, 1);
			p->sock.Send((char*) &playerguid, 4);
		}
	}
}