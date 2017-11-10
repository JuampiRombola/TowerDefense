#ifndef TOWERDEFENSE_AUMENTARTIEMPOBUTTON_H
#define TOWERDEFENSE_AUMENTARTIEMPOBUTTON_H


#include "../Common/Button.h"
#include "Editor.h"

class AumentarTiempoButton : public Button {
private:
    int horda;
    Editor &editor;

    void click();

public:
    AumentarTiempoButton(int horda,
                         SDL_Texture *texture,
                         MousePosition &mousePosition,
                         Renderer &renderer,
                         Editor &editor);
    void draw(int number);
    bool belongsToHorda(int horda);
};


#endif //TOWERDEFENSE_AUMENTARTIEMPOBUTTON_H
