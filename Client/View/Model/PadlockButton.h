#ifndef TOWERDEFENSE_PADLOCKBUTTON_H
#define TOWERDEFENSE_PADLOCKBUTTON_H


#include "../Common/TextureLoader.h"
#include "GameButton.h"

class PadlockButton : public GameButton {
public:
    PadlockButton(Renderer &r, TextureLoader &tl,
                  MousePosition &mousePosition,
                  int x, int y, int w, int h);
    void draw() override;
    void click() override;
};


#endif //TOWERDEFENSE_PADLOCKBUTTON_H
