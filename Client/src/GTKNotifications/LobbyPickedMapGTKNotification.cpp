//
// Created by tino on 23/11/17.
//

#include <zconf.h>
#include "../../include/GTKNotifications/LobbyPickedMapGTKNotification.h"

LobbyPickedMapGTKNotification::LobbyPickedMapGTKNotification(uint lobbyId, uint mapId)
: _lobbyId(lobbyId), _mapId(mapId) {

}

LobbyPickedMapGTKNotification::~LobbyPickedMapGTKNotification() {

}

void LobbyPickedMapGTKNotification::Execute(GTKRunner &runner) {
}