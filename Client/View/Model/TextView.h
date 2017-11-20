#ifndef TOWERDEFENSE_TEXTVIEW_H
#define TOWERDEFENSE_TEXTVIEW_H

#include <SDL2/SDL_ttf.h>
#include <string>
#include "../Common/Renderer.h"

class TextView {
private:
    Renderer &renderer;
    SDL_Texture *texture;
    SDL_Rect dstRect;
public:
    TextView(Renderer &r, TTF_Font *font,
             const std::string &msg, SDL_Color &color);
    ~TextView();
    void setDestXY(int x, int y);
    int getDestW();
    int getDestH();
    void draw();
};


#endif //TOWERDEFENSE_TEXTVIEW_H
