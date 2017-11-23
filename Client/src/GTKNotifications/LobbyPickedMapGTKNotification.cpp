//
// Created by tino on 23/11/17.
//

#include <zconf.h>
#include "../../include/GTKNotifications/LobbyPickedMapGTKNotification.h"
#include "../../GTKRunner.h"

LobbyPickedMapGTKNotification::LobbyPickedMapGTKNotification(uint lobbyId, uint mapId)
: _lobbyId(lobbyId), _mapId(mapId) {

}

LobbyPickedMapGTKNotification::~LobbyPickedMapGTKNotification() {

}

void LobbyPickedMapGTKNotification::Execute(GTKRunner &runner){
    if (runner.lobbyManager->joinedLobby->GUID() == _lobbyId){
        g_signal_handler_block(runner.combobox_maps, runner.combo_box_maps_changed_handler_id);
        gtk_combo_box_set_active(runner.combobox_maps, _mapId);
        g_signal_handler_unblock(runner.combobox_maps, runner.combo_box_maps_changed_handler_id);
    }
}