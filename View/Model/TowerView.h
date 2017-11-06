#ifndef TOWERDEFENSE_FIRETOWERVIEW_H
#define TOWERDEFENSE_FIRETOWERVIEW_H

#include "../Common/View.h"
#include "../Common/TextureLoader.h"
#include "../Common/Renderer.h"
#include "../Common/AnimatedSprite.h"

class TowerView : public View{
private:
    const YAML::Node cfg;
    AnimatedSprite spriteTower;
    AnimatedSprite spriteFire;

public:
    TowerView(int key, TextureLoader &textures, Renderer &renderer);
    void draw(Uint32 ticks) override;
    void setXY(int x, int y) override;
};


#endif //TOWERDEFENSE_FIRETOWERVIEW_H
