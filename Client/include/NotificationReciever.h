#ifndef __NOTIFICATION_RECIEVER__
#define __NOTIFICATION_RECIEVER__

#include <mutex>
#include <thread>
#include <iostream>
#include "../../Common/SocketWrapper.h"
#include "../../Common/Protocolo.h"
#include "Lobbies/ClientLobbyManager.h"
#include "SDLNotifications/SDLNotification.h"
#include "NonBlockingThreadSafeQueue.h"
#include "../View/Model/ModelView.h"
#include "NetCommands/CommandDispatcher.h"
#include "../View/Model/ChatView.h"
#include "../View/Model/HudView.h"

class NotificationReciever : public std::thread
{
private:
	std::mutex _stopMutex;
	SocketWrapper& _sock;
	ClientLobbyManager& _lobbyManager;
	std::thread _thread;
	GTKmmRunner& _runner;
	CommandDispatcher& _dispatcher;
	bool _stop;
	bool _Stop();
	void _HandleGameOpcode();
	void _HandleTowerPlaced();
    void _HandleUnitPositionUpdate();
    void _HandleUnitCreated();
	void _HandleProjectileFired();
	void _HandleSpellCasted();
	void _HandleTowerGainedExperience();
	void _HandleHordeStarted();
    void _HandleTowerUpgrade();
    void _HandleHordeEnded();
	void _HandleUnitSpeedUpdate();
	void _HandleUnitFrozen();
	void _SwitchOnOpcode(uint8_t opcode);


	std::map<std::pair<uint, uint>, uint> _towerCoordToId;
	uint _localTowerId;
public:
	NotificationReciever(SocketWrapper& socket,
						 ClientLobbyManager& lobbyManager, GTKmmRunner& runner,
						 CommandDispatcher& dispatcher);
	~NotificationReciever();
	void RecieveNotifications();
	void Run();
	void Stop();
	bool Running();
	ModelView *model_view;
	ChatView *chat_view;
	HudView *hud_view;
};
#endif