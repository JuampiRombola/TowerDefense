#ifndef TOWERDEFENSE_INSTANTBUTTON_H
#define TOWERDEFENSE_INSTANTBUTTON_H


#include "GameButton.h"

class InstantButton : public GameButton {
    bool active;
public:
    InstantButton(Renderer &r, TextureLoader &tl,
                  int spriteKey, MousePosition &mousePosition,
                  int x, int y, int w, int h, int &cmd);
    void draw() override;
    void click() override;
    void desactivate();
private:
    void mapKey(int spriteKey);
};


#endif //TOWERDEFENSE_INSTANTBUTTON_H
