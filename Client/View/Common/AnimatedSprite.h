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
    enum DISPLAY {LOOP, ONCE, FROZEN};
    int display;

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
    void reset();

    // 0 - LOOP reproduce la animacion indefinidamente (por defecto)
    // 1 - ONCE reproduce la animacion una sola vez
    // 2 - FROZEN reproduce la animacion una sola vez,
    //     y luego muestra el ultimo sprite
    void setDisplayMode(int mode);
};


#endif //TOWERDEFENSE_ANIMATEDSPRITE_H
