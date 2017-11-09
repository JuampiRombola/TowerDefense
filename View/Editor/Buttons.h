#ifndef TOWERDEFENSE_BUTTONS_H
#define TOWERDEFENSE_BUTTONS_H

#include <list>
#include <SDL2/SDL.h>
#include "Button.h"
#include "../Common/Text.h"
#include "../Common/MousePosition.h"
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
#include "AumentarTiempoButton.h"
#include "DisminuirTiempoButton.h"
#include "ContadorTiempoInput.h"
#include "AumentarAltoMapaButton.h"
#include "AumentarAnchoMapaButton.h"
#include "DisminuirAnchoMapaButton.h"
#include "DisminuirAltoMapaButton.h"
#include "GuardarButton.h"

class Buttons {
private:
    std::list<Image*> images;
    MousePosition &mousePosition;
    Renderer &renderer;
    Editor& editor;
    TextureLoader &textureLoader;
    void addEnemigoButton(int horda, std::string enemigoKey, int texture);
    void addTiempoEntreHorda(int horda);
public:
    Buttons(MousePosition &mousePosition, Renderer &renderer, Editor &editor,
                TextureLoader &textureLoader);
    ~Buttons();
    void draw();
    void addInitialButtons();
    void addEnemigosButton(int horda);
    void deleteButtonsOfHorda(int horda);
    bool isAnyClicked();
};



#endif //TOWERDEFENSE_BUTTONS_H
