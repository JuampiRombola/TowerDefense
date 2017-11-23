#include "../include/NotificationReciever.h"
#include "../GTKRunner.h"
#include "../include/GTKNotifications/LogInSuccessGtkNotification.h"
#include "../include/GTKNotifications/LogInFailedGtkNotification.h"
#include "../include/GTKNotifications/GameStartedGTKNotification.h"
#include "../View/Common/SpriteNamesConfig.h"
#include "../include/NetCommands/PlayerLoadedGameCommand.h"

NotificationReciever::NotificationReciever(SocketWrapper& socket, ClientLobbyManager& lobbyManager, GTKRunner& runner, CommandDispatcher& dispatcher)
: _sock(socket), _lobbyManager(lobbyManager),  _runner(runner), _dispatcher(dispatcher), _stop(false), _towerCoordToId() {

}

NotificationReciever::~NotificationReciever(){
	this->Stop();
	if (_thread.joinable())
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
			case PICK_MAP:
				std::cout << "PICK_MAP::\n" << std::flush;
				_lobbyManager.HandleMapPicked();
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
				g_idle_add(GTKRunner::notification_check, &_runner);
				break;
			case GAME_STARTED:
				std::cout << "GAME_STARTED::\n" << std::flush;
				uint32_t width;
				uint32_t height;
				uint8_t superficie;
				_sock.Recieve((char*)&superficie, 1);
				_sock.Recieve((char*)&width, 4);
				_sock.Recieve((char*)&height, 4);

				_runner.gtkNotifications.Queue(new GameStartedGTKNotification(superficie, width, height));
				g_idle_add(GTKRunner::notification_check, &_runner);
				break;
			case GAME_OPCODE:
				std::cout << "GAME_OPCODE::\n" << std::flush;
				_HandleGameOpcode();
				break;
			case GAME_MODEL_STARTED_RUNNING:
				_dispatcher.Enable();
				break;
			case LOAD_MAP:
				std::cout << "LOAD_MAP::\n" << std::flush;
				uint8_t op;
				_sock.Recieve((char*) &op, 1);
				uint8_t x;
				uint8_t y;
				_sock.Recieve((char*) &x, 4);
				_sock.Recieve((char*) &y, 4);
				if (op == PATH_TILE)
					model_view->createPathTile(x, y);
				if (op == STRUCTURE_TILE)
					model_view->createStructureTile(x, y);
				if (op == SPAWN_TILE)
					model_view->createPortalEntrada(x, y);
				if (op == FINISH_TILE)
					model_view->createPortalSalida(x, y);
				break;
			case MAP_FINISHED_LOADING:
				{
					std::lock_guard<std::mutex> lock(model_view->mapLoadedMutex);
					model_view->mapLoaded = true;
					model_view->mapLoadedCondVariable.notify_one();
					_dispatcher.QueueCommand(new PlayerLoadedGameCommand());
					_dispatcher.Disable();
                    model_view->addAnnouncement("Bienvenido a Tower Defense!");
                }
				break;
			case IN_GAME_CHAT_MESSAGE:
			{
				uint32_t pguid;
				_sock.Recieve((char*) &pguid, 4);
				std::string message = _sock.RecieveString();

                if (pguid == _lobbyManager.myGuid){
                    chat_view->MessageFrom(message, _lobbyManager.myName);
                } else {
                    std::string playerName = _lobbyManager.GetPlayerName(pguid);
                    chat_view->MessageFrom(message, playerName);
                }
				break;
			}

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
			std::cout << "TOWER_PLACED::\n" << std::flush;
			_HandleTowerPlaced();
			break;
		case UNIT_POSITION_UPDATE:
			std::cout << "UNIT_POSITION_UPDATE::\n" << std::flush;
			_HandleUnitPositionUpdate();
			break;
        case UNIT_CREATED:
			std::cout << "UNIT_CREATED::\n" << std::flush;
			_HandleUnitCreated();
            break;
        case PROJECTILE_FIRED:
			std::cout << "PROJECTILE_FIRED::\n" << std::flush;
			_HandleProjectileFired();
            break;
		case GAME_OVER:
            model_view->addAnnouncement("Defeat!");
            std::this_thread::sleep_for (std::chrono::milliseconds(3000));
            std::cout << "GAME_OVER::\n" << std::flush;
			this->Stop();
            break;
        case GAME_WON:
            model_view->addAnnouncement("Victory!");
            std::this_thread::sleep_for (std::chrono::milliseconds(3000));
            std::cout << "GAME_WON::\n" << std::flush;
            this->Stop();
            break;
        case UNIT_DIED:
			std::cout << "UNIT_DIED::\n" << std::flush;
			uint32_t unitid;
			_sock.Recieve((char *) &unitid, 4);
			model_view->killUnit(unitid);
			break;
		case CLIENT_CAST_SPELL:
			std::cout << "CLIENT_CAST_SPELL::\n" << std::flush;
			_HandleSpellCasted();
			break;
		case HORDE_STARTED:
			std::cout << "HORDE_STARTED::\n" << std::flush;
			_HandleHordeStarted();
			break;
		case HORDE_ENDED:
			std::cout << "HORDE_ENDED::\n" << std::flush;
			_HandleHordeEnded();
			break;
		case TOWER_GAINED_EXP:
			std::cout << "TOWER_GAINED_EXP::\n" << std::flush;
			_HandleTowerGainedExperience();
			break;
        case TOWER_UPGRADE:
            std::cout << "TOWER_UPGRADE::\n" << std::flush;
            _HandleTowerUpgrade();
            break;
    }
}

void NotificationReciever::_HandleTowerGainedExperience() {
	uint32_t x;
	uint32_t y;
	uint32_t exp;
	_sock.Recieve((char*)&x, 4);
	_sock.Recieve((char*)&y, 4);
	_sock.Recieve((char*)&exp, 4);

	std::cout << "Tower @(" << x << ", " << y << ") now has "
			  << exp << "xp\n" <<std::flush;

	uint towerid = _towerCoordToId[std::pair<uint, uint>(x, y)];


}

void NotificationReciever::_HandleTowerUpgrade() {
    uint32_t x;
    uint32_t y;
    uint32_t damage;
    uint32_t range;
    uint32_t projectile_ms_over_tile;
    uint32_t level;

    _sock.Recieve((char*) &x, 4);
    _sock.Recieve((char*) &y, 4);
	
	uint towerId = _towerCoordToId[std::pair<uint, uint>(x, y)];
	
    _sock.Recieve((char*) &damage, 4);
    _sock.Recieve((char*) &range, 4);
    _sock.Recieve((char*) &projectile_ms_over_tile, 4);
    _sock.Recieve((char*) &level, 4);
	uint8_t type = -1;
    _sock.Recieve((char*) &type, 1);
    switch (type){
        case SPELL_TYPE_FIRE:
            uint32_t collateral_damage;
            uint32_t collateral_range;
            _sock.Recieve((char*)&collateral_damage, 4);
            _sock.Recieve((char*)&collateral_range, 4);
            break;
        case SPELL_TYPE_WATER:
            uint32_t slow_seconds;
            uint32_t slow_percent;
            _sock.Recieve((char*)&slow_seconds, 4);
            _sock.Recieve((char*)&slow_percent, 4);
            break;
        case SPELL_TYPE_AIR:
            uint32_t nonFlyingDamage;
            _sock.Recieve((char*) &nonFlyingDamage, 4);
            break;
        case SPELL_TYPE_GROUND:
            break;
    }
}

void NotificationReciever::_HandleHordeEnded() {
	uint hordeId;
	_sock.Recieve((char*) &hordeId, 4);
	std::string s = "Horda " +  std::to_string(hordeId) + " superada!";
	model_view->addAnnouncement(s);
}
void NotificationReciever::_HandleHordeStarted() {
	uint hordeId;
	_sock.Recieve((char*) &hordeId, 4);
	std::string s = "Horda " +  std::to_string(hordeId) + " ha empezado!";
	model_view->addAnnouncement(s);
}

void NotificationReciever::_HandleSpellCasted(){
	uint8_t spell;
	_sock.Recieve((char *) &spell, 1);
	uint32_t x;
	_sock.Recieve((char *) &x, 4);
	uint32_t y;
	_sock.Recieve((char *) &y, 4);
    uint32_t duration_ms;
    _sock.Recieve((char *) &duration_ms, 4);
    uint32_t cooldown_ms;
    _sock.Recieve((char *) &cooldown_ms, 4);
	switch(spell){
		case SPELL_TERRAFORMING:
			model_view->createStructureTile(x, y);
			break;
		case SPELL_METEORITO:
			model_view->createSpell(METEORITO, x, y, duration_ms);
			break;
		case SPELL_VENTISCA:
			model_view->createSpell(VENTISCA, x, y, duration_ms);
			break;
		case SPELL_CONGELACION:
			model_view->createSpell(CONGELACION, x, y, duration_ms);
			break;
		case SPELL_TORNADO:
			model_view->createSpell(TORNADO, x, y, duration_ms);
			break;
		case SPELL_RAYO:
			model_view->createSpell(RAYO, x, y, duration_ms);
			break;
		case SPELL_FIREWALL:
			model_view->createSpell(FIREWALL, x, y, duration_ms);
			break;
		case SPELL_GRIETA:
			model_view->createSpell(GRIETA, x, y, duration_ms);
			break;
		case SPELL_PING:
			model_view->createSpell(PING, x, y, duration_ms);
			break;
	}
}


void NotificationReciever::_HandleProjectileFired(){
	uint32_t x;
	_sock.Recieve((char *) &x, 4);
	uint32_t y;
	_sock.Recieve((char *) &y, 4);
	uint32_t tox;
	_sock.Recieve((char *) &tox, 4);
	uint32_t toy;
	_sock.Recieve((char *) &toy, 4);
	uint32_t delay_ms;
	_sock.Recieve((char *) &delay_ms, 4);
	uint8_t spelltype;
	_sock.Recieve((char*) &spelltype, 1);
	switch(spelltype){
		case SPELL_TYPE_WATER:
			model_view->createShot(DISPARO_AGUA, x, y, tox, toy, delay_ms);
			break;
		case SPELL_TYPE_GROUND:
			model_view->createShot(DISPARO_TIERRA, x, y, tox, toy, delay_ms);
			break;
		case SPELL_TYPE_FIRE:
			model_view->createShot(DISPARO_FUEGO, x, y, tox, toy, delay_ms);
			break;
		case SPELL_TYPE_AIR:
			model_view->createShot(DISPARO_AIRE, x, y, tox, toy, delay_ms);
			break;
	}
}
void NotificationReciever::_HandleTowerPlaced(){
    static int towerID = 1;
	uint32_t x;
	_sock.Recieve((char *) &x, 4);
	uint32_t y;
	_sock.Recieve((char *) &y, 4);
	uint8_t type = -1;
	_sock.Recieve((char *) &type, 1);
	_towerCoordToId[std::pair<uint, uint>(x, y)] = towerID;
    switch (type) {
        case SPELL_TYPE_GROUND:
            model_view->createTower(towerID++, TORRE_TIERRA , x, y);
            break;
        case SPELL_TYPE_FIRE:
            model_view->createTower(towerID++, TORRE_FUEGO , x, y);
            break;
        case SPELL_TYPE_WATER:
            model_view->createTower(towerID++, TORRE_AGUA , x, y);
            break;
        case SPELL_TYPE_AIR:
            model_view->createTower(towerID++, TORRE_AIRE, x, y);
            break;
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

	std::cout << "unit move x: " << x << ", y: " << y << ", to x: " << tox << ", toy: " << toy <<'\n' <<std::flush;
	if (tox == 0xFFFFFFFF || toy == 0xFFFFFFFF)
		return;

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
	std::cout << "unit created x: " << x << ", y: " << y << ", to x: " << tox << ", toy: " << toy <<'\n' <<std::flush;
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

bool NotificationReciever::Running(){
	std::lock_guard<std::mutex> lock(_stopMutex);
	return !_stop;
}


void NotificationReciever::Stop(){
	std::lock_guard<std::mutex> lock(_stopMutex);
	_stop = true;
}