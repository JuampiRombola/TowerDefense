
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
#include "../../GTKRunner.h"
#include "../../include/GTKNotifications/PlayerJoinedLobbyGTKNotification.h"
#include "../../include/GTKNotifications/PlayerLeftLobbyGTKNotification.h"
#include "../../include/GTKNotifications/LogInSuccessGtkNotification.h"
#include "../../include/GTKNotifications/PickedSpellGTKNotification.h"
#include "../../include/GTKNotifications/OtherPickedSpellGTKNotification.h"


ClientLobbyManager::ClientLobbyManager(SocketWrapper& _sock, GTKRunner& runner)
: _sock(_sock), _lobbies(), _otherPlayers(), _joinedLobby(nullptr), _runner(runner) {

}

ClientLobbyManager::~ClientLobbyManager(){
    for (auto it = _lobbies.begin(); it != _lobbies.end(); ++it){
        delete (*it);
    }
    for (auto it = _otherPlayers.begin(); it != _otherPlayers.end(); ++it){
        delete (*it);
    }
}

void ClientLobbyManager::HandleLeaveLobby(){
    _joinedLobby = nullptr;
    _runner.gtkNotifications.Queue(new LeftLobbyGTKNotification());
}

void ClientLobbyManager::HandleLobbyJoin(){
    uint32_t lobbyGuid = -1;
    _sock.Recieve((char*)&lobbyGuid, 4);
    _joinedLobby = GetLobby(lobbyGuid);


    uint32_t firepguid;
    _sock.Recieve((char*) &firepguid, 4);
    if (firepguid > 0){
        auto it = GetOtherPlayer(firepguid);
        OtherPlayer* p = *it;
        _joinedLobby->PlayerPickSpell(*p, SPELL_TYPE_FIRE, true);
    }
    
    uint32_t waterpguid;
    _sock.Recieve((char*) &waterpguid, 4);
    if (waterpguid > 0){
        auto it = GetOtherPlayer(waterpguid);
        OtherPlayer* p = *it;
        _joinedLobby->PlayerPickSpell(*p, SPELL_TYPE_WATER, true);
    }
    
    uint32_t airpguid;
    _sock.Recieve((char*) &airpguid, 4);
    if (airpguid > 0){
        auto it = GetOtherPlayer(airpguid);
        OtherPlayer* p = *it;
        _joinedLobby->PlayerPickSpell(*p, SPELL_TYPE_AIR, true);
    }
    
    uint32_t groundpguid;
    _sock.Recieve((char*) &groundpguid, 4);
    if (groundpguid > 0){
        auto it = GetOtherPlayer(groundpguid);
        OtherPlayer* p = *it;
        _joinedLobby->PlayerPickSpell(*p, SPELL_TYPE_GROUND, true);
    }    
    
    _runner.gtkNotifications.Queue(new JoinedLobbyGUINotification(*_joinedLobby));
}

void ClientLobbyManager::HandlePlayerJoin(){
    uint32_t pguid = -1;
    _sock.Recieve((char*) &pguid, 4);
    std::string pname = _sock.RecieveString();
    _otherPlayers.push_back(new OtherPlayer(pname, pguid));
    std::cout << pname << ", id: " << pguid <<  " joined\n" << std::flush;
}

void ClientLobbyManager::HandlePlayerLeave(){
    uint32_t pguid = -1;
    _sock.Recieve((char*) &pguid, 4);
    auto it = GetOtherPlayer(pguid);

    OtherPlayer* p = *it;
    if (p->joinedLobby != nullptr){
        p->joinedLobby->PlayerLeave(*p);
    }

    _otherPlayers.erase(it);
    delete *it;
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
    uint32_t pguid = -1;
    _sock.Recieve((char*) &pguid, 4);
    uint32_t lobbyGuid = -1;
    _sock.Recieve((char*)&lobbyGuid, 4);

    std::cout << "player id: " << pguid << " joined lobby id: " << lobbyGuid << '\n' << std::flush;
    Lobby* lobbyOtherPlayerJoined = GetLobby(lobbyGuid);
    auto itplayer = GetOtherPlayer(pguid);
    lobbyOtherPlayerJoined->PlayerJoin(*(*itplayer));
    if (_joinedLobby == lobbyOtherPlayerJoined)
        _runner.gtkNotifications.Queue(new PlayerJoinedLobbyGTKNotification(*(*itplayer)));

}

void ClientLobbyManager::HandlePlayerLeftLobby(){
    uint32_t pguid = -1;
    _sock.Recieve((char*) &pguid, 4);
    uint32_t lobbyGuid = -1;
    _sock.Recieve((char*)&lobbyGuid, 4);

    Lobby* lobbyOtherPlayerLeft = GetLobby(lobbyGuid);
    auto itplayer = GetOtherPlayer(pguid);
    lobbyOtherPlayerLeft->PlayerLeave(*(*itplayer));
    if (_joinedLobby == lobbyOtherPlayerLeft)
        _runner.gtkNotifications.Queue(new PlayerLeftLobbyGTKNotification(*(*itplayer)));
}

void ClientLobbyManager::HandleNewLobbyNotification(){
	uint32_t lobbyGuid = -1;
	_sock.Recieve((char*)&lobbyGuid, 4);
	std::string lobbyName = _sock.RecieveString();

    bool found = true;
    try {
        Lobby *lobby = GetLobby(lobbyGuid);
    }catch (std::exception& e){
        found = false;
    }

    if (found)
        throw NewLobbyNotifiedTwiceException();

    _lobbies.push_back(new Lobby(lobbyName, lobbyGuid));
	_runner.gtkNotifications.Queue(new NewLobbyGTKNotification(*(_lobbies.back())));

}

std::vector<Lobby*> ClientLobbyManager::GetLobbies(){
    return _lobbies;
}



void ClientLobbyManager::HandlePickedSpell(){
    uint8_t spell;
    _sock.Recieve((char*) &spell, 1);
    SPELL_TYPE spelltype = (SPELL_TYPE) spell;
    _runner.gtkNotifications.Queue(new PickedSpellGTKNotification(spelltype, true));
}

void ClientLobbyManager::HandleUnpickedSpell(){
    uint8_t spell;
    _sock.Recieve((char*) &spell, 1);
    SPELL_TYPE spelltype = (SPELL_TYPE) spell;
    _runner.gtkNotifications.Queue(new PickedSpellGTKNotification(spelltype, false));
}

void ClientLobbyManager::HandleOtherPlayerPickedSpell(){
    uint8_t spell;
    _sock.Recieve((char*) &spell, 1);
    uint32_t pguid;
    _sock.Recieve((char*) &pguid, 4);
    SPELL_TYPE spelltype = (SPELL_TYPE) spell;
    auto it = this->GetOtherPlayer(pguid);
    (*it)->joinedLobby->PlayerPickSpell(*(*it), spelltype, true);
    _runner.gtkNotifications.Queue(new OtherPickedSpellGTKNotification(*(*it), spelltype, true));
}

void ClientLobbyManager::HandleOtherPlayerUnpickedSpell(){
    uint8_t spell;
    _sock.Recieve((char*) &spell, 1);
    uint32_t pguid;
    _sock.Recieve((char*) &pguid, 4);
    SPELL_TYPE spelltype = (SPELL_TYPE) spell;
    auto it = this->GetOtherPlayer(pguid);
    (*it)->joinedLobby->PlayerPickSpell(*(*it), spelltype, false);
    _runner.gtkNotifications.Queue(new OtherPickedSpellGTKNotification(*(*it), spelltype, false));
}

void ClientLobbyManager::HandleLoginSuccess(){

    uint32_t lobbyCount = -1;
    _sock.Recieve((char*) &lobbyCount, 4);

    for (int i = 0; i < lobbyCount; i++){
        uint32_t lobbyGuid = -1;
        _sock.Recieve((char*) &lobbyGuid, 4);
        std::string lobbyName = _sock.RecieveString();
        _lobbies.push_back(new Lobby(lobbyName, lobbyGuid));
        _runner.gtkNotifications.Queue(new NewLobbyGTKNotification(*(_lobbies.back())));
    }

    uint32_t playerAmount = -1;
    _sock.Recieve((char*) &playerAmount, 4);

    for (int i = 0; i < playerAmount; i++){
        uint32_t  playerGUID = -1;
        _sock.Recieve((char*) &playerGUID, 4);
        std::string playerName = _sock.RecieveString();
        _otherPlayers.push_back(new OtherPlayer(playerName, playerGUID));
    }

    uint32_t relationsAmount = -1;
    _sock.Recieve((char*) &relationsAmount, 4);

    for (int i = 0; i < relationsAmount; i++){
        uint32_t lobbyGuid = -1;
        uint32_t playerGuid = -1;
        _sock.Recieve((char*) &lobbyGuid, 4);
        _sock.Recieve((char*) &playerGuid, 4);

        Lobby* l = GetLobby(lobbyGuid);
        auto itPlayer = GetOtherPlayer(playerGuid);

        l->PlayerJoin(*(*itPlayer));
    }

    _runner.gtkNotifications.Queue(new LogInSuccessGtkNotification(_lobbies));
}