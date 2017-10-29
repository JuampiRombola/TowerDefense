#ifndef TOWERDEFENSE_BUTTONS_H
#define TOWERDEFENSE_BUTTONS_H

#include <list>
#include <SDL2/SDL.h>
#include "Button.h"
#include "../Common/TextInput.h"
#include "../Common/MousePosition.h"
#include "../Common/KeyboardInput.h"
#include "../Common/Renderer.h"
#include "../Common/TextureLoader.h"
#include "SuperficieButton.h"
#include "NuevaHordaButton.h"
#include "AgregarEnemigoButton.h"
#include "EliminarEnemigoButton.h"
#include "EliminarHordaButton.h"
#include "../Common/SpriteNamesConfig.h"

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
