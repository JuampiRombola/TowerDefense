#ifndef TOWERDEFENSE_BUTTONS_H
#define TOWERDEFENSE_BUTTONS_H

#include <list>
#include <SDL2/SDL.h>
#include "Button.h"
#include "TestButton.h"
#include "MousePosition.h"
#include "Renderer.h"

class Buttons {
private:
    std::list<Button*> buttons;
    MousePosition &mousePosition;
    Renderer &renderer;
public:
    Buttons(MousePosition &mousePosition, Renderer &renderer);
    ~Buttons();
    void draw();
    void addTestButton(SDL_Texture* texture);
};


#endif //TOWERDEFENSE_BUTTONS_H
