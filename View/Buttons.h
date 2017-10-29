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
#include "SpriteNamesConfig.h"

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
    void addSuperficieButtons();
    void addNuevaHordaButton();
    void cleanHordasButtons();
    void addEnemigosButton(int horda);
};



#endif //TOWERDEFENSE_BUTTONS_H
