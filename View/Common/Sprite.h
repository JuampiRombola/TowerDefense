//
// Created by juampi on 10/19/17.
//

#ifndef TOWERDEFENSE_SPRITE_H
#define TOWERDEFENSE_SPRITE_H

#include <SDL2/SDL.h>
#include "Renderer.h"

class Sprite {
private:
    SDL_Texture *texture;
    Renderer &renderer;
    SDL_Rect srcRect;
    SDL_Rect dstRect;
    int offsetX;
    int offsetY;

public:
    Sprite(SDL_Texture *texture, Renderer &renderer);
    ~Sprite();
    void draw();
    void setSourceXY(int x, int y);
    void setDestXY(int x, int y);
    void setSourceRect(int x, int y, int w, int h);
    void setDestRect(int x, int y, int w, int h);
    void setOffsetXY(int x, int y);
    void setTexture(SDL_Texture *newTexture);
    int getOffsetX();
    int getOffsetY();
};


#endif //TOWERDEFENSE_SPRITE_H
