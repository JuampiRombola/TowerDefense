#ifndef TOWERDEFENSE_CHATVIEW_H
#define TOWERDEFENSE_CHATVIEW_H

#include <SDL2/SDL_ttf.h>
#include <string>
#include "../Common/Renderer.h"
#include "../Common/TextureLoader.h"
#include "../Common/Sprite.h"

class ChatView {
private:
    Window &window;
    Renderer &renderer;
    std::string inputText;
    TTF_Font *font;
    SDL_Texture *texture;
    Sprite spriteBackground;
    Sprite spriteInput;
    SDL_Color textColor;
    SDL_Texture *textureIbeam;
    SDL_Rect dstRect;
    SDL_Rect dstRectIbeam;
    bool active;

public:
    ChatView(Window &w, Renderer &r, TextureLoader &tl);
    ~ChatView();
    bool isActive();
    void enable();
    void disable();
    void erase();
    void renderText();
    void input(std::string &input);
    void draw();
};


#endif //TOWERDEFENSE_CHATVIEW_H
