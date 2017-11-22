#include "Announcement.h"

#define ANNOUNCE_FONT_PATH "../Resources/announcement_font.ttf"
#define FONT_SCALE 25

#define ANNOUNCE_START_X 200
#define ANNOUNCE_START_Y 130

Announcement::Announcement(std::string &text, Renderer &renderer)
        : text(text), time(5000),
          renderer(renderer),
          ticks(SDL_GetTicks()) {
    font = TTF_OpenFont(ANNOUNCE_FONT_PATH,
                        renderer.getWindowWidth() / FONT_SCALE);
    SDL_Surface *t = TTF_RenderText_Solid(font, text.c_str(),
                                          SDL_Color{0, 0, 0, 0xFF});
    dstRect = SDL_Rect{renderer.getWindowWidth()/2 - (t->w)/2,
                       ANNOUNCE_START_Y, 0, 0};
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

void Announcement::Disable(){
    if (texture) SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}

Announcement::~Announcement() {

}