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
    Uint32 frequency;
    Uint32 damage;
    Uint32 range;
    Uint32 level;
    Uint32 flyDamage;
    Uint32 collateralDamage;
    Uint32 collateralRange;
    Uint32 freezePercent;
    Uint32 freezeDuration;
    Uint32 upgradeDamage;
    Uint32 upgradeRange;
    Uint32 upgradeImpact;
    Uint32 upgradeFreeze;
    std::mutex m;

public:
    TowerView(int id, int key, TextureLoader &textures, Renderer &renderer);
    void draw(Uint32 ticks) override;
    void setXY(int x, int y) override;

    void setUpgradesByElement();
    int getId();
    int getKey();
    Uint32 getExp();
    Uint32 getFrequency();
    Uint32 getDamage();
    Uint32 getRange();
    Uint32 getLevel();
    Uint32 getCollateralDamage();
    Uint32 getCollateralRange();
    Uint32 getFreezePercent();
    Uint32 getFreezeDuration();
    Uint32 getFlyDamage();
    
    void setExp(Uint32 n);
    void setFrequency(Uint32 n);
    void setDamage(Uint32 n);
    void setRange(Uint32 n);
    void setCollateralRange(Uint32 n);
    void setFreezePercent(Uint32 n);
    void setLevel(Uint32 n);
    void setCollateralDamage(Uint32 n);
    void setFreezeDuration(Uint32 n);
    void setFlyDamage(Uint32 n);
    
    Uint32 getUpgradeDamage();
    Uint32 getUpgradeRange();
    Uint32 getUpgradeImpact();
    Uint32 getUpgradeFreeze();
};


#endif //TOWERDEFENSE_FIRETOWERVIEW_H
