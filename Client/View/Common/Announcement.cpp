#include "Announcement.h"

#define ANNOUNCE_FONT_PATH "../Resources/announcement_font.ttf"
#define MONOSPACE_FONT_PATH "../Resources/font.ttf"
#define FONT_SCALE 25
#define OUTLINE_SIZE 1

#define ANNOUNCE_START_Y 130

#define VICTORY "Victory!"
#define DEFEAT "Defeat!"

Announcement::Announcement(std::string &text, Renderer &renderer)
        : text(text), time(3000),
          renderer(renderer),
          ticks(SDL_GetTicks()),
          fontSize(renderer.getWindowWidth() / FONT_SCALE),
          front(SDL_Color{202, 164, 120}), back(SDL_Color{0, 0, 0}) {
    if (text == VICTORY || text == DEFEAT)
        time = 30000;
    font = TTF_OpenFont(ANNOUNCE_FONT_PATH, fontSize);
    outlineF = TTF_OpenFont(ANNOUNCE_FONT_PATH, fontSize);
    this->createTexture();
}

Announcement::Announcement(std::string &text, Renderer &renderer, int size) :
        text(text), renderer(renderer), fontSize(size),
        front(SDL_Color{255, 255, 255}), back(SDL_Color{0, 0, 0}) {
    font = TTF_OpenFont(MONOSPACE_FONT_PATH, fontSize);
    outlineF = TTF_OpenFont(MONOSPACE_FONT_PATH, fontSize);
    this->createTexture();
}

void Announcement::draw() {
    renderer.copyEuclidean(outline, &dstRect);
    renderer.copyEuclidean(texture, &dstRect);
}

bool Announcement::isActive() {
    return (SDL_GetTicks() - ticks) < time;
}

void Announcement::Disable(){
    if (texture) SDL_DestroyTexture(texture);
    if (outline) SDL_DestroyTexture(outline);
    TTF_CloseFont(font);
    TTF_CloseFont(outlineF);
}

Announcement::~Announcement() {

}

void Announcement::createTexture() {
    TTF_SetFontOutline(outlineF, OUTLINE_SIZE);

    SDL_Surface *tOutline = TTF_RenderText_Solid(outlineF, text.c_str(), back);
    SDL_Surface *t = TTF_RenderText_Solid(font, text.c_str(), front);

    dstRect = {renderer.getWindowWidth()/2-(t->w)/2, ANNOUNCE_START_Y, 0, 0};
    dstRect.w = t->w;
    dstRect.h = t->h;
    texture = SDL_CreateTextureFromSurface(renderer.getRenderer(), t);
    outline = SDL_CreateTextureFromSurface(renderer.getRenderer(), tOutline);
    SDL_FreeSurface(t);
    SDL_FreeSurface(tOutline);
}

void Announcement::setDestXY(int x, int y) {
    dstRect.x = x;
    dstRect.y = y;
}

