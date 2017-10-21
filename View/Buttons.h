#ifndef TOWERDEFENSE_BUTTONS_H
#define TOWERDEFENSE_BUTTONS_H

#include <list>
#include <SDL2/SDL.h>
#include "Button.h"
#include "TestButton.h"
#include "MousePosition.h"
#include "Renderer.h"
#include "TestToggleButton.h"
#include "SuperficieButton.h"

class Buttons {
private:
    std::list<Button*> buttons;
    MousePosition &mousePosition;
    Renderer &renderer;
    Editor& editor;
public:
    Buttons(MousePosition &mousePosition, Renderer &renderer, Editor &editor);
    ~Buttons();
    void draw();
    void addTestButton(SDL_Texture* texture);
    void addTestToggleButton(SDL_Texture* activeTexture, SDL_Texture*
                            inactiveTexture);
    void addSuperficieButtons(SDL_Texture* pradera, SDL_Texture* lava,
                              SDL_Texture* desierto, SDL_Texture* glaciar);
};


#endif //TOWERDEFENSE_BUTTONS_H
