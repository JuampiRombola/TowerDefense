#ifndef TOWERDEFENSE_FIRETOWERVIEW_H
#define TOWERDEFENSE_FIRETOWERVIEW_H

#include "../Common/View.h"
#include "../Common/TextureLoader.h"
#include "../Common/Renderer.h"
#include "../Common/AnimatedSprite.h"

class TowerView : public View {
private:
    int id;
    int key;
    int exp;
    const YAML::Node cfg;
    AnimatedSprite spriteTower;
    AnimatedSprite spriteFire;

public:
    TowerView(int id, int key, TextureLoader &textures, Renderer &renderer);
    void draw(Uint32 ticks) override;
    void setXY(int x, int y) override;
    std::string onClick() override;
    int getId();
};


#endif //TOWERDEFENSE_FIRETOWERVIEW_H
