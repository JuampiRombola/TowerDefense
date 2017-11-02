#ifndef TOWERDEFENSE_FIRETOWERVIEW_H
#define TOWERDEFENSE_FIRETOWERVIEW_H

#include "../Common/View.h"
#include "../Common/TextureLoader.h"
#include "../Common/Renderer.h"
#include "../Common/AnimatedSprite.h"

class FireTowerView : public View{
private:
    AnimatedSprite spriteTower;
    AnimatedSprite spriteFire;

public:
    FireTowerView(TextureLoader &textures, Renderer &renderer);
    ~FireTowerView() override;
    void draw(Uint32 ticks) override;
    void setXY(int x, int y) override;
};


#endif //TOWERDEFENSE_FIRETOWERVIEW_H
