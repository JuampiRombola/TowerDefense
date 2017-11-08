#ifndef TOWERDEFENSE_CONTADORENEMIGOSINPUT_H
#define TOWERDEFENSE_CONTADORENEMIGOSINPUT_H

#include <string>
#include "../Common/Text.h"
#include "Editor.h"

class ContadorEnemigosInput : public Text {
private:
    int horda;
    std::string enemigo;
    Editor &editor;
public:
    ContadorEnemigosInput(int horda, std::string enemigo, SDL_Texture *texture,
                          Renderer &renderer, Editor &editor);

    void draw(int number);
    bool belongsToHorda(int horda);
};


#endif //TOWERDEFENSE_CONTADORENEMIGOSINPUT_H
