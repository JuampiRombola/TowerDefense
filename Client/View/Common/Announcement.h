#ifndef TOWERDEFENSE_ANNOUNCEMENT_H
#define TOWERDEFENSE_ANNOUNCEMENT_H

#include <string>
#include <SDL_types.h>
#include <SDL_ttf.h>
#include "View.h"
#include "Window.h"
#include "Renderer.h"

class Announcement {
private:
    std::string text;
    Uint32 time;
    Renderer &renderer;
    TTF_Font *font;
    SDL_Texture *texture;
    SDL_Rect dstRect;
    Uint32 ticks;
public:
    Announcement(std::string &text, Renderer &renderer);
    void draw();
    bool isActive();
    void Disable();
    ~Announcement();
};


#endif //TOWERDEFENSE_ANNOUNCEMENT_H
