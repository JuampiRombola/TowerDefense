#ifndef TOWERDEFENSE_BUTTON_H
#define TOWERDEFENSE_BUTTON_H

#include <SDL2/SDL.h>
#include "MousePosition.h"
#include "Renderer.h"

class Button {
private:
    SDL_Rect button;
    SDL_Texture *texture;
    MousePosition &mousePosition;
    Renderer &renderer;
    virtual void click() = 0;
    bool isClicked();
public:
    Button(int posX, int posY, int width, int height, SDL_Texture *texture,
           MousePosition &mousePosition, Renderer &renderer);
    virtual ~Button();
    void draw();
};

#endif //TOWERDEFENSE_BUTTON_H
