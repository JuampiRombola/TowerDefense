#ifndef TOWERDEFENSE_BUTTONS_H
#define TOWERDEFENSE_BUTTONS_H

#include <list>
#include <SDL2/SDL.h>
#include "Button.h"
#include "../Common/Text.h"
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
#include "../Common/SpriteNamesConfig.h"
#include "ContadorEnemigosInput.h"
#include "EnemigoImage.h"

class Buttons {
private:
    std::list<Image*> images;
    MousePosition &mousePosition;
    Renderer &renderer;
    Editor& editor;
    TextureLoader &textureLoader;
    KeyboardInput &keyboardInput;
    void addEnemigoButton(int horda, std::string enemigoKey, int texture);
public:
    Buttons(MousePosition &mousePosition, Renderer &renderer, Editor &editor,
            TextureLoader &textureLoader, KeyboardInput &keyboardInput);
    ~Buttons();
    void draw();
    void addInitialButtons();
    void addEnemigosButton(int horda);
    bool isAnyClicked();
};



#endif //TOWERDEFENSE_BUTTONS_H
