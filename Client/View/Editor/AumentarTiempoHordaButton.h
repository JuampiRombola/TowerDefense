#ifndef TOWERDEFENSE_AUMENTARTIEMPOBUTTON_H
#define TOWERDEFENSE_AUMENTARTIEMPOBUTTON_H


#include "../Common/Button.h"
#include "Editor.h"

class AumentarTiempoHordaButton : public Button {
private:
    int horda;
    Editor &editor;

    void click();

public:
    AumentarTiempoHordaButton(int horda,
                         SDL_Texture *texture,
                         MousePosition &mousePosition,
                         Renderer &renderer,
                         Editor &editor);
    void draw(int number, int padding);
    bool belongsToHorda(int horda);
};


#endif //TOWERDEFENSE_AUMENTARTIEMPOBUTTON_H
