#include <SDL_system.h>
#include <SDL2/SDL_ttf.h>
#include "ChatView.h"
#include "../Common/SpriteNamesConfig.h"
#include "ViewConstants.h"

#define FONT_PATH "../Resources/font.ttf"
#define FONT_SIZE 10
#define MAX_LENGTH 57

#define CHAT_PAD 20

#define CHAT_W 416
#define CHAT_H 156

#define OFFSET_Y_IBEAM 1
#define OFFSET_X_IBEAM 3

ChatView::ChatView(Window &w, Renderer &r, TextureLoader &tl) :
        window(w), renderer(r), texture(nullptr),
        spriteBackground(tl.getTexture(CHAT_BG), r),
        spriteInput(tl.getTexture(CHAT_INPUT), r),
        textColor(SDL_Color{255, 255, 255, 0xFF}), active(false) {
    TTF_Init();
    font = TTF_OpenFont(FONT_PATH, FONT_SIZE);

    int chatY = window.getHeight() - CHAT_H - PADDING_HUD;
    spriteBackground.setSourceRect(0, 0, CHAT_W, CHAT_H);
    spriteBackground.setDestRect(PADDING_HUD, chatY, CHAT_W, CHAT_H);
    spriteInput.setSourceRect(0, 0, CHAT_W, CHAT_H);
    spriteInput.setDestRect(PADDING_HUD, chatY, CHAT_W, CHAT_H);

    dstRect = { PADDING_HUD * 4 , window.getHeight() - CHAT_PAD, 0, 0 };

    SDL_Surface *textSurface = TTF_RenderText_Solid(font, "|", textColor);
    textureIbeam = SDL_CreateTextureFromSurface(renderer.getRenderer(),
                                                textSurface);
    dstRectIbeam = { dstRect.x - OFFSET_X_IBEAM, dstRect.y - OFFSET_Y_IBEAM,
                     textSurface->w, textSurface->h + OFFSET_Y_IBEAM};
    SDL_FreeSurface(textSurface);
}

ChatView::~ChatView() {
    TTF_CloseFont(font);
    TTF_Quit();
    if (textureIbeam) SDL_DestroyTexture(textureIbeam);
}

bool ChatView::isActive() {
    return active;
}

void ChatView::enable() {
    active = true;
    SDL_StartTextInput();
    dstRectIbeam.x = dstRect.x - OFFSET_X_IBEAM;
}

void ChatView::disable() {
    active = false;
    SDL_StopTextInput();
    inputText = "";
    if (texture) SDL_DestroyTexture(texture);
    texture = nullptr;
}

void ChatView::erase() {
    if (inputText.length() == 0)
        return;
    inputText.pop_back();
    this->renderText();
}

void ChatView::renderText() {
    SDL_Surface *textSurface = TTF_RenderText_Solid(font,
                                                    inputText.c_str(),
                                                    textColor);

    if (textSurface) {
        dstRect.w = textSurface->w;
        dstRect.h = textSurface->h;
        dstRectIbeam.x = dstRect.x + dstRect.w - OFFSET_X_IBEAM;
    }

    // Borro la textura existente para no perder memoria
    if (texture) SDL_DestroyTexture(texture);
    texture = SDL_CreateTextureFromSurface(renderer.getRenderer(),
                                           textSurface);

    SDL_FreeSurface(textSurface);
}

void ChatView::input(std::string &input) {
    if (inputText.size() >= MAX_LENGTH) return;
    inputText += input;
    if (inputText.size() > MAX_LENGTH)
        inputText = inputText.substr(0, MAX_LENGTH);
    this->renderText();
}

void ChatView::draw() {
    spriteBackground.drawEuclidian();
    if (active) {
        spriteInput.drawEuclidian();
        renderer.copyEuclidean(texture, nullptr, &dstRect);
        if (((SDL_GetTicks() / 600) % 2) == 0)
            renderer.copyEuclidean(textureIbeam, nullptr, &dstRectIbeam);
        if (inputText.size() >= MAX_LENGTH)
            renderer.copyEuclidean(textureIbeam, nullptr, &dstRectIbeam);
    }
}
