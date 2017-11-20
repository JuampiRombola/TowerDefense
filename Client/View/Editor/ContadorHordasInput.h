#ifndef TOWERDEFENSE_CONTADORHORDASINPUT_H
#define TOWERDEFENSE_CONTADORHORDASINPUT_H

#include "../Common/Text.h"

class ContadorHordasInput : public Text {
private:
    int horda;
public:
    ContadorHordasInput(int horda, SDL_Texture *texture,
            Renderer &renderer);
    void draw(int number, int padding);
    bool belongsToHorda(int horda);
};


#endif //TOWERDEFENSE_CONTADORHORDASINPUT_H
