
#include "../../include/Lobbies/ClientLobbyManager.h"
#include "../../include/Lobbies/Lobby.h"
#include "../../../Common/Protocolo.h"
#include "../../include/GTKNotifications/NewLobbyGTKNotification.h"
#include "../../include/GTKNotifications/JoinedLobbyGTKNotification.h"
#include "../../include/Exceptions/SomePlayerLeftLobbyAndLobbyNotSet.h"
#include "../../include/Exceptions/PlayerJoinedInexistingLobbyException.h"
#include "../../include/Exceptions/PlayerNotFoundException.h"
#include "../../include/Exceptions/OtherPlayerJoinedLobbyTwice.h"
#include "../../include/Exceptions/LobbyNotFoundException.h"
#include "../../include/Exceptions/NewLobbyNotifiedTwiceException.h"
#include "../../include/GTKNotifications/LeftLobbyGTKNotification.h"
#include "../../GTKmm/GTKmmRunner.h"
#include "../../include/GTKNotifications/PlayerLeftJoinedLobbyGTKNotification.h"
#include "../../include/GTKNotifications/LogInSuccessGtkNotification.h"
#include "../../include/GTKNotifications/PickSpellGTKNotification.h"
#include "../../../Server/include/Lobbies/Lobby.h"
#include "../../include/GTKNotifications/LobbyPickedMapGTKNotification.h"
#include "../../include/GTKNotifications/PlayerIsReadyGTKNotification.h"


ClientLobbyManager::ClientLobbyManager(SocketWrapper& _sock, GTKmmRunner& runner)
: _sock(_sock), _lobbies(), fireHUDEnabled(false), waterHUDEnabled(false),
 airHUDEnabled(false),  groundHUDEnabled(false),
  _otherPlayers(), maps(), _runner(runner), joinedLobby(nullptr) {

}

ClientLobbyManager::~ClientLobbyManager(){
    for (auto it = _lobbies.begin(); it != _lobbies.end(); ++it){
        delete (*it);
    }
    for (auto it = _otherPlayers.begin(); it != _otherPlayers.end(); ++it){
        delete (*it);
    }
}


void ClientLobbyManager::HandleLobbyJoin(){
    uint32_t lobbyGuid = _sock.RecieveInt32();
    std::cout << "LOBBY JOINED: " << lobbyGuid << "\n" << std::flush;
    joinedLobby = GetLobby(lobbyGuid);



    uint32_t firepguid = _sock.RecieveInt32();
    if (firepguid > 0){
        uint8_t ready = _sock.RecieveByte();// espero 0 o 1
        if (firepguid != myGuid)
            (*GetOtherPlayer(firepguid))->ready = ready;
        joinedLobby->PlayerPickSpell(firepguid, SPELL_TYPE_FIRE, false);
    }

    uint32_t waterpguid = _sock.RecieveInt32();
    if (waterpguid > 0){
        uint8_t ready = _sock.RecieveByte();// espero 0 o 1
        if (waterpguid != myGuid)
            (*GetOtherPlayer(waterpguid))->ready = ready;
        joinedLobby->PlayerPickSpell(waterpguid, SPELL_TYPE_WATER, false);
    }

    uint32_t airpguid = _sock.RecieveInt32();
    if (airpguid > 0){
        uint8_t ready = _sock.RecieveByte();// espero 0 o 1
        if (airpguid != myGuid)
            (*GetOtherPlayer(airpguid))->ready = ready;
        joinedLobby->PlayerPickSpell(airpguid, SPELL_TYPE_AIR, false);
    }

    uint32_t groundpguid = _sock.RecieveInt32();
    if (groundpguid > 0){
        uint8_t ready = _sock.RecieveByte();// espero 0 o 1
        if (groundpguid != myGuid)
            (*GetOtherPlayer(groundpguid))->ready = ready;
        joinedLobby->PlayerPickSpell(groundpguid, SPELL_TYPE_GROUND, false);
    }



    _runner.gtkNotifications.Queue(new JoinedLobbyGUINotification(*joinedLobby));
    g_idle_add(GTKmmRunner::notification_check, &_runner);
}

void ClientLobbyManager::HandlePlayerJoin(){
    uint32_t pguid = _sock.RecieveInt32();
    std::string pname = _sock.RecieveString();

    OtherPlayer* p = nullptr;
    for (auto it = _otherPlayers.begin(); it != _otherPlayers.end(); ++it){
        if ((*it)->GUID() == pguid)
            p = *it;
    }

    if (p == nullptr)
        _otherPlayers.push_back(new OtherPlayer(pname, pguid));

    std::cout << pname << ", id: " << pguid <<  " joined\n" << std::flush;
}

void ClientLobbyManager::HandlePlayerLeave(){
    try{
        uint32_t pguid = _sock.RecieveInt32();
        auto it = GetOtherPlayer(pguid);

        OtherPlayer* p = *it;
        if (p->joinedLobby != nullptr){
            p->joinedLobby->PlayerLeave(*p);
        }

        //_otherPlayers.erase(it);
        //delete *it;
    } catch (std::exception& e){

    }

}

std::vector<OtherPlayer*>::const_iterator ClientLobbyManager::GetOtherPlayer(uint32_t guid){
    bool found = false;
    for (auto it = _otherPlayers.begin(); it != _otherPlayers.end() && !found; ++it){
        OtherPlayer* p = *it;
        if (p->GUID() == guid){
            found = true;
            return it;
        }
    }
    throw PlayerNotFoundException();
}

Lobby* ClientLobbyManager::GetLobby(uint32_t guid){
    bool found = false;
    for (auto it = _lobbies.begin(); it != _lobbies.end() && !found; ++it){
        Lobby* l = *it;
        if (l->GUID() == guid){
            found = true;
            return l;
        }
    }
    throw LobbyNotFoundException();
}

void ClientLobbyManager::HandlePlayerJoinedLobby(){
    uint32_t pguid = _sock.RecieveInt32();
    uint32_t lobbyGuid = _sock.RecieveInt32();

    std::cout << "player id: " << pguid << " joined lobby id: " << lobbyGuid << '\n' << std::flush;
    Lobby* lobbyOtherPlayerJoined = GetLobby(lobbyGuid);
    auto itplayer = GetOtherPlayer(pguid);
    lobbyOtherPlayerJoined->PlayerJoin(*(*itplayer));
}

void ClientLobbyManager::HandlePlayerLeftLobby(){
    uint32_t pguid = _sock.RecieveInt32();
    uint32_t lobbyGuid = _sock.RecieveInt32();

    if (pguid == myGuid){
        joinedLobby = nullptr;
        _runner.gtkNotifications.Queue(new LeftLobbyGTKNotification());
        g_idle_add(GTKmmRunner::notification_check, &_runner);
    } else {
        Lobby* lobbyOtherPlayerLeft = GetLobby(lobbyGuid);
        auto itplayer = GetOtherPlayer(pguid);
        lobbyOtherPlayerLeft->PlayerLeave(*(*itplayer));
    }
}

void ClientLobbyManager::HandleNewLobbyNotification(){
    uint32_t lobbyGuid = _sock.RecieveInt32();
    std::string lobbyName = _sock.RecieveString();
    uint32_t pickedmapid = _sock.RecieveInt32();

    bool found = true;
    try {
        Lobby *lobby = GetLobby(lobbyGuid);
    }catch (std::exception& e){
        found = false;
    }

    if (found)
        throw NewLobbyNotifiedTwiceException();


    auto l = new Lobby(lobbyName, lobbyGuid, _runner);
    l->pickedMapId = pickedmapid;
    _lobbies.push_back(l);
	_runner.gtkNotifications.Queue(new NewLobbyGTKNotification(*(_lobbies.back())));
    g_idle_add(GTKmmRunner::notification_check, &_runner);

}

std::vector<Lobby*> ClientLobbyManager::GetLobbies(){
    return _lobbies;
}

std::string ClientLobbyManager::GetPlayerName(uint32_t guid){
    OtherPlayer* p = *(GetOtherPlayer(guid));
    return p->Name();
}


void ClientLobbyManager::HandlePickedSpell(){
    uint8_t spell = _sock.RecieveByte();
    SPELL_TYPE spelltype = (SPELL_TYPE) spell;
    joinedLobby->PlayerPickSpell(myGuid, spelltype, true);
}


void ClientLobbyManager::HandleOtherPlayerPickedSpell(){
    uint8_t spell = _sock.RecieveByte();
    uint32_t pguid = _sock.RecieveInt32();
    SPELL_TYPE spelltype = (SPELL_TYPE) spell;
    auto it = this->GetOtherPlayer(pguid);
    (*it)->joinedLobby->PlayerPickSpell(pguid, spelltype, true);
}


void ClientLobbyManager::HandleUnpickedSpell(){
    /*uint8_t spell = _sock.RecieveByte();
    SPELL_TYPE spelltype = (SPELL_TYPE) spell;


    groundHUDEnabled &= spelltype != SPELL_TYPE_GROUND;
    fireHUDEnabled &= spelltype != SPELL_TYPE_FIRE;
    waterHUDEnabled &= spelltype != SPELL_TYPE_WATER;
    airHUDEnabled &= spelltype != SPELL_TYPE_AIR;


    _runner.gtkNotifications.Queue(new PickedSpellGTKNotification(spelltype, false));
    g_idle_add(GTKmmRunner::notification_check, &_runner);*/
}

void ClientLobbyManager::HandleOtherPlayerUnpickedSpell(){
    /*
    uint8_t spell = _sock.RecieveByte();
    uint32_t pguid = _sock.RecieveInt32();
    SPELL_TYPE spelltype = (SPELL_TYPE) spell;
    auto it = this->GetOtherPlayer(pguid);
    //(*it)->joinedLobby->PlayerPickSpell(*(*it), spelltype, false);
    _runner.gtkNotifications.Queue(new OtherPickedSpellGTKNotification(*(*it), spelltype, false));
    g_idle_add(GTKmmRunner::notification_check, &_runner);*/
}

void ClientLobbyManager::HandleMapPicked() {
    uint32_t mapid = _sock.RecieveInt32();
    uint32_t lobbyid = _sock.RecieveInt32();
    Lobby* l = GetLobby(lobbyid);
    for (auto it = maps.begin(); it != maps.end(); ++it){
        std::tuple<std::string, uint32_t> tup = *it;
        if (std::get<1>(tup) == mapid){
            l->pickedMapId = mapid;
            _runner.gtkNotifications.Queue(new LobbyPickedMapGTKNotification(lobbyid, mapid));
            g_idle_add(GTKmmRunner::notification_check, &_runner);
        }
    }

}


void ClientLobbyManager::HandlePlayerReady(){
    uint32_t pguid = _sock.RecieveInt32();


    if (pguid != myGuid){
        OtherPlayer* p = *GetOtherPlayer(pguid);
        p->ready = true;
    }


    _runner.gtkNotifications.Queue(new PlayerIsReadyGTKNotification(pguid));
    g_idle_add(GTKmmRunner::notification_check, &_runner);
}


void ClientLobbyManager::HandleLoginSuccess(){
    myGuid = _sock.RecieveInt32();
    myName = _sock.RecieveString();
    mySecret = _sock.RecieveInt32();

    uint32_t lobbyCount = _sock.RecieveInt32();

    for (int i = 0; i < lobbyCount; i++){
        uint32_t lobbyGuid = _sock.RecieveInt32();
        std::string lobbyName = _sock.RecieveString();
        int32_t mapId = _sock.RecieveInt32();
        Lobby* l = new Lobby(lobbyName, lobbyGuid, _runner);
        l->pickedMapId = mapId;
        _lobbies.push_back(l);
    }

    uint32_t playerAmount = _sock.RecieveInt32();

    for (int i = 0; i < playerAmount; i++){
        uint32_t  playerGUID = _sock.RecieveInt32();
        std::string playerName = _sock.RecieveString();
        _otherPlayers.push_back(new OtherPlayer(playerName, playerGUID));
    }

    uint32_t relationsAmount = _sock.RecieveInt32();

    for (int i = 0; i < relationsAmount; i++){
        uint32_t lobbyGuid = _sock.RecieveInt32();
        uint32_t playerGuid = _sock.RecieveInt32();

        Lobby* l = GetLobby(lobbyGuid);
        auto itPlayer = GetOtherPlayer(playerGuid);

        l->PlayerJoin(*(*itPlayer));
    }


    uint32_t mapsAmount = _sock.RecieveInt32();
    for (int i = 0; i < mapsAmount; i++){
        uint32_t mapId = _sock.RecieveInt32();
        std::string mapname = _sock.RecieveString();
        auto tup = std::tuple<std::string, uint32_t>(mapname, mapId);
        maps.push_back(tup);
    }

    _runner.gtkNotifications.Queue(new LogInSuccessGtkNotification(_lobbies, myName));
    g_idle_add(GTKmmRunner::notification_check, &_runner);

    return;
}