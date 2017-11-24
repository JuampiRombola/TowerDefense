#include "TowerView.h"
#include "../Common/SpriteNamesConfig.h"
#include "../../../Common/Lock.h"

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
    this->setUpgradesByElement();
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

int TowerView::getId() {
    return id;
}

Uint32 TowerView::getExp() {
    Lock(this->m);
    return exp;
}

Uint32 TowerView::getDamage() {
    Lock(this->m);
    return damage;
}

Uint32 TowerView::getRange() {
    Lock(this->m);
    return range;
}

Uint32 TowerView::getCollateralDamage() {
    Lock(this->m);
    return collateralDamage;
}

Uint32 TowerView::getFreezePercent() {
    Lock(this->m);
    return freezePercent;
}

Uint32 TowerView::getUpgradeDamage() {
    Lock(this->m);
    return upgradeDamage;
}

Uint32 TowerView::getUpgradeRange() {
    Lock(this->m);
    return upgradeRange;
}

Uint32 TowerView::getUpgradeImpact() {
    Lock(this->m);
    return upgradeImpact;
}

Uint32 TowerView::getUpgradeFreeze() {
    Lock(this->m);
    return upgradeFreeze;
}

void TowerView::setExp(Uint32 n) {
    Lock(this->m);
    exp = n;
}

void TowerView::setDamage(Uint32 n) {
    Lock(this->m);
    damage = n;
}

void TowerView::setRange(Uint32 n) {
    Lock(this->m);
    range = n;
}

void TowerView::setCollateralRange(Uint32 n) {
    Lock(this->m);
    collateralRange = n;
}

void TowerView::setFreezePercent(Uint32 n) {
    Lock(this->m);
    freezePercent = n;
}

int TowerView::getKey() {
    return key;
}

Uint32 TowerView::getLevel() {
    Lock(this->m);
    return level;
}

Uint32 TowerView::getCollateralRange() {
    Lock(this->m);
    return collateralRange;
}

Uint32 TowerView::getFreezeDuration() {
    Lock(this->m);
    return freezeDuration;
}

Uint32 TowerView::getFlyDamage() {
    Lock(this->m);
    return flyDamage;
}

void TowerView::setLevel(Uint32 n) {
    Lock(this->m);
    level = n;
}

void TowerView::setCollateralDamage(Uint32 n) {
    Lock(this->m);
    collateralDamage = n;
}

void TowerView::setFreezeDuration(Uint32 n) {
    Lock(this->m);
    freezeDuration = n;
}

void TowerView::setFlyDamage(Uint32 n) {
    Lock(this->m);
    flyDamage = n;
}

Uint32 TowerView::getFrequency() {
    Lock(this->m);
    return frequency;
}

void TowerView::setFrequency(Uint32 n) {
    Lock(this->m);
    frequency = n;
}
