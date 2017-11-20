#include "TextView.h"

TextView::TextView(Renderer &r, TTF_Font *font,
                   const std::string &msg, SDL_Color &color) :
        renderer(r) {
    SDL_Surface *t = TTF_RenderText_Solid(font, msg.c_str(), color);
    dstRect = {0, 0, 0, 0};
    dstRect.w = t->w;
    dstRect.h = t->h;
    texture = SDL_CreateTextureFromSurface(r.getRenderer(), t);
    SDL_FreeSurface(t);
}

TextView::~TextView() {
    if (texture) SDL_DestroyTexture(texture);
}

void TextView::setDestXY(int x, int y) {
    dstRect.x = x;
    dstRect.y = y;
}

int TextView::getDestW() {
    return dstRect.w;
}

int TextView::getDestH() {
    return  dstRect.h;
}

void TextView::draw() {
    renderer.copyEuclidean(texture, &dstRect);
}
