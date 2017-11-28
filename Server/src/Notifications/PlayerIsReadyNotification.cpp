//
// Created by tino on 27/11/17.
//

#include "../../include/Notifications/PlayerIsReadyNotification.h"
#include "../../../Common/Protocolo.h"

PlayerIsReadyNotification::PlayerIsReadyNotification(Lobby &lobby, PlayerProxy &player)
: _lobby(lobby), _player(player) {}

PlayerIsReadyNotification::~PlayerIsReadyNotification() {

}

void PlayerIsReadyNotification::Notify() {
    std::vector<PlayerProxy*> tonotify = _lobby.GetPlayers();
    for (auto it = tonotify.begin(); it != tonotify.end(); ++it){
        PlayerProxy* p = *it;
        p->SendByte(PLAYER_IS_READY);
        p->SendInt32(_player.GUID());
    }
}

void PlayerIsReadyNotification::SetPlayersToNotify(std::vector<PlayerProxy *> *players) {

}