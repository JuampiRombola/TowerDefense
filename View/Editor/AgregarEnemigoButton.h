#ifndef TOWERDEFENSE_AGREGARENEMIGOBUTTON_H
#define TOWERDEFENSE_AGREGARENEMIGOBUTTON_H

#include "Button.h"
#include "Editor.h"

class AgregarEnemigoButton : public Button {
private:
    int horda;
    std::string enemigo;
    Editor &editor;

    void click();

public:
    AgregarEnemigoButton(int id, int horda, const std::string &enemigo,
                         SDL_Texture *texture, MousePosition &mousePosition,
                         Renderer &renderer, Editor &editor);
};

#endif //TOWERDEFENSE_AGREGARENEMIGOBUTTON_H
