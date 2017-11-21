#ifndef TOWERDEFENSE_AUMENTARTIEMPOENEMIGOSBUTTON_H
#define TOWERDEFENSE_AUMENTARTIEMPOENEMIGOSBUTTON_H


#include "../Common/Button.h"
#include "Editor.h"

class AumentarTiempoEnemigosButton : public Button {
private:
    int horda;
    Editor &editor;

    void click();

public:
    AumentarTiempoEnemigosButton(int horda,
                              SDL_Texture *texture,
                              MousePosition &mousePosition,
                              Renderer &renderer,
                              Editor &editor);
    void draw(int number, int padding);
    bool belongsToHorda(int horda);
};


#endif //TOWERDEFENSE_AUMENTARTIEMPOENEMIGOSBUTTON_H
