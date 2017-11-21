#ifndef TOWERDEFENSE_CONTADORTIEMPOENEMIGOSINPUT_H
#define TOWERDEFENSE_CONTADORTIEMPOENEMIGOSINPUT_H


#include "../Common/Text.h"
#include "Editor.h"

class ContadorTiempoEnemigosInput : public Text {
private:
    int horda;
    Editor &editor;
public:
    ContadorTiempoEnemigosInput(int horda, SDL_Texture *texture,
                             Renderer &renderer, Editor &editor);

    void draw(int number, int padding);
    bool belongsToHorda(int horda);
};


#endif //TOWERDEFENSE_CONTADORTIEMPOENEMIGOSINPUT_H
