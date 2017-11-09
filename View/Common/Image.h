#ifndef TOWERDEFENSE_IMAGE_H
#define TOWERDEFENSE_IMAGE_H

#include <SDL2/SDL.h>
#include "Renderer.h"
#include "../Editor/EditorConstants.h"

class Image {
protected:
    Renderer& renderer;
    SDL_Texture* texture;
    SDL_Rect button;
public:
    Image(int x, int y, int width, int height, SDL_Texture* texture,
          Renderer& renderer);
    virtual void draw(int number);
    virtual bool isClicked();
    virtual bool belongsToHorda(int horda);
    virtual ~Image();
};


#endif //TOWERDEFENSE_IMAGE_H
