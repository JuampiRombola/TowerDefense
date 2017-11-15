#include "../../include/Notifications/PlayerUnpickedSpellNotification.h"
#include "../../include/Lobbies/Lobby.h"
#include <iostream>

PlayerUnpickedSpellNotification::PlayerUnpickedSpellNotification(PlayerProxy& player, Lobby &lobby, SPELL_TYPE spelltype)
: _player(player), _spelltype(spelltype), _lobby(lobby)
{

}

PlayerUnpickedSpellNotification::~PlayerUnpickedSpellNotification(){

}

void PlayerUnpickedSpellNotification::SetPlayersToNotify(std::vector<PlayerProxy*>* players){

}

void PlayerUnpickedSpellNotification::Notify(){
	std::vector<PlayerProxy*> players = _lobby.GetOtherPlayersInLobby();
	for (auto it = players.begin(); it != players.end(); ++it){
		PlayerProxy* p = *it;
		if (p == &_player){
			uint8_t ins = UNPICK_SPELL;
			p->SendByte(ins);
			uint8_t spell = _spelltype;
			p->SendByte(spell);
		} else {
			uint32_t playerguid = _player.GUID();
			uint8_t ins = PLAYER_UNPICKED_SPELL;
			p->SendByte(ins);
			uint8_t spell = _spelltype;
			p->SendByte(spell);
			p->SendInt32(playerguid);
		}
	}
}