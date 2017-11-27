#ifndef TOWERDEFENSE_CHATVIEW_H
#define TOWERDEFENSE_CHATVIEW_H

#include <SDL2/SDL_ttf.h>
#include <string>
#include "../Common/Renderer.h"
#include "../Common/TextureLoader.h"
#include "../Common/Sprite.h"
#include "TextView.h"
#include "../../include/NetCommands/CommandDispatcher.h"
#include "../../include/NonBlockingThreadSafeQueue.h"
#include <list>
#include <mutex>

class ChatView {
private:
    CommandDispatcher &dispatcher;
    Window &window;
    Renderer &renderer;
    std::string inputText;
    TTF_Font *font;
    TextView *input;
    Sprite spriteBackground;
    Sprite spriteInput;
    SDL_Color textColor;
    SDL_Texture *textureIbeam;
    SDL_Rect dstRectIbeam;
    bool active;
    int dstX;
    int dstY;
    std::list<TextView *> messages;
    std::mutex mutex;
    NonBlockingThreadSafeQueue<std::string*> _messagesToAdd;
    bool visible;
    int offsetResolution;

public:
    ChatView(CommandDispatcher &d, Window &w, Renderer &r, TextureLoader &tl);
    ~ChatView();
    bool isActive();
    void enable();
    void disable();
    void erase();
    void renderText();
    void newInput(std::string &entry);
    void draw();
    void addMessage(std::string &msg);
    void MessageFrom(std::string &msg, std::string &playerName);

private:
    void initialMessages();
};


#endif //TOWERDEFENSE_CHATVIEW_H
