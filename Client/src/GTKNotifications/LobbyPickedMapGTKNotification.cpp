//
// Created by tino on 23/11/17.
//

#include <zconf.h>
#include "../../include/GTKNotifications/LobbyPickedMapGTKNotification.h"
#include "../../GTKmm/GTKmmRunner.h"

LobbyPickedMapGTKNotification::LobbyPickedMapGTKNotification(uint lobbyId, uint mapId)
: _lobbyId(lobbyId), _mapId(mapId) {

}

LobbyPickedMapGTKNotification::~LobbyPickedMapGTKNotification() {

}

void LobbyPickedMapGTKNotification::Execute(GTKmmRunner &runner){
    
    if (runner.lobbyManager->joinedLobby != nullptr){
        if (runner.lobbyManager->joinedLobby->GUID() == _lobbyId){
            runner.fixed_lobby.combobox_changed_signal.block();
            runner.fixed_lobby.combobox_maps->set_active(_mapId);
            runner.fixed_lobby.combobox_changed_signal.unblock();
        } 
    }

}