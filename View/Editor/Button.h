#ifndef TOWERDEFENSE_BUTTON_H
#define TOWERDEFENSE_BUTTON_H

#include <SDL2/SDL.h>
#include "../Common/MousePosition.h"
#include "../Common/Renderer.h"

class Button {
private:
    int id;
    MousePosition &mousePosition;
    virtual void click() = 0;
protected:
    SDL_Rect button;
    Renderer &renderer;
    SDL_Texture *texture;
    bool isClicked();
public:
    Button(int id, int posX, int posY, int width, int height,
           SDL_Texture *texture, MousePosition &mousePosition,
           Renderer &renderer);

    virtual ~Button();

    virtual void draw();
};

#endif //TOWERDEFENSE_BUTTON_H
