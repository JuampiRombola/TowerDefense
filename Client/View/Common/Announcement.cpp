#include "Announcement.h"

#define ANNOUNCE_FONT_PATH "../Resources/announcement_font.ttf"
#define FONT_SCALE 25
#define OUTLINE_SIZE 1

#define ANNOUNCE_START_Y 130

#define VICTORY "Victory!"
#define DEFEAT "Defeat!"

Announcement::Announcement(std::string &text, Renderer &renderer)
        : text(text), time(3000),
          renderer(renderer),
          ticks(SDL_GetTicks()) {
    if (text == VICTORY || text == DEFEAT)
        time = 30000;
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
    font = TTF_OpenFont(ANNOUNCE_FONT_PATH,
                        renderer.getWindowWidth() / FONT_SCALE);
    outlineF = TTF_OpenFont(ANNOUNCE_FONT_PATH,
                            renderer.getWindowWidth() / FONT_SCALE);
    TTF_SetFontOutline(outlineF, OUTLINE_SIZE);

    SDL_Color black = {0, 0, 0};
    SDL_Color yellow = {202, 164, 120};
    SDL_Surface *tOutline = TTF_RenderText_Solid(outlineF, text.c_str(), black);
    SDL_Surface *t = TTF_RenderText_Solid(font, text.c_str(), yellow);

    dstRect = {renderer.getWindowWidth()/2-(t->w)/2, ANNOUNCE_START_Y, 0, 0};
    dstRect.w = t->w;
    dstRect.h = t->h;
    texture = SDL_CreateTextureFromSurface(renderer.getRenderer(), t);
    outline = SDL_CreateTextureFromSurface(renderer.getRenderer(), tOutline);
    SDL_FreeSurface(t);
    SDL_FreeSurface(tOutline);
}
