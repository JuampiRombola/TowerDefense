#ifndef TOWERDEFENSE_BUTTON_H
#define TOWERDEFENSE_BUTTON_H

#include <SDL2/SDL.h>
#include "MousePosition.h"
#include "Renderer.h"
#include "Image.h"

class Button : public Image {
private:
    MousePosition &mousePosition;

protected:
    virtual void click() = 0;

public:
    Button(int posX, int posY, int width, int height,
               SDL_Texture *texture, MousePosition &mousePosition,
               Renderer &renderer);

    virtual ~Button();

    virtual void draw(int number, int padding);

    bool isClicked();

    bool wasLastClick();

    bool isMarked();
};

#endif //TOWERDEFENSE_BUTTON_H
