#ifndef __CLIENT_LOBBY_MANAGER__
#define __CLIENT_LOBBY_MANAGER__

#include <vector>
#include <string>
#include <mutex>
#include <iostream>

#include "Lobby.h"
#include "../../../Common/SocketWrapper.h"

class GTKmmRunner;

class ClientLobbyManager{
private:
	SocketWrapper& _sock;
	std::vector<Lobby*> _lobbies;
	std::vector<OtherPlayer*> _otherPlayers;
	GTKmmRunner& _runner;


	std::vector<OtherPlayer*>::const_iterator  GetOtherPlayer(uint32_t guid);
	Lobby* GetLobby(uint32_t guid);
public:
	ClientLobbyManager(SocketWrapper& sock, GTKmmRunner& GtkRunner);
	~ClientLobbyManager();
	void HandleNewLobbyNotification();
	void HandleLobbyJoin();
	void HandlePlayerLeftLobby();
	void HandlePlayerJoinedLobby();
	void HandlePlayerJoin();
	void HandlePlayerLeave();
	void HandleLoginSuccess();
    void HandlePlayerReady();

    void HandlePickedSpell();
	void HandleUnpickedSpell();
	void HandleOtherPlayerPickedSpell();
	void HandleOtherPlayerUnpickedSpell();
	void HandleMapPicked();

	std::vector<Lobby*> GetLobbies();
	std::string GetPlayerName(uint32_t guid);
	bool fireHUDEnabled;
	bool waterHUDEnabled;
	bool airHUDEnabled;
	bool groundHUDEnabled;
	std::string myName;
	uint32_t myGuid;
	uint32_t mySecret;
	std::vector<std::tuple<std::string, uint32_t>> maps;
	Lobby* joinedLobby;

};

#endif