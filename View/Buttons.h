#ifndef TOWERDEFENSE_BUTTONS_H
#define TOWERDEFENSE_BUTTONS_H

#include <list>
#include <SDL2/SDL.h>
#include "Button.h"
#include "TextInput.h"
#include "MousePosition.h"
#include "KeyboardInput.h"
#include "Renderer.h"
#include "TextureLoader.h"
#include "SuperficieButton.h"
#include "NuevaHordaButton.h"
#include "AgregarEnemigoButton.h"
#include "EliminarEnemigoButton.h"
#include "EliminarHordaButton.h"

class Buttons {
private:
    std::list<Button*> buttons;
    std::list<Button*> hordasButtons;
    MousePosition &mousePosition;
    Renderer &renderer;
    Editor& editor;
    TextureLoader &textureLoader;
    KeyboardInput &keyboardInput;
    int nextId;
public:
    Buttons(MousePosition &mousePosition, Renderer &renderer, Editor &editor,
            TextureLoader &textureLoader, KeyboardInput &keyboardInput);
    ~Buttons();
    void draw();
    void addSuperficieButtons(SDL_Texture* pradera, SDL_Texture* lava,
                              SDL_Texture* desierto, SDL_Texture* glaciar);
    void addNuevaHordaButton(SDL_Texture *texture);
    void cleanHordasButtons();
    void addEnemigosButton(int horda);
};


#endif //TOWERDEFENSE_BUTTONS_H
