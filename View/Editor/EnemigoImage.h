#ifndef TOWERDEFENSE_ENEMIGOIMAGE_H
#define TOWERDEFENSE_ENEMIGOIMAGE_H


#include "../Common/Image.h"

class EnemigoImage : public Image {
private:
    int horda;
public:
    EnemigoImage(int horda, SDL_Texture *texture, Renderer &renderer);
    virtual void draw(int number);
    bool belongsToHorda(int hordaNro);
};


#endif //TOWERDEFENSE_ENEMIGOIMAGE_H
