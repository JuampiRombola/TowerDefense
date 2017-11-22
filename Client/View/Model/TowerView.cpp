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
        exp(1), damage(1), range(1), impact(0), freeze(0),
        upgradeDamage(1), upgradeRange(2), upgradeImpact(2),
        upgradeFreeze(2) {

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

Uint32 TowerView::getImpact() {
    Lock(this->m);
    return impact;
}

Uint32 TowerView::getFreeze() {
    Lock(this->m);
    return freeze;
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

void TowerView::setImpact(Uint32 n) {
    Lock(this->m);
    impact = n;
}

void TowerView::setFreeze(Uint32 n) {
    Lock(this->m);
    freeze = n;
}

void TowerView::setUpgradeDamage(Uint32 n) {
    Lock(this->m);
    upgradeDamage = n;
}

void TowerView::setUpgradeRange(Uint32 n) {
    Lock(this->m);
    upgradeRange = n;
}

void TowerView::setUpgradeImpact(Uint32 n) {
    Lock(this->m);
    upgradeImpact = n;
}

void TowerView::setUpgradeFreeze(Uint32 n) {
    Lock(this->m);
    upgradeFreeze = n;
}

int TowerView::getkey() {
    return key;
}
