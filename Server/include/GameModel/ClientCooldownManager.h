//
// Created by tino on 15/11/17.
//

#ifndef TOWERDEFENSE_CLIENTCOOLDOWNMANAGER_H
#define TOWERDEFENSE_CLIENTCOOLDOWNMANAGER_H


#include "../../../Common/Protocolo.h"
#include "Configuration.h"
#include "../PlayerProxy.h"

class ClientCooldownManager {
private:
    unsigned long long _lastFireTowerPlacedTimeStamp_ms;
    unsigned long long _lastWaterTowerPlacedTimeStamp_ms;
    unsigned long long _lastAirTowerPlacedTimeStamp_ms;
    unsigned long long _lastGroundTowerPlacedTimeStamp_ms;

    unsigned long long _lastRayoTimeStamp_ms;
    unsigned long long _lastVentiscaTimeStamp_ms;
    unsigned long long _lastTornadoTimeStamp_ms;
    unsigned long long _lastFirewallTimeStamp_ms;
    unsigned long long _lastMeteoritoTimeStamp_ms;
    unsigned long long _lastGrietaTimeStamp_ms;
    unsigned long long _lastTerraformingTimeStamp_ms;
    unsigned long long _lastCongelacionTimeStamp_ms;


    uint _fireTowerPlacedCooldown_sec;
    uint _waterTowerPlacedCooldown_sec;
    uint _airTowerPlacedCooldown_sec;
    uint _groundTowerPlacedCooldown_sec;

    uint _rayoCooldown_sec;
    uint _ventiscaCooldown_sec;
    uint _tornadoCooldown_sec;
    uint _firewallCooldown_sec;
    uint _meteoritoCooldown_sec;
    uint _grietaCooldown_sec;
    uint _terraformingCooldown_sec;
    uint _congelacionCooldown_sec;

    std::map<PlayerProxy*, unsigned long long> _pingLastTimeStamps;
    uint _pingCooldown_sec;


public:
    ClientCooldownManager(Configuration& gameCfg);
    ~ClientCooldownManager();

    bool IsSpellReady(CAST_SPELL_TYPE type);
    bool IsTowerPlacementReady(SPELL_TYPE type);

    uint GetPingCooldown();
    bool IsPingForPlayerReady(PlayerProxy& player);
    uint GetSpellCooldown_ms(CAST_SPELL_TYPE type);
    void SpellCasted(CAST_SPELL_TYPE type);
    void PingSet(PlayerProxy& player);


};


#endif //TOWERDEFENSE_CLIENTCOOLDOWNMANAGER_H
