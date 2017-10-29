#ifndef TOWERDEFENSE_TEXTINPUT_H
#define TOWERDEFENSE_TEXTINPUT_H


#include "Button.h"

class TextInput : public Button {
private:
    std::string text;

    void click();

public:
    TextInput(int id, int posX, int posY, int width, int height,
              SDL_Texture *texture, MousePosition &mousePosition,
              Renderer &renderer);

    void draw();

    std::string &getInput();

    ~TextInput();
};



#endif //TOWERDEFENSE_TEXTINPUT_H
