#ifndef TOWERDEFENSE_PROGRESSBARVIEW_H
#define TOWERDEFENSE_PROGRESSBARVIEW_H


#include "../Common/Sprite.h"

class ProgressBarView {
private:
    Renderer &renderer;
    int srcW;
    int srcH;
    int dstW;
    int dstH;
    Sprite bar;
    Uint32 total;
    Uint32 part;
public:
    ProgressBarView(Renderer &r, SDL_Texture *t,
                    int srcW, int srcH,
                    int dstW, int dstH);
    void draw();
    void setTotal(Uint32 t);
    void setPart(Uint32 p);
    void setDestXY(int x, int y);
    bool isFull();
};


#endif //TOWERDEFENSE_PROGRESSBARVIEW_H
