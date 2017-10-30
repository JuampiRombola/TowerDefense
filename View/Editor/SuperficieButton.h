#ifndef TOWERDEFENSE_SUPERFICIEBUTTON_H
#define TOWERDEFENSE_SUPERFICIEBUTTON_H

#include <string>
#include "Button.h"
#include "Editor.h"

class SuperficieButton : public Button {
private:
    int number;
    const int superficie;
    Editor &editor;
    void click();
public:
    SuperficieButton(int id, int number, const int superficie, SDL_Texture
    *texture, MousePosition &mousePosition, Renderer &renderer,
                     Editor& editor);
    ~SuperficieButton();
};


#endif //TOWERDEFENSE_SUPERFICIEBUTTON_H
