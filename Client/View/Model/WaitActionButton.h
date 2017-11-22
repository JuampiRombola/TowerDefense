#ifndef TOWERDEFENSE_WAITACTIONBUTTON_H
#define TOWERDEFENSE_WAITACTIONBUTTON_H


#include "GameButton.h"

class WaitActionButton : public GameButton {
public:
    WaitActionButton(Renderer &r, TextureLoader &tl,
        int spriteKey, MousePosition &mousePosition,
        int x, int y, int w, int h, int &cmd);
        void draw() override;
private:
        void mapKey(int spriteKey);
};


#endif //TOWERDEFENSE_WAITACTIONBUTTON_H
