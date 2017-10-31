#ifndef TOWERDEFENSE_BUTTON_H
#define TOWERDEFENSE_BUTTON_H

#include <SDL2/SDL.h>
#include "../Common/MousePosition.h"
#include "../Common/Renderer.h"
#include "../Common/Image.h"

class Button : public Image {
private:
    MousePosition &mousePosition;
    virtual void click() = 0;
protected:
    int id;
    bool isClicked();
public:
    Button(int id, int posX, int posY, int width, int height,
           SDL_Texture *texture, MousePosition &mousePosition,
           Renderer &renderer);

    virtual ~Button();

    virtual void draw();
};

#endif //TOWERDEFENSE_BUTTON_H