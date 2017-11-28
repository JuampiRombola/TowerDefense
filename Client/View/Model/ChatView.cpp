#include <SDL_system.h>
#include <SDL2/SDL_ttf.h>
#include "ChatView.h"
#include "../Common/SpriteNamesConfig.h"
#include "ViewConstants.h"
#include "../../../Common/Lock.h"
#include "../../include/NetCommands/ChatMessageCommand.h"
#include "../../../Common/Paths.h"

#define FONT_PATH "Fonts/font.ttf"
#define FONT_SIZE 10
#define MAX_LENGTH 49
#define MAX_SIZE 8

#define CHAT_PAD 20
#define MSG_OFFSET 23
#define TEXT_H 14

#define SRC_CHAT_W 416
#define SRC_CHAT_H 156

#define CHAT_W 358
#define CHAT_H 150

#define OFFSET_Y_IBEAM 1
#define OFFSET_X_IBEAM 3

#define MIN_RESOLUTION 1152

#define CMD_HIDE_CHAT "/hide"
#define CMD_SHOW_CHAT "/show"

ChatView::ChatView(CommandDispatcher &d, Window &w,
                   Renderer &r, TextureLoader &tl) :
        dispatcher(d), window(w), renderer(r), input(nullptr),
        spriteBackground(tl.getTexture(CHAT_BG), r),
        spriteInput(tl.getTexture(CHAT_INPUT), r),
        textColor(SDL_Color{255, 255, 255, 0xFF}), active(false),
        _messagesToAdd(), visible(true), offsetResolution(0) {
    font = TTF_OpenFont((PATH_RESOURCES + std::string("")
                         + FONT_PATH).c_str(), FONT_SIZE);

    if (window.getWidth() < MIN_RESOLUTION)
        offsetResolution = HUD_BUTTON_Y + MARQUESINA_H;

    dstX = PADDING_HUD * 3;
    dstY = window.getHeight() - CHAT_PAD - offsetResolution;

    int chatY = window.getHeight() - CHAT_H - offsetResolution;
    spriteBackground.setSourceRect(0, 0, CHAT_W, CHAT_H);
    spriteBackground.setDestRect(0, chatY, CHAT_W, CHAT_H);
    spriteInput.setSourceRect(0, 0, SRC_CHAT_W, SRC_CHAT_H);
    spriteInput.setDestRect(0, chatY, CHAT_W, CHAT_H);

    SDL_Surface *t = TTF_RenderText_Solid(font, "|", textColor);
    textureIbeam = SDL_CreateTextureFromSurface(renderer.getRenderer(), t);
    dstRectIbeam = { dstX - OFFSET_X_IBEAM, dstY - OFFSET_Y_IBEAM,
                     t->w, t->h + OFFSET_Y_IBEAM};
    SDL_FreeSurface(t);
    this->initialMessages();
}

ChatView::~ChatView() {
    if (textureIbeam) SDL_DestroyTexture(textureIbeam);
    if (input) delete input;

    for (int i=0; i < messages.size(); ++i) {
        delete messages.front();
        messages.pop_front();
    }
}

bool ChatView::isActive() {
    Lock(this->mutex);

    return active;
}

void ChatView::enable() {
    SDL_StartTextInput();

    Lock(this->mutex);

    active = true;
    dstRectIbeam.x = dstX - OFFSET_X_IBEAM;
}

void ChatView::disable() {
    SDL_StopTextInput();

    Lock(this->mutex);

    active = false;
    if (!inputText.empty()) {
        if (inputText == CMD_HIDE_CHAT) {
            visible = false;
        } else if ((inputText == CMD_SHOW_CHAT)) {
            visible = true;
        } else {
            // Reemplazar esta funcion por comando al servidor
            // dispatcher
            //this->addMessage(inputText);
            this->dispatcher.QueueCommand(new ChatMessageCommand(inputText));
        }
    }
    inputText = "";
    if (input) delete input;
    input = nullptr;
}

void ChatView::erase() {
    Lock(this->mutex);

    if (inputText.empty()) return;
    inputText.pop_back();
    if (inputText.empty())
        dstRectIbeam.x = dstX - OFFSET_X_IBEAM;
    this->renderText();
}

void ChatView::renderText() {
    Lock(this->mutex);
    if (input) delete input;
    input = nullptr;
    if (inputText.empty()) return;
    input = new TextView(renderer, font, inputText,textColor);
    input->setDestXY(dstX, dstY);
    dstRectIbeam.x = dstX + input->getDestW() - OFFSET_X_IBEAM;
}

void ChatView::newInput(std::string &entry) {
    Lock(this->mutex);
    if (!active) return;
    if (inputText.size() >= MAX_LENGTH) return;
    inputText += entry;
    if (inputText.size() > MAX_LENGTH)
        inputText = inputText.substr(0, MAX_LENGTH);
    this->renderText();
}

void ChatView::draw() {
    std::string* s = _messagesToAdd.Dequeue();
    while(s != nullptr){
        addMessage(*s);
        std::cout << *s << std::endl << std::flush;
        delete s;
        s = _messagesToAdd.Dequeue();
    }

    if (visible)
        spriteBackground.drawEuclidian();

    if (active) {
        spriteInput.drawEuclidian();
        if (input) input->draw();
        if (((SDL_GetTicks() / 600) % 2) == 0)
            renderer.copyEuclidean(textureIbeam, &dstRectIbeam);
        if (inputText.size() >= MAX_LENGTH)
            renderer.copyEuclidean(textureIbeam, &dstRectIbeam);
    }
    
    if (!visible) return; 
    Lock(this->mutex);
    int i = 0;
    for (auto it= messages.rbegin(); it != messages.rend(); ++it) {
        (*it)->setDestXY(dstX, dstY-MSG_OFFSET-(TEXT_H * i++));
        (*it)->draw();
    }
}

void ChatView::MessageFrom(std::string &msg, std::string &playerName) {
    std::string* s = new std::string(playerName + ": " + msg);
    _messagesToAdd.Queue(s);
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

void ChatView::initialMessages() {
    std::string m = "Bienvenido a Tower Defense v1.0";
    std::string i = "Para usar chat presiona Enter";
    std::string h = "Para ocultar el chat utiliza el comando /hide";
    std::string j = "Para mostrarlo, el comando /show";
    std::string s = " ";
    addMessage(m);
    addMessage(i);
    addMessage(h);
    addMessage(j);
    addMessage(s);
    addMessage(s);
    addMessage(s);
    addMessage(s);
}
