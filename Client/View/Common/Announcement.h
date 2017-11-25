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
    TTF_Font *outlineF;
    SDL_Texture *texture;
    SDL_Texture *outline;
    SDL_Rect dstRect;
    Uint32 ticks;
    int fontSize;
    SDL_Color front;
    SDL_Color back;
public:
    Announcement(std::string &text, Renderer &renderer);
    Announcement(std::string &text, Renderer &renderer, int size);
    void draw();
    bool isActive();
    void Disable();
    ~Announcement();
    void setDestXY(int x, int y);
private:
    void createTexture();
};


#endif //TOWERDEFENSE_ANNOUNCEMENT_H
