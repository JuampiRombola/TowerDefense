#ifndef TOWERDEFENSE_VIEW_H
#define TOWERDEFENSE_VIEW_H

#include "Sprite.h"
#include "TextureLoader.h"
#include "Renderer.h"

class View {
protected:
    Sprite sprite;
    int x;
    int y;

public:
    View(int key, TextureLoader &textures, Renderer &renderer);
    virtual ~View();
    virtual void draw(Uint32 ticks) = 0;
    virtual void setXY(int x, int y);
};


#endif //TOWERDEFENSE_VIEW_H
