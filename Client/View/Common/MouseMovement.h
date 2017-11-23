#ifndef TOWERDEFENSE_MOUSEMOVEMENT_H
#define TOWERDEFENSE_MOUSEMOVEMENT_H


#include "Renderer.h"

class MouseMovement {
private:
    Renderer &renderer;
    int x;
    int y;
    Uint32 windowID;
public:
    explicit MouseMovement(Renderer &r);
    void entryMovement(int x, int y, Uint32 windowID);
    void doMovement();
};


#endif //TOWERDEFENSE_MOUSEMOVEMENT_H
