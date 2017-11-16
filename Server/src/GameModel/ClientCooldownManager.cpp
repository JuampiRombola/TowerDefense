//
// Created by tino on 15/11/17.
//
#include <iostream>
#include "../../include/GameModel/Helpers.h"
#include "../../include/GameModel/ClientCooldownManager.h"

ClientCooldownManager::ClientCooldownManager(GameConfiguration& gameCfg)
:
 _lastFireTowerPlacedTimeStamp_ms(0),
 _lastWaterTowerPlacedTimeStamp_ms(0),
 _lastAirTowerPlacedTimeStamp_ms(0),
 _lastGroundTowerPlacedTimeStamp_ms(0),
 _lastRayoTimeStamp_ms(0),
 _lastVentiscaTimeStamp_ms(0),
 _lastTornadoTimeStamp_ms(0),
 _lastFirewallTimeStamp_ms(0),
 _lastMeteoritoTimeStamp_ms(0),
 _lastGrietaTimeStamp_ms(0),
 _lastTerraformingTimeStamp_ms(0),
 _lastCongelacionTimeStamp_ms(0)
{

     _fireTowerPlacedCooldown_sec = gameCfg.Cfg["towers"]["fire"]["place_cooldown_sec"].as<uint>();
     _waterTowerPlacedCooldown_sec = gameCfg.Cfg["towers"]["water"]["place_cooldown_sec"].as<uint>();
     _airTowerPlacedCooldown_sec = gameCfg.Cfg["towers"]["air"]["place_cooldown_sec"].as<uint>();
     _groundTowerPlacedCooldown_sec = gameCfg.Cfg["towers"]["ground"]["place_cooldown_sec"].as<uint>();

     _rayoCooldown_sec = gameCfg.Cfg["spells"]["rayo"]["cast_cooldown_sec"].as<uint>();
    std::cout << " CHAU 1" << std::flush;

    _ventiscaCooldown_sec = gameCfg.Cfg["spells"]["ventisca"]["cast_cooldown_sec"].as<uint>();

    std::cout << " CHAU 2" << std::flush;
     _tornadoCooldown_sec = gameCfg.Cfg["spells"]["tornado"]["cast_cooldown_sec"].as<uint>();
    std::cout << " CHAU 3" << std::flush;
     _firewallCooldown_sec = gameCfg.Cfg["spells"]["murodefuego"]["cast_cooldown_sec"].as<uint>();
    std::cout << " CHAU4 " << std::flush;
     _meteoritoCooldown_sec = gameCfg.Cfg["spells"]["meteorito"]["cast_cooldown_sec"].as<uint>();
    std::cout << " CHAU 5" << std::flush;
     _grietaCooldown_sec = gameCfg.Cfg["spells"]["grieta"]["cast_cooldown_sec"].as<uint>();
    std::cout << " CHAU 6" << std::flush;
     _terraformingCooldown_sec = gameCfg.Cfg["spells"]["terraforming"]["cast_cooldown_sec"].as<uint>();
    std::cout << " CHAU 7" << std::flush;
     _congelacionCooldown_sec = gameCfg.Cfg["spells"]["congelacion"]["cast_cooldown_sec"].as<uint>();
    std::cout << " CHAU 8" << std::flush;
}

ClientCooldownManager::~ClientCooldownManager() {

}


bool ClientCooldownManager::IsSpellReady(CAST_SPELL_TYPE type){
    uint cooldown_ms;
    unsigned long long actual_ts = Helpers::MillisecondsTimeStamp();
    switch (type){
        case SPELL_GRIETA:
            cooldown_ms = _grietaCooldown_sec * 1000;
            if (actual_ts - _lastGrietaTimeStamp_ms > cooldown_ms){
                _lastGrietaTimeStamp_ms = actual_ts;
                return true;
            }
            return false;
        case SPELL_TORNADO:
            cooldown_ms = _tornadoCooldown_sec * 1000;
            if (actual_ts - _lastTornadoTimeStamp_ms > cooldown_ms){
                _lastTornadoTimeStamp_ms = actual_ts;
                return true;
            }
            return false;

        case SPELL_TERRAFORMING:
            cooldown_ms = _terraformingCooldown_sec * 1000;
            if (actual_ts - _lastTerraformingTimeStamp_ms > cooldown_ms){
                _lastTerraformingTimeStamp_ms = actual_ts;
                return true;
            }
            return false;

        case SPELL_CONGELACION:
            cooldown_ms = _congelacionCooldown_sec * 1000;
            if (actual_ts - _lastCongelacionTimeStamp_ms > cooldown_ms){
                _lastCongelacionTimeStamp_ms = actual_ts;
                return true;
            }
            return false;

        case SPELL_RAYO:
            cooldown_ms = _rayoCooldown_sec * 1000;
            if (actual_ts - _lastRayoTimeStamp_ms > cooldown_ms){
                _lastRayoTimeStamp_ms = actual_ts;
                return true;
            }
            return false;

        case SPELL_VENTISCA:
            cooldown_ms = _ventiscaCooldown_sec * 1000;
            if (actual_ts - _lastVentiscaTimeStamp_ms > cooldown_ms){
                _lastVentiscaTimeStamp_ms = actual_ts;
                return true;
            }
            return false;

        case SPELL_METEORITO:
            cooldown_ms = _meteoritoCooldown_sec * 1000;
            if (actual_ts - _lastMeteoritoTimeStamp_ms > cooldown_ms){
                _lastMeteoritoTimeStamp_ms = actual_ts;
                return true;
            }
            return false;

        case SPELL_FIREWALL:
            cooldown_ms = _firewallCooldown_sec * 1000;
            if (actual_ts - _lastFirewallTimeStamp_ms > cooldown_ms){
                _lastFirewallTimeStamp_ms = actual_ts;
                return true;
            }
            return false;

    }
    return false;
}

bool ClientCooldownManager::IsTowerPlacementReady(SPELL_TYPE type){
    uint cooldown_ms;
    unsigned long long actual_ts = Helpers::MillisecondsTimeStamp();
    switch (type){
        case SPELL_TYPE_GROUND:
            cooldown_ms = _groundTowerPlacedCooldown_sec * 1000;
            if (actual_ts - _lastGroundTowerPlacedTimeStamp_ms > cooldown_ms){
                _lastGroundTowerPlacedTimeStamp_ms = actual_ts;
                return true;
            }
            return false;
        case SPELL_TYPE_WATER:
            cooldown_ms = _waterTowerPlacedCooldown_sec * 1000;
            if (actual_ts - _lastWaterTowerPlacedTimeStamp_ms > cooldown_ms){
                _lastWaterTowerPlacedTimeStamp_ms = actual_ts;
                return true;
            }
            return false;

        case SPELL_TYPE_AIR:
            cooldown_ms = _airTowerPlacedCooldown_sec * 1000;
            if (actual_ts - _lastAirTowerPlacedTimeStamp_ms > cooldown_ms){
                _lastAirTowerPlacedTimeStamp_ms = actual_ts;
                return true;
            }
            return false;

        case SPELL_TYPE_FIRE:
            cooldown_ms = _fireTowerPlacedCooldown_sec * 1000;
            if (actual_ts - _lastFireTowerPlacedTimeStamp_ms > cooldown_ms){
                _lastFireTowerPlacedTimeStamp_ms = actual_ts;
                return true;
            }
            return false;
    }
    return false;
}