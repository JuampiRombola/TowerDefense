#include "TowerView.h"
#include "../Common/SpriteNamesConfig.h"
#include "../../../Common/Lock.h"
#include "ViewConstants.h"

TowerView::TowerView(int id, int key, TextureLoader &textures, 
                     Renderer &renderer) :
        id(id), key(key),
        cfg(textures.getConfig(key)),
        spriteTower(textures.getTexture(key), renderer,
                    cfg["TOWER_W"].as<int>(),
                    cfg["TOWER_H"].as<int>(),
                    cfg["TOWER_START_X"].as<int>(),
                    cfg["TOWER_START_Y"].as<int>(),
                    cfg["TOWER_COLUMNS"].as<int>(),
                    cfg["TOWER_ROWS"].as<int>()),
        spriteFire(textures.getTexture(key), renderer,
                   cfg["POWER_W"].as<int>(),
                   cfg["POWER_H"].as<int>(),
                   cfg["POWER_START_X"].as<int>(),
                   cfg["POWER_START_Y"].as<int>(),
                   cfg["POWER_COLUMNS"].as<int>(),
                   cfg["POWER_ROWS"].as<int>()),
        exp(0), frequency(1), damage(1), range(1), level(1), flyDamage(0),
        collateralDamage(0), collateralRange(0), freezePercent(0),
        freezeDuration(0) {
    spriteTower.setDestRect(x, y,
                            cfg["TOWER_DST_W"].as<int>(),
                            cfg["TOWER_DST_H"].as<int>());
    spriteTower.setOffsetXY(cfg["TOWER_OFFSET_X"].as<int>(),
                            cfg["TOWER_OFFSET_Y"].as<int>());

    spriteFire.setDestRect(x, y,
                           cfg["POWER_DST_W"].as<int>(),
                           cfg["POWER_DST_H"].as<int>());
    spriteFire.setOffsetXY(cfg["POWER_OFFSET_X"].as<int>(),
                           cfg["POWER_OFFSET_Y"].as<int>());
   // this->setUpgradesByElement();
}

void TowerView::draw(Uint32 ticks) {
    spriteTower.nextAndDraw(ticks);
    spriteFire.nextAndDraw(ticks);
}

void TowerView::setXY(int x, int y) {
    View::setXY(x, y);
    spriteTower.setDestXY(x, y);
    spriteFire.setDestXY(x, y);
}

void TowerView::setUpgradesByElement() {
    upgradeDamage = static_cast<Uint32>(pow(1.5, level) * 100);
    if (key == TORRE_TIERRA) {
        upgradeRange = static_cast<Uint32>(pow(2, level) * 500);
    }
    if (key == TORRE_FUEGO) {
        upgradeRange = static_cast<Uint32>(pow(2, level) * 100);
        upgradeImpact = static_cast<Uint32>(pow(2, level) * 500);
    }
    if (key == TORRE_AGUA) {
        upgradeRange = static_cast<Uint32>(pow(2, level) * 100);
        upgradeFreeze = static_cast<Uint32>(pow(2, level) * 100);
    }
    if (key == TORRE_AIRE) {
        upgradeRange = static_cast<Uint32>(pow(2, level) * 100);
    }
}

void TowerView::setUpgradeExperienceDamage(uint32_t exp){
    std::unique_lock<std::mutex> lock(this->m);
    upgradeDamage = exp;
}

void TowerView::setUpgradeExperienceRange(uint32_t exp){
    std::unique_lock<std::mutex> lock(this->m);
    upgradeRange = exp;
}
void TowerView::setUpgradeExperienceCollateralRange(uint32_t exp){
    std::unique_lock<std::mutex> lock(this->m);
    upgradeImpact = exp;

}
void TowerView::setUpgradeExperienceSlow(uint32_t exp){
    std::unique_lock<std::mutex> lock(this->m);
    upgradeFreeze = exp;
}



int TowerView::getId() {
    return id;
}

Uint32 TowerView::getExp() {
    std::unique_lock<std::mutex> lock(this->m);
    return exp;
}

Uint32 TowerView::getDamage() {
    std::unique_lock<std::mutex> lock(this->m);
    return damage;
}

Uint32 TowerView::getRange() {
    std::unique_lock<std::mutex> lock(this->m);
    return range;
}

Uint32 TowerView::getCollateralDamage() {
    std::unique_lock<std::mutex> lock(this->m);
    return collateralDamage;
}

Uint32 TowerView::getFreezePercent() {
    std::unique_lock<std::mutex> lock(this->m);
    return freezePercent;
}

Uint32 TowerView::getUpgradeDamage() {
    std::unique_lock<std::mutex> lock(this->m);
    return upgradeDamage;
}

Uint32 TowerView::getUpgradeRange() {
    std::unique_lock<std::mutex> lock(this->m);
    return upgradeRange;
}

Uint32 TowerView::getUpgradeImpact() {
    std::unique_lock<std::mutex> lock(this->m);
    return upgradeImpact;
}

Uint32 TowerView::getUpgradeFreeze() {
    std::unique_lock<std::mutex> lock(this->m);
    return upgradeFreeze;
}

void TowerView::setExp(Uint32 n) {
    std::unique_lock<std::mutex> lock(this->m);
    exp = n;
}

void TowerView::setDamage(Uint32 n) {
    std::unique_lock<std::mutex> lock(this->m);
    damage = n;
}

void TowerView::setRange(Uint32 n) {
    std::unique_lock<std::mutex> lock(this->m);
    range = n;
}

void TowerView::setCollateralRange(Uint32 n) {
    std::unique_lock<std::mutex> lock(this->m);
    collateralRange = n;
}

void TowerView::setFreezePercent(Uint32 n) {
    std::unique_lock<std::mutex> lock(this->m);
    freezePercent = n;
}

int TowerView::getKey() {
    if (key == TORRE_TIERRA)
        return ELEMENTAL_EARTH;
    if (key == TORRE_FUEGO)
        return ELEMENTAL_FIRE;
    if (key == TORRE_AGUA)
        return ELEMENTAL_WATER;
    if (key == TORRE_AIRE)
        return ELEMENTAL_AIR;
}

Uint32 TowerView::getLevel() {
    std::unique_lock<std::mutex> lock(this->m);
    return level;
}

Uint32 TowerView::getCollateralRange() {
    std::unique_lock<std::mutex> lock(this->m);
    return collateralRange;
}

Uint32 TowerView::getFreezeDuration() {
    std::unique_lock<std::mutex> lock(this->m);
    return freezeDuration;
}

Uint32 TowerView::getFlyDamage() {
    std::unique_lock<std::mutex> lock(this->m);
    return flyDamage;
}

void TowerView::setLevel(Uint32 n) {
    std::unique_lock<std::mutex> lock(this->m);
    level = n;
}

void TowerView::setCollateralDamage(Uint32 n) {
    std::unique_lock<std::mutex> lock(this->m);
    collateralDamage = n;
}

void TowerView::setFreezeDuration(Uint32 n) {
    std::unique_lock<std::mutex> lock(this->m);
    freezeDuration = n;
}

void TowerView::setFlyDamage(Uint32 n) {
    std::unique_lock<std::mutex> lock(this->m);
    flyDamage = n;
}

Uint32 TowerView::getFrequency() {
    std::unique_lock<std::mutex> lock(this->m);
    return frequency;
}

void TowerView::setFrequency(Uint32 n) {
    std::unique_lock<std::mutex> lock(this->m);
    frequency = n;
}
