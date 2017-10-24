#ifndef TOWERDEFENSE_FIRETOWERVIEW_H
#define TOWERDEFENSE_FIRETOWERVIEW_H

#include "View.h"
#include "Sprite.h"
#include "TextureLoader.h"
#include "Renderer.h"

class FireTowerView : public View{
private:
    Sprite spriteTower;
    Sprite spriteFire;

public:
    FireTowerView(TextureLoader &textures, Renderer &renderer);
    ~FireTowerView() override;
    void draw(Uint32 ticks) override;
    void setXY(int x, int y) override;
};


#endif //TOWERDEFENSE_FIRETOWERVIEW_H
