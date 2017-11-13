#include "../include/NotificationReciever.h"
#include "../GTKRunner.h"
#include "../include/GTKNotifications/LogInSuccessGtkNotification.h"
#include "../include/GTKNotifications/LogInFailedGtkNotification.h"
#include "../include/GTKNotifications/GameStartedGTKNotification.h"
#include "../View/Common/SpriteNamesConfig.h"


NotificationReciever::NotificationReciever(SocketWrapper& socket, ClientLobbyManager& lobbyManager, GTKRunner& runner)
: _sock(socket), _lobbyManager(lobbyManager),  _runner(runner), _stop(false) {
	
}

NotificationReciever::~NotificationReciever(){
	Stop();
	_thread.join();
}

void NotificationReciever::Run(){
	_thread = std::thread(&NotificationReciever::RecieveNotifications, this);
}

void NotificationReciever::RecieveNotifications(){
	uint8_t opcode;
	while (!_Stop()){
		std::cout << " CHECK \n" << std::flush;
		_sock.Recieve((char*) &opcode, 1);
		std::cout << " RUN \n" << std::flush;
		switch (opcode){
			case CREATE_LOBBY:
				std::cout << "CREATE_LOBBY::\n" << std::flush;
				_lobbyManager.HandleNewLobbyNotification();
				break;
			case JOIN_LOBBY:
				std::cout << "JOIN_LOBBY::\n" << std::flush;
				_lobbyManager.HandleLobbyJoin();
				break;
			case LEAVE_LOBBY:
				std::cout << "LEAVE_LOBBY::\n" << std::flush;
				_lobbyManager.HandleLeaveLobby();
				break;
			case PLAYER_LEFT_LOBBY:
				std::cout << "PLAYER_LEFT_LOBBY::\n" << std::flush;
				_lobbyManager.HandlePlayerLeftLobby();
				break;
			case PLAYER_JOINED_LOBBY:
				std::cout << "PLAYER_JOINED_LOBBY::\n" << std::flush;
				_lobbyManager.HandlePlayerJoinedLobby();
				break;
			case PLAYER_JOIN:
				std::cout << "PLAYER_JOIN::\n" << std::flush;
				_lobbyManager.HandlePlayerJoin();
				break;
			case PLAYER_LEAVE:
				std::cout << "PLAYER_LEAVE::\n" << std::flush;
				_lobbyManager.HandlePlayerLeave();
				break;
			case LOG_IN_SUCCESS:
				std::cout << "LOG_IN_SUCCESS::\n" << std::flush;
				_lobbyManager.HandleLoginSuccess();
				break;
			case PICK_SPELL:
				std::cout << "PICK_SPELL::\n" << std::flush;
				_lobbyManager.HandlePickedSpell();
				break;
			case UNPICK_SPELL:
				std::cout << "UNPICK_SPELL::\n" << std::flush;
				_lobbyManager.HandleUnpickedSpell();
				break;
			case PLAYER_PICKED_SPELL:
				std::cout << "PLAYER_PICKED_SPELL::\n" << std::flush;
				_lobbyManager.HandleOtherPlayerPickedSpell();
				break;
			case PLAYER_UNPICKED_SPELL:
				std::cout << "PLAYER_UNPICKED_SPELL::\n" << std::flush;
				_lobbyManager.HandleOtherPlayerUnpickedSpell();
				break;
			case LOG_IN_FAILED:
                _runner.gtkNotifications.Queue(new LogInFailedGtkNotification());
				break;
			case GAME_STARTED:
				std::cout << "GAME_STARTED::\n" << std::flush;
				_runner.gtkNotifications.Queue(new GameStartedGTKNotification());
				break;
			case GAME_OPCODE:
				std::cout << "GAME_OPCODE::\n" << std::flush;
				_HandleGameOpcode();
			default:
				std::cout << "UNKNOWN OPCODE RECIEVED: '" << opcode << ", ( " << (int) opcode << ")\'" << std::flush;
		}
		std::cout << " OUT \n" << std::flush;
	}

}


void NotificationReciever::_HandleGameOpcode(){
	uint8_t opcode;
	_sock.Recieve((char*) &opcode, 1);
	switch (opcode) {
		case TOWER_PLACED:
			_HandleTowerPlaced();
			break;
		case UNIT_POSITION_UPDATE:
			_HandleUnitPositionUpdate();
			break;
        case UNIT_CREATED:
            _HandleUnitCreated();
            break;
    }
}


void NotificationReciever::_HandleTowerPlaced(){
	uint32_t x;
	_sock.Recieve((char *) &x, 4);
	uint32_t y;
	_sock.Recieve((char *) &y, 4);
	SPELL_TYPE type;
	_sock.Recieve((char *) &type, 1);
	switch(type){
		case SPELL_TYPE_FIRE:
			model_view->createTower(990, TORRE_FUEGO, x, y);
		case SPELL_TYPE_WATER:
            model_view->createTower(990, TORRE_AGUA, x, y);
		case SPELL_TYPE_AIR:
            model_view->createTower(990, TORRE_AIRE, x, y);
		case SPELL_TYPE_GROUND:
            model_view->createTower(990, TORRE_TIERRA, x, y);
	}
}
void NotificationReciever::_HandleUnitPositionUpdate(){
    uint32_t unitID;
    _sock.Recieve((char *) &unitID, 4);
    uint32_t x;
    _sock.Recieve((char *) &x, 4);
    uint32_t y;
    _sock.Recieve((char *) &y, 4);
    uint32_t tox;
    _sock.Recieve((char *) &tox, 4);
    uint32_t toy;
    _sock.Recieve((char *) &toy, 4);
    uint32_t delay_ms ;
    _sock.Recieve((char *) &delay_ms, 4);
    model_view->moveUnit(unitID, x, y, tox, toy, delay_ms);
}
void NotificationReciever::_HandleUnitCreated(){
    uint32_t unitID;
    _sock.Recieve((char *) &unitID, 4);
    uint32_t x;
    _sock.Recieve((char *) &x, 4);
    uint32_t y;
    _sock.Recieve((char *) &y, 4);
    uint32_t tox;
    _sock.Recieve((char *) &tox, 4);
    uint32_t toy;
    _sock.Recieve((char *) &toy, 4);
    uint32_t delay_ms ;
    _sock.Recieve((char *) &delay_ms, 4);
    uint8_t unittype;
    _sock.Recieve((char *) &unittype, 1);
    UNIT_TYPE type = (UNIT_TYPE) unittype;
    switch(type){
        case UNIT_TYPE_Abmonible:
            model_view->createUnit(unitID, ABOMINABLE, x, y, tox, toy, delay_ms);
            break;
        case UNIT_TYPE_NoMuerto:
            model_view->createUnit(unitID, NOMUERTO, x, y, tox, toy, delay_ms);
            break;
        case UNIT_TYPE_HalconSangriento:
            model_view->createUnit(unitID, HALCONSANGRIENTO, x, y, tox, toy, delay_ms);
            break;
        case UNIT_TYPE_HombreCabra:
            model_view->createUnit(unitID, HOMBRECABRA, x, y, tox, toy, delay_ms);
            break;
        case UNIT_TYPE_DemonioVerde:
            model_view->createUnit(unitID, DEMONIOVERDE, x, y, tox, toy, delay_ms);
            break;
        case UNIT_TYPE_Espectro:
            model_view->createUnit(unitID, ESPECTRO, x, y, tox, toy, delay_ms);
            break;
    }
}


bool NotificationReciever::_Stop(){
	std::lock_guard<std::mutex> lock(_stopMutex);
	return _stop;
}




void NotificationReciever::Stop(){
	std::lock_guard<std::mutex> lock(_stopMutex);
	_stop = true;
}