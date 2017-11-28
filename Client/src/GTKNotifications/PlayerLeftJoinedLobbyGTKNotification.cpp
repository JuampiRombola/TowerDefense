//
// Created by tino on 12/11/17.
//

#include "../../include/GTKNotifications/PlayerLeftJoinedLobbyGTKNotification.h"
#include "../../GTKmm/GTKmmRunner.h"

PlayerLeftJoinedLobbyGTKNotification::PlayerLeftJoinedLobbyGTKNotification(OtherPlayer& player, Lobby& lobby, bool inmylobby, bool joined) :
        _player(player), _lobby(lobby), _inmylobby(inmylobby), _joined(joined) {

}

PlayerLeftJoinedLobbyGTKNotification::~PlayerLeftJoinedLobbyGTKNotification() {

}
void PlayerLeftJoinedLobbyGTKNotification::Execute(GTKmmRunner& runner){

    int amount = _joined ? 1 : -1;
    runner.fixed_lobbies.UpdateLobbyPlayerCount(_lobby.GUID(), amount);
    if (_inmylobby){

        if (_joined)
            runner.fixed_lobby.AddPlayer(_player);
        else
            runner.fixed_lobby.RemovePlayer(_player);
    }
}
