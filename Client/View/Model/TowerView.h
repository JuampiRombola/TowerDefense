#ifndef TOWERDEFENSE_FIRETOWERVIEW_H
#define TOWERDEFENSE_FIRETOWERVIEW_H

#include <mutex>
#include "../Common/View.h"
#include "../Common/TextureLoader.h"
#include "../Common/Renderer.h"
#include "../Common/AnimatedSprite.h"

class TowerView : public View {
private:
    int id;
    int key;
    const YAML::Node cfg;
    AnimatedSprite spriteTower;
    AnimatedSprite spriteFire;
    Uint32 exp;
    Uint32 damage;
    Uint32 range;
    Uint32 impact;
    Uint32 freeze;
    Uint32 upgradeDamage;
    Uint32 upgradeRange;
    Uint32 upgradeImpact;
    Uint32 upgradeFreeze;
    std::mutex m;

public:
    TowerView(int id, int key, TextureLoader &textures, Renderer &renderer);
    void draw(Uint32 ticks) override;
    void setXY(int x, int y) override;

    int getId();
    int getkey();
    Uint32 getExp();
    Uint32 getDamage();
    Uint32 getRange();
    Uint32 getImpact();
    Uint32 getFreeze();
    void setExp(Uint32 n);
    void setDamage(Uint32 n);
    void setRange(Uint32 n);
    void setImpact(Uint32 n);
    void setFreeze(Uint32 n);
    Uint32 getUpgradeDamage();
    Uint32 getUpgradeRange();
    Uint32 getUpgradeImpact();
    Uint32 getUpgradeFreeze();
    void setUpgradeDamage(Uint32 n);
    void setUpgradeRange(Uint32 n);
    void setUpgradeImpact(Uint32 n);
    void setUpgradeFreeze(Uint32 n);
};


#endif //TOWERDEFENSE_FIRETOWERVIEW_H
