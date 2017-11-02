#ifndef TOWERDEFENSE_ANIMATEDSPRITE_H
#define TOWERDEFENSE_ANIMATEDSPRITE_H


#include "Sprite.h"

class AnimatedSprite : public Sprite {
private:
    int width;
    int height;
    int startX;
    int startY;
    int totalColumns;
    int totalRows;
    int timePerSprite;
    int i;
    int j;
    int currentSprite;

public:
    AnimatedSprite(SDL_Texture *texture, Renderer &renderer,
                   int width, int height,
                   int startX, int startY,
                   int totalColumns, int totalRows);
    void next(Uint32 ticks);
    void nextAndDraw(Uint32 ticks);
    void setTimePerSprite(Uint32 t);
    void setStartXStartY(int sx, int sy);
    int getCurrentSprite();
};


#endif //TOWERDEFENSE_ANIMATEDSPRITE_H
