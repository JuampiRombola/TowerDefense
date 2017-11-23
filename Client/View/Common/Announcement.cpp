#include "Announcement.h"

#define ANNOUNCE_FONT_PATH "../Resources/announcement_font.ttf"
#define FONT_SCALE 25
#define OUTLINE_SIZE 1

#define ANNOUNCE_START_Y 130

Announcement::Announcement(std::string &text, Renderer &renderer)
        : text(text), time(5000),
          renderer(renderer),
          ticks(SDL_GetTicks()) {
    font = TTF_OpenFont(ANNOUNCE_FONT_PATH,
                        renderer.getWindowWidth() / FONT_SCALE);
    outlineF = TTF_OpenFont(ANNOUNCE_FONT_PATH,
                               renderer.getWindowWidth() / FONT_SCALE);
    TTF_SetFontOutline(outlineF, OUTLINE_SIZE);
    
    SDL_Color black = {0, 0, 0};
    SDL_Color yellow = {202, 164, 120};
    SDL_Surface *tOutline = TTF_RenderText_Solid(outlineF, text.c_str(), black);
    SDL_Surface *t = TTF_RenderText_Solid(font, text.c_str(), yellow);
    //SDL_Rect rect = {OUTLINE_SIZE, OUTLINE_SIZE, tOutline->w, tOutline->h};

    //SDL_SetSurfaceBlendMode(tOutline, SDL_BLENDMODE_BLEND);
    //SDL_BlitSurface(tOutline, NULL, t, &rect);

    dstRect = {renderer.getWindowWidth()/2-(t->w)/2, ANNOUNCE_START_Y, 0, 0};
    dstRect.w = t->w;
    dstRect.h = t->h;
    texture = SDL_CreateTextureFromSurface(renderer.getRenderer(), t);
    outline = SDL_CreateTextureFromSurface(renderer.getRenderer(), tOutline);
    SDL_FreeSurface(t);
    SDL_FreeSurface(tOutline);
}

void Announcement::draw() {
    renderer.copyEuclidean(outline, &dstRect);
    renderer.copyEuclidean(texture, &dstRect);
}

bool Announcement::isActive() {
    return (SDL_GetTicks() - ticks) < 3000;
}

void Announcement::Disable(){
    if (texture) SDL_DestroyTexture(texture);
    if (outline) SDL_DestroyTexture(outline);
    TTF_CloseFont(font);
    TTF_CloseFont(outlineF);
}

Announcement::~Announcement() {

}