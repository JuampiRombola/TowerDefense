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
    enum State {WALKING, DYING, DEAD, FROZEN};
    int currentDirection;
    int currentState;
    int nextX;
    int nextY;
    int directionX;
    int directionY;
    Uint32 initTime;
    Uint32 timePerPixel;
    int currentDisplacement;
    bool isFirstStep;
    Uint32 lastTime;
    Uint32 freezeTime;

    // Es el total de desplazamiento por tile
    // con la velocidad actual
    int accumulatedDisplacement;

    // Lo que se desplazo con otras velocidades
    // distintas a la actual
    int otherSpeedDisplacement;

public:
    UnitView(int id, int key, TextureLoader &textures, Renderer &renderer);
    void draw(Uint32 ticks) override;
    void setXY(int x, int y) override;
    void move(int x, int y, int nextX, int nextY, Uint32 t);
    void move(int x, int y, int nextX, int nextY);
    void enableDying();
    int getId();
    bool isDead();
    void setSpeed(Uint32 newSpeed);
    void totalFreeze(Uint32 duration);

private:
    void setNumberOfPixelsToMove(Uint32 currentTime);
    void setOffsetXY();
    void calculateNewDirection();
    void setCurrentDirection();
    void finishFreeze();
};


#endif //TOWERDEFENSE_ENEMY_H
