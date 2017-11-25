//
// Created by tino on 21/11/17.
//

#include "../../../include/GameModel/GameNotifications/TowerUpgradedGameNotification.h"
#include "../../../../Common/Protocolo.h"

TowerUpgradedGameNotification::TowerUpgradedGameNotification(TowerVM vm) : _vm(vm) {}

TowerUpgradedGameNotification::~TowerUpgradedGameNotification() {}

void TowerUpgradedGameNotification::Notify(std::vector<PlayerProxy *> playersToNotify) {
    uint8_t opcode = TOWER_UPGRADE;
    uint8_t gameocopde = GAME_OPCODE;

    for (auto it = playersToNotify.begin(); it != playersToNotify.end(); ++it){
        PlayerProxy* p = *it;
        p->SendByte(gameocopde);
        p->SendByte(opcode);
        p->SendInt32(_vm.xPos);
        p->SendInt32(_vm.yPos);
        p->SendInt32(_vm.damage);
        p->SendInt32(_vm.range);
        p->SendInt32(_vm.projectile_ms_over_tile);
        p->SendInt32(_vm.level);
        
        p->SendInt32(_vm.exp_required_for_damage_upgrade);
        p->SendInt32(_vm.exp_required_for_range_upgrade);

        switch (_vm.type){
            case Fire:
                p->SendByte(SPELL_TYPE_FIRE);
                p->SendInt32(_vm.collateral_damage);
                p->SendInt32(_vm.collateral_range);
                p->SendInt32(_vm.exp_required_for_collateral_range_upgrade);
                break;
            case Water:
                p->SendByte(SPELL_TYPE_WATER);
                p->SendInt32(_vm.slow_seconds);
                p->SendInt32(_vm.slow_percent);
                p->SendInt32(_vm.exp_required_for_slow_upgrade);
                break;
            case Air:
                p->SendByte(SPELL_TYPE_AIR);
                p->SendInt32(_vm.nonFlyingDamage);
                break;
            case Ground:
                p->SendByte(SPELL_TYPE_GROUND);
                break;
        }
    }
}