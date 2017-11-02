#ifndef TOWERDEFENSE_SHOT_H
#define TOWERDEFENSE_SHOT_H


#include "../Common/View.h"
#include "../Common/Sprite.h"
#include "../Common/TextureLoader.h"
#include "../Common/Renderer.h"

class Shot : public View {
private:
    //Sprite spriteShot;
    //Sprite spriteExplotion;

public:
    Shot(int key, TextureLoader &textures, Renderer &renderer);
    void draw(Uint32 ticks) override;
    void setXY(int x, int y) override;
};


#endif //TOWERDEFENSE_SHOT_H
