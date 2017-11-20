#include <SDL_system.h>
#include <SDL2/SDL_ttf.h>
#include "ChatView.h"
#include "../Common/SpriteNamesConfig.h"
#include "ViewConstants.h"
#include "../../../Common/Lock.h"

#define FONT_PATH "../Resources/font.ttf"
#define FONT_SIZE 10
#define MAX_LENGTH 57
#define MAX_SIZE 9

#define CHAT_PAD 20
#define MSG_OFFSET 23
#define TEXT_H 14

#define CHAT_W 416
#define CHAT_H 156

#define OFFSET_Y_IBEAM 1
#define OFFSET_X_IBEAM 3

ChatView::ChatView(CommandDispatcher &d, Window &w,
                   Renderer &r, TextureLoader &tl) :
        dispatcher(d), window(w), renderer(r), input(nullptr),
        spriteBackground(tl.getTexture(CHAT_BG), r),
        spriteInput(tl.getTexture(CHAT_INPUT), r),
        textColor(SDL_Color{255, 255, 255, 0xFF}), active(false),
        dstX(PADDING_HUD * 4), dstY(window.getHeight() - CHAT_PAD) {
    TTF_Init();
    font = TTF_OpenFont(FONT_PATH, FONT_SIZE);

    int chatY = window.getHeight() - CHAT_H - PADDING_HUD;
    spriteBackground.setSourceRect(0, 0, CHAT_W, CHAT_H);
    spriteBackground.setDestRect(PADDING_HUD, chatY, CHAT_W, CHAT_H);
    spriteInput.setSourceRect(0, 0, CHAT_W, CHAT_H);
    spriteInput.setDestRect(PADDING_HUD, chatY, CHAT_W, CHAT_H);

    SDL_Surface *t = TTF_RenderText_Solid(font, "|", textColor);
    textureIbeam = SDL_CreateTextureFromSurface(renderer.getRenderer(), t);
    dstRectIbeam = { dstX - OFFSET_X_IBEAM, dstY - OFFSET_Y_IBEAM,
                     t->w, t->h + OFFSET_Y_IBEAM};
    SDL_FreeSurface(t);
}

ChatView::~ChatView() {
    TTF_CloseFont(font);
    TTF_Quit();
    if (textureIbeam) SDL_DestroyTexture(textureIbeam);
    if (input) delete input;

    auto it = messages.begin();
    while (it != messages.end())
        delete (*it++);
}

bool ChatView::isActive() {
    return active;
}

void ChatView::enable() {
    active = true;
    SDL_StartTextInput();
    dstRectIbeam.x = dstX - OFFSET_X_IBEAM;
}

void ChatView::disable() {
    active = false;
    SDL_StopTextInput();
    if (!inputText.empty()) {
        // Reemplazar esta funcion por comando al servidor
        // dispatcher
        this->addMessage(inputText);
    }
    inputText = "";
    if (input) delete input;
    input = nullptr;
}

void ChatView::erase() {
    if (inputText.empty()) return;
    inputText.pop_back();
    if (inputText.empty())
        dstRectIbeam.x = dstX - OFFSET_X_IBEAM;
    this->renderText();
}

void ChatView::renderText() {
    if (input) delete input;
    input = nullptr;
    if (inputText.empty()) return;
    input = new TextView(renderer, font, inputText,textColor);
    input->setDestXY(dstX, dstY);
    dstRectIbeam.x = dstX + input->getDestW() - OFFSET_X_IBEAM;
}

void ChatView::newInput(std::string &entry) {
    if (inputText.size() >= MAX_LENGTH) return;
    inputText += entry;
    if (inputText.size() > MAX_LENGTH)
        inputText = inputText.substr(0, MAX_LENGTH);
    this->renderText();
}

void ChatView::draw() {
    spriteBackground.drawEuclidian();

    if (active) {
        spriteInput.drawEuclidian();
        if (input )input->draw();
        if (((SDL_GetTicks() / 600) % 2) == 0)
            renderer.copyEuclidean(textureIbeam, &dstRectIbeam);
        if (inputText.size() >= MAX_LENGTH)
            renderer.copyEuclidean(textureIbeam, &dstRectIbeam);
    }
    int i = 0;
    Lock(this->mutex);
    for (auto it= messages.rbegin(); it != messages.rend(); ++it) {
        (*it)->setDestXY(dstX, dstY-MSG_OFFSET-(TEXT_H * i++));
        (*it)->draw();
    }
}

void ChatView::addMessage(std::string &m) {
    Lock(this->mutex);
    TextView *t;
    for (int i=MAX_SIZE; i <= (messages.size()+m.size()/(MAX_LENGTH+1)); ++i){
        t = messages.front();
        messages.pop_front();
        delete t;
    }
    for (unsigned long i=0; i<= (m.size()/(MAX_LENGTH+1)); ++i) {
        std::string msg= m.substr(i*MAX_LENGTH, MAX_LENGTH);
        t = new TextView(renderer, font, msg, textColor);
        messages.push_back(t);
    }
}
