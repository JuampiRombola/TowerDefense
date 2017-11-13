#ifndef __LOBBY__
#define __LOBBY__

#include <string>
#include <mutex>
#include "Lobby.h"
#include "../PlayerProxy.h"
#include "../ThreadSafeQueue.h"
#include "../Notifications/Notification.h"

class Lobby 
{
private:
	std::mutex _playersMutex;
	std::mutex _playerSpellsSlotsMutex;
	std::mutex _readyPlayersMutex;
	std::mutex _gameEnabledMutex;
	uint _guid;
	std::string _name;
	std::vector<PlayerProxy*> _players;	
	ThreadSafeQueue<Notification*>& _notifications;
	PlayerProxy* _firePlayer;
	PlayerProxy* _airPlayer;
	PlayerProxy* _groundPlayer;
	PlayerProxy* _waterPlayer;
    std::vector<PlayerProxy*> _readyPlayers;
    std::vector<PlayerProxy*> _playingPlayers;
	bool _gameEnabled;

public:
	Lobby(std::string name, uint guid, ThreadSafeQueue<Notification*>& notifications);
	~Lobby();
	std::vector<int> GetPlayersGUIDS();
	std::vector<PlayerProxy*> GetOtherPlayersInLobby();
	std::string Name();
	uint GUID();
	bool PlayerJoin(PlayerProxy& player);
	void PlayerLeave(PlayerProxy& player);
	void PlayerIsReady(PlayerProxy& player);
	void PlayerPickFire(PlayerProxy& player);
	void PlayerPickWater(PlayerProxy& player);
	void PlayerPickAir(PlayerProxy& player);
	void PlayerPickGround(PlayerProxy& player);
	void PlayerUnpickFire(PlayerProxy& player);
	void PlayerUnpickWater(PlayerProxy& player);
	void PlayerUnpickAir(PlayerProxy& player);
	void PlayerUnpickGround(PlayerProxy& player);

	//Devuelve 0 si nadie eligio fuego.
	uint32_t GetFirePlayerID();
	uint32_t GetWaterPlayerID();
	uint32_t GetAirPlayerID();
	uint32_t GetGroundPlayerID();

	bool GameEnabled();

    std::vector<PlayerProxy*> GetPlayersInLobbyWithSomeSpellSet();
    std::vector<PlayerProxy*> GetPlayingPlayers();

};

#endif
