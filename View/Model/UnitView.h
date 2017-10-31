#ifndef TOWERDEFENSE_ENEMY_H
#define TOWERDEFENSE_ENEMY_H


#include "../Common/View.h"
#include "../Common/Sprite.h"
#include "../Common/TextureLoader.h"

class UnitView : public View {
private:
    enum Direction {S, SO, O, NO, N, NE, E, SE};
    enum State {WALKING, DYING};
    int currentDirection;
    int currentState;
    int currentIndex;
    Sprite spriteWalking;
    Sprite spriteDying;
    std::vector<std::pair<int, int>> *path;
    //std::pair<int, int> walkingWH;
    //std::pair<int, int> dyingWH;

public:
    UnitView(int key, TextureLoader &textures, Renderer &renderer,
             std::vector<std::pair<int, int>> *path);
    void draw(Uint32 ticks) override;
    void setXY(int x, int y) override;
    void move();
};


#endif //TOWERDEFENSE_ENEMY_H
