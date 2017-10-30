#ifndef TOWERDEFENSE_IMAGE_H
#define TOWERDEFENSE_IMAGE_H

#include <SDL2/SDL.h>
#include "Renderer.h"

class Image {
protected:
    Renderer& renderer;
    SDL_Texture* texture;
    SDL_Rect button;
public:
    Image(int x, int y, int width, int height, SDL_Texture* texture,
          Renderer& renderer);
    virtual void draw();
};


#endif //TOWERDEFENSE_IMAGE_H
