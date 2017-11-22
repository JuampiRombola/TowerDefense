#ifndef TOWERDEFENSE_GAMEBUTTON_H
#define TOWERDEFENSE_GAMEBUTTON_H


#include "../Common/Button.h"
#include "ProgressBarView.h"
#include "../Common/TextureLoader.h"

class GameButton : public Button {
protected:
    Image edge;
    Image background;
    ProgressBarView bar;
    int &cmd;
    int key;

public:
    GameButton(Renderer &r, TextureLoader &tl,
               int spriteKey, MousePosition &mousePosition,
               int x, int y, int w, int h, int &cmd);
    virtual void draw();
    void click() override;
    void setTotalProgressBar(Uint32 t);
    void setPartProgressBar(Uint32 p);
};


#endif //TOWERDEFENSE_GAMEBUTTON_H
