#ifndef TOWERDEFENSE_EXITVIEW_H
#define TOWERDEFENSE_EXITVIEW_H


#include "../Common/Sprite.h"
#include "../Common/TextureLoader.h"
#include "../Common/MousePosition.h"

class ExitView {
private:
    Sprite imageExit;
    MousePosition &mousePosition;
    bool active;
public:
    ExitView(Renderer &renderer, TextureLoader &tl, MousePosition &mp);
    bool isActive();
    void activate();
    void desactivate();
    bool isOk();
    bool isCancel();
    void draw();
private:
    bool isClicked(int offsetX);
};


#endif //TOWERDEFENSE_EXITVIEW_H
