#include "Buttons.h"

Buttons::Buttons(MousePosition &mousePosition, Renderer &renderer, Editor
                &editor) : mousePosition(mousePosition), renderer(renderer),
                           editor(editor) {}

Buttons::~Buttons() {
    for (Button* button : buttons) {
        delete button;
    }
}

void Buttons::draw() {
    for (Button* button : buttons) {
        button->draw();
    }
}

void Buttons::addTestButton(SDL_Texture* texture) {
    Button* testButton = new TestButton(0, 0, 100, 100, texture,
                                        mousePosition, renderer);
    buttons.push_back(testButton);
}

void Buttons::addTestToggleButton(SDL_Texture *activeTexture,
                                  SDL_Texture *inactiveTexture) {
    Button* testToggleButton = new TestToggleButton(100, 0, 100, 100,
                                                    activeTexture,
                                                    inactiveTexture,
                                                    mousePosition, renderer);
    buttons.push_back(testToggleButton);
}

void Buttons::addSuperficieButtons(SDL_Texture *pradera, SDL_Texture *lava,
                                   SDL_Texture *desierto,
                                   SDL_Texture *glaciar) {
    Button* praderaButton = new SuperficieButton(0, "pradera", pradera,
                                                 mousePosition, renderer,
                                                 editor);
    buttons.push_back(praderaButton);

    Button* lavaButton = new SuperficieButton(1, "lava", lava,
                                                 mousePosition, renderer,
                                                 editor);
    buttons.push_back(lavaButton);

    Button* desiertoButton = new SuperficieButton(2, "desierto", desierto,
                                                 mousePosition, renderer,
                                                 editor);
    buttons.push_back(desiertoButton);

    Button* glaciarButton = new SuperficieButton(3, "glaciar", glaciar,
                                                 mousePosition, renderer,
                                                 editor);
    buttons.push_back(glaciarButton);
}