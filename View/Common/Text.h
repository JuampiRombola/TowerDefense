#ifndef TOWERDEFENSE_TEXTINPUT_H
#define TOWERDEFENSE_TEXTINPUT_H

#include "Image.h"

class Text : public Image {
protected:
    std::string text;

public:
    Text(int posX, int posY, int width, int height,
              SDL_Texture *texture, Renderer &renderer);

    virtual void draw();

};


#endif //TOWERDEFENSE_TEXTINPUT_H
