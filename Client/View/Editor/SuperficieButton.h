#ifndef TOWERDEFENSE_SUPERFICIEBUTTON_H
#define TOWERDEFENSE_SUPERFICIEBUTTON_H

#include <string>
#include "../Common/Button.h"
#include "Editor.h"

class SuperficieButton : public Button {
private:
    const int superficie;
    Editor &editor;
    void click();
public:
    SuperficieButton(const int superficie,
                         SDL_Texture *texture,
                         MousePosition &mousePosition,
                         Renderer &renderer, Editor &editor);
    void draw(int number, int padding);
};


#endif //TOWERDEFENSE_SUPERFICIEBUTTON_H
