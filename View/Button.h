#ifndef TOWERDEFENSE_BUTTON_H
#define TOWERDEFENSE_BUTTON_H

#include <SDL2/SDL.h>
#include "MousePosition.h"
#include "Renderer.h"

class Button {
private:
    int id;
protected:
    SDL_Rect button;
private:
    MousePosition &mousePosition;
protected:
    Renderer &renderer;
private:
    virtual void click() = 0;

protected:
    bool isClicked();

    SDL_Texture *texture;
public:
    Button(int id, int posX, int posY, int width, int height,
           SDL_Texture *texture, MousePosition &mousePosition,
           Renderer &renderer);

    virtual ~Button();

    virtual void draw();
};

#endif //TOWERDEFENSE_BUTTON_H
