#include <SDL_system.h>
#include <SDL2/SDL_ttf.h>
#include "ChatView.h"

#define FONT_PATH "../Client/View/gillsansmt.ttf"
#define FONT_SIZE 18
#define MAX_LENGTH 40

#define CHAT_X 50
#define CHAT_Y 50

ChatView::ChatView(Window &w, Renderer &r) :
        window(w), renderer(r), texture(nullptr),
        textColor(SDL_Color{0, 0, 0, 0xFF}) {
    TTF_Init();
    font = TTF_OpenFont(FONT_PATH, FONT_SIZE);
    dstRect = { CHAT_X, window.getHeight() - CHAT_Y, 0, 0 };
    active = false;
}

ChatView::~ChatView() {
    TTF_CloseFont(font);
    TTF_Quit();
}

bool ChatView::isActive() {
    return active;
}

void ChatView::enable() {
    active = true;
    SDL_StartTextInput();
}

void ChatView::disable() {
    active = false;
    SDL_StopTextInput();
}

void ChatView::erase() {
    if (inputText.length() == 0)
        return;
    inputText.pop_back();
    this->renderText();
}

void ChatView::renderText() {
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, inputText.c_str(), textColor);

    if (textSurface) {
        dstRect.w = textSurface->w;
        dstRect.h = textSurface->h;
    }

    // Borro la textura existente para no perder memoria
    if (texture) SDL_DestroyTexture(texture);
    texture = SDL_CreateTextureFromSurface(renderer.getRenderer(), textSurface);

    SDL_FreeSurface( textSurface );
}

void ChatView::input(std::string &input) {
    if (inputText.size() >= MAX_LENGTH) return;
    inputText += input;
    if (inputText.size() > MAX_LENGTH)
        inputText = inputText.substr(0, MAX_LENGTH);
    this->renderText();
}

void ChatView::draw() {
    renderer.copyEuclidean(texture, nullptr, &dstRect);
}

