#ifndef TOWERDEFENSE_ENEMY_H
#define TOWERDEFENSE_ENEMY_H


#include "../Common/View.h"
#include "../Common/TextureLoader.h"
#include "../Common/AnimatedSprite.h"

class UnitView : public View {
private:
    int id;
    int key;
    int health;
    const YAML::Node cfg;
    AnimatedSprite spriteWalking;
    AnimatedSprite spriteDying;
    enum Direction {S, SO, O, NO, N, NE, E, SE};
    enum State {WALKING, DYING, DEAD};
    int currentDirection;
    int currentState;
    int nextX;
    int nextY;
    int directionX;
    int directionY;
    Uint32 initTime;
    Uint32 timePerPixel;
    int currentDisplacement;
    int accumulatedDisplacement;
    bool isFirstStep;

public:
    UnitView(int id, int key, TextureLoader &textures, Renderer &renderer);
    void draw(Uint32 ticks) override;
    void setXY(int x, int y) override;
    void move(int x, int y, int nextX, int nextY, Uint32 t);
    void enableDying();
    std::string onClick() override;
    int getId();
    bool isDead();

private:
    void setNumberOfPixelsToMove(Uint32 currentTime);
    void setOffsetXY();
    void calculateNewDirection();
    void setCurrentDirection();
};


#endif //TOWERDEFENSE_ENEMY_H
