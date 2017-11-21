#include "Announcement.h"

#define FONT_PATH "../Resources/announcement_font.ttf"
#define FONT_SIZE 100

Announcement::Announcement(std::string &text, Renderer &renderer)
        : text(text), time(5000),
          renderer(renderer),
          ticks(SDL_GetTicks()) {
    font = TTF_OpenFont(FONT_PATH, FONT_SIZE);
    SDL_Surface *t = TTF_RenderText_Solid(font, text.c_str(),
                                          SDL_Color{0, 0, 0, 0xFF});
    dstRect = SDL_Rect{0, 0, 0, 0};
    dstRect.w = t->w;
    dstRect.h = t->h;
    texture = SDL_CreateTextureFromSurface(renderer.getRenderer(), t);
    SDL_FreeSurface(t);
}

void Announcement::draw() {
    renderer.copyEuclidean(texture, &dstRect);
}

bool Announcement::isActive() {
    return (SDL_GetTicks() - ticks) < 3000;
}

Announcement::~Announcement() {
    TTF_CloseFont(font);
}