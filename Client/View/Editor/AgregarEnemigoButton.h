#ifndef TOWERDEFENSE_AGREGARENEMIGOBUTTON_H
#define TOWERDEFENSE_AGREGARENEMIGOBUTTON_H

#include "../Common/Button.h"
#include "Editor.h"

class AgregarEnemigoButton : public Button {
private:
    int horda;
    std::string enemigo;
    Editor &editor;

    void click();

public:
    AgregarEnemigoButton(int horda,
                             const std::string &enemigo,
                             SDL_Texture *texture,
                             MousePosition &mousePosition,
                             Renderer &renderer,
                             Editor &editor);
    void draw(int number, int padding);
    bool belongsToHorda(int horda);
};

#endif //TOWERDEFENSE_AGREGARENEMIGOBUTTON_H
