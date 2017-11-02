#ifndef TOWERDEFENSE_SHOT_H
#define TOWERDEFENSE_SHOT_H


#include "../Common/View.h"
#include "../Common/AnimatedSprite.h"
#include "../Common/TextureLoader.h"
#include "../Common/Renderer.h"

class ShotView : public View {
private:
    enum State {DISABLE, SHOOT, EXPLOSION};
    Renderer &renderer;
    AnimatedSprite spriteShot;
    AnimatedSprite spriteExplosion;
    int currentState;
    Uint32 initTime;
    int requiredTime;
    int totalDistanceX;
    int totalDistanceY;
    int traveledDistanceX;
    int traveledDistanceY;

public:
    ShotView(int key, TextureLoader &textures, Renderer &renderer);
    void draw(Uint32 ticks) override;
    void setXY(int x, int y) override;
    void shoot(int fromX, int fromY, int toX, int toY, Uint32 t);

private:
    void setDistanceToMove(Uint32 ticks);
    void enableExplosion();
};


#endif //TOWERDEFENSE_SHOT_H
