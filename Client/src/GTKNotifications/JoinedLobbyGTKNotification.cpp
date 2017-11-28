#include "../../include/GTKNotifications/JoinedLobbyGTKNotification.h"
#include "../../GTKmm/GTKmmRunner.h"


JoinedLobbyGUINotification::JoinedLobbyGUINotification(Lobby& lobby)
: _lobby(lobby)
{
}

JoinedLobbyGUINotification::~JoinedLobbyGUINotification(){
	
}

void JoinedLobbyGUINotification::Execute(GTKmmRunner& runner){
    runner.fixed_lobby.label_lobbyname->set_text(_lobby.Name());
    runner.box->remove(*runner.fixed_lobbies.fixed);
    runner.box->add(*runner.fixed_lobby.fixed);


    runner.fixed_lobby.toggle_fire->set_state_flags(Gtk::StateFlags::STATE_FLAG_NORMAL);
    runner.fixed_lobby.toggle_water->set_sensitive(true);
    runner.fixed_lobby.toggle_water->set_state_flags(Gtk::StateFlags::STATE_FLAG_NORMAL);
    runner.fixed_lobby.toggle_water->set_sensitive(true);
    runner.fixed_lobby.toggle_air->set_state_flags(Gtk::StateFlags::STATE_FLAG_NORMAL);
    runner.fixed_lobby.toggle_air->set_sensitive(true);
    runner.fixed_lobby.toggle_ground->set_state_flags(Gtk::StateFlags::STATE_FLAG_NORMAL);
    runner.fixed_lobby.toggle_ground->set_sensitive(true);



    runner.fixed_lobby.RemoveAllPlayers();

    auto ps = _lobby.GetOtherPlayersInLobby();
    for (auto it = ps.begin(); it != ps.end(); ++it){
        runner.fixed_lobby.AddPlayer(*(*it));
    }

    runner.fixed_lobby.AddMe(runner.lobbyManager->myName, runner.lobbyManager->myGuid);

    uint myguid = runner.lobbyManager->myGuid;
    int fguid = _lobby.firePlayerGUID();
    int wguid = _lobby.waterPlayerGUID();
    int gguid = _lobby.groundPlayerGUID();
    int aguid = _lobby.airPlayerGUID();

    bool wsensitive = true;
    bool gsensitive = true;
    bool fsensitive = true;
    bool asensitive = true;

    if (fguid > 0){
        fsensitive = (fguid == myguid);
        runner.fixed_lobby.toggle_fire->set_state_flags(Gtk::StateFlags::STATE_FLAG_CHECKED);
        runner.fixed_lobby.fire_pguid = fguid;
    }

    if (wguid > 0){
        wsensitive = (wguid == myguid);
        runner.fixed_lobby.toggle_water->set_state_flags(Gtk::StateFlags::STATE_FLAG_CHECKED);
        runner.fixed_lobby.water_pguid = wguid;
    }

    if (gguid > 0){
        gsensitive = (gguid == myguid);
        runner.fixed_lobby.toggle_ground->set_state_flags(Gtk::StateFlags::STATE_FLAG_CHECKED);
        runner.fixed_lobby.ground_pguid = gguid;
    }

    if (aguid > 0){
        asensitive = (aguid == myguid);
        runner.fixed_lobby.toggle_air->set_state_flags(Gtk::StateFlags::STATE_FLAG_CHECKED);
        runner.fixed_lobby.air_pguid = aguid;
    }

    runner.fixed_lobby.toggle_fire->set_sensitive(fsensitive);
    runner.fixed_lobby.toggle_water->set_sensitive(wsensitive);
    runner.fixed_lobby.toggle_ground->set_sensitive(gsensitive);
    runner.fixed_lobby.toggle_air->set_sensitive(asensitive);

    runner.fixed_lobby.combobox_changed_signal.block();
    runner.fixed_lobby.combobox_maps->set_active(_lobby.pickedMapId);
    runner.fixed_lobby.combobox_changed_signal.unblock();



}