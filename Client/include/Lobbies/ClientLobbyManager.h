#ifndef __CLIENT_LOBBY_MANAGER__
#define __CLIENT_LOBBY_MANAGER__

#include <vector>
#include <string>
#include <mutex>
#include <iostream>

#include "Lobby.h"
#include "../../../Common/SocketWrapper.h"

class GTKRunner;

class ClientLobbyManager{
private:
	SocketWrapper& _sock;
	std::vector<Lobby*> _lobbies;
	std::vector<OtherPlayer*> _otherPlayers;
	GTKRunner& _runner;
	Lobby* _joinedLobby;


	std::vector<OtherPlayer*>::const_iterator  GetOtherPlayer(uint32_t guid);
	Lobby* GetLobby(uint32_t guid);
public:
	ClientLobbyManager(SocketWrapper& sock, GTKRunner& GtkRunner);
	~ClientLobbyManager();
	void HandleNewLobbyNotification();
	void HandleLobbyJoin();
	void HandlePlayerLeftLobby();
	void HandlePlayerJoinedLobby();
	void HandleLeaveLobby();
	void HandlePlayerJoin();
	void HandlePlayerLeave();
	void HandleLoginSuccess();

	void HandlePickedSpell();
	void HandleUnpickedSpell();
	void HandleOtherPlayerPickedSpell();
	void HandleOtherPlayerUnpickedSpell();

	std::vector<Lobby*> GetLobbies();
};

#endif