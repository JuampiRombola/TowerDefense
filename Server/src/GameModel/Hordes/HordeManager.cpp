//
// Created by tino on 21/11/17.
//

#include "../../../include/GameModel/Hordes/HordeManager.h"
#include "../../../include/GameModel/TowerDefenseGame.h"
#include "../../../include/GameModel/GameNotifications/HordeUpdateGameNotification.h"


HordeManager::HordeManager(Configuration& mapCfg)
        : _hordes(), _timeStamp(0), _currentHorde(nullptr) {

    int i = 1;
	for (YAML::const_iterator it = mapCfg.Cfg["hordas"].begin();
		 it != mapCfg.Cfg["hordas"].end(); ++it)

	{

		const YAML::Node& node = *it;
        Horde* h = new Horde(i++);
        h->timeBetweenUnits_ms  = 100 * node["tiempo"].as<uint>();
        h->abmonibleAmount = node["abmonible"].as<uint>();
        h->demonioVerdeAmount = node["demonio_verde"].as<uint>();
        h->espectroAmount = node["espectro"].as<uint>();
        h->halconSangrientoAmount = node["halcon_sangriento"].as<uint>();
        h->hombreCabraAmount = node["hombre_cabra"].as<uint>();
        h->noMuertoAmount = node["no_muerto"].as<uint>();
        _hordes.push(h);
	}

}

HordeManager::~HordeManager() {

}

void HordeManager::AddHorde(Horde *horde) {

}

void HordeManager::Step() {
    if (_timeStamp == 0){
        _timeStamp = Helpers::MillisecondsTimeStamp();
        return;
    }

    bool isBegin = false;
    if (_currentHorde == nullptr){

        if (_hordes.empty()){
            //GANARON !!!
            game->PlayersWon();
            return;
        }

        _currentHorde = _hordes.front();
        _hordes.pop();
        game->notifications.Queue(new HordeUpdateGameNotification(_currentHorde->Id(), true));
        isBegin = true;
    }
    unsigned long long actualTimeStamp = Helpers::MillisecondsTimeStamp();

    if (_currentHorde->IsFinished()){
        if (!_currentHorde->finishNotified){
            _currentHorde->finishNotified = true;
            game->notifications.Queue(new HordeUpdateGameNotification(_currentHorde->Id(), false));
        }
        else if (actualTimeStamp - _timeStamp > timeToWaitBetweenHordes_ms){
            _timeStamp = actualTimeStamp;
            delete _currentHorde;
            _currentHorde = nullptr;
        }
        return;
    }


    if (actualTimeStamp - _timeStamp > _currentHorde->timeBetweenUnits_ms || isBegin){
        std::cout << "SPAWNING UNIT\n" << std::flush;
        if (isBegin){
            isBegin = false;
            std::cout << "IS BEGIN\n" << std::flush;
        }
        uint random_variable = (uint) std::rand() % 6;
        _timeStamp = actualTimeStamp;
        if (_currentHorde->abmonibleAmount > 0){
            _currentHorde->abmonibleAmount--;
            _currentHorde->units.push_back(game->SpawnAbmonible());
            return;
        }
        
        if (_currentHorde->demonioVerdeAmount > 0){
            _currentHorde->demonioVerdeAmount--;
            _currentHorde->units.push_back(game->SpawnDemonioVerde());
            return;
        }
        
        if (_currentHorde->espectroAmount > 0) {
            _currentHorde->espectroAmount--;
            _currentHorde->units.push_back(game->SpawnEspectro());
            return;
        }
        
        if (_currentHorde->halconSangrientoAmount > 0) {
            _currentHorde->halconSangrientoAmount--;
            _currentHorde->units.push_back(game->SpawnHalconSangriento());
            return;
        }
            
        if (_currentHorde->hombreCabraAmount > 0){
            _currentHorde->hombreCabraAmount--;
            _currentHorde->units.push_back(game->SpawnHombreCabra());
            return;
        }
        if (_currentHorde->noMuertoAmount > 0) {
            _currentHorde->noMuertoAmount--;
            _currentHorde->units.push_back(game->SpawnNoMuerto());
            return;
        }
                    
        std::cout << "UNIT SPAWNED\n" << std::flush;

    }
}