#ifndef TOWERDEFENSE_BUTTONS_H
#define TOWERDEFENSE_BUTTONS_H

#include <list>
#include <SDL2/SDL.h>
#include "../Common/Button.h"
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
#include "AumentarTiempoHordaButton.h"
#include "DisminuirTiempoHordaButton.h"
#include "ContadorTiempoHordaInput.h"
#include "AumentarAltoMapaButton.h"
#include "AumentarAnchoMapaButton.h"
#include "DisminuirAnchoMapaButton.h"
#include "DisminuirAltoMapaButton.h"
#include "GuardarButton.h"

class EditorButtons {
private:
    std::list<Image*> images;
    MousePosition &mousePosition;
    std::list<Sprite *> backgrounds;
    unsigned int padding;
    Renderer &renderer;
    Editor& editor;
    TextureLoader &textureLoader;
    void addEnemigoButton(int horda, std::string enemigoKey, int texture);
    void addTiempoEntreHorda(int horda);
    int hordaToDelete;
public:
    EditorButtons(MousePosition &mousePosition, Renderer &renderer, Editor &editor,
                TextureLoader &textureLoader);
    ~EditorButtons();
    void draw();
    void addInitialButtons();
    void addEnemigosButton(int horda);
    void deleteButtonsOfHorda(int horda);
    bool isAnyClicked();
    void addTiempoEntreEnemigos(int horda);
    void addBackground();
    void limitPadding();
};



#endif //TOWERDEFENSE_BUTTONS_H
