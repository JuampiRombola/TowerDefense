#include "Buttons.h"

Buttons::Buttons(MousePosition &mousePosition, Renderer &renderer,
                 Editor &editor, TextureLoader &textureLoader) : mousePosition(
        mousePosition), renderer(renderer), editor(editor), textureLoader(
        textureLoader) {}

Buttons::~Buttons() {
    for (Button *button : buttons) {
        delete button;
    }
    for (Button *button : hordasButtons) {
        delete button;
    }
}

void Buttons::draw() {
    for (Button *button : buttons) {
        button->draw();
    }
    for (Button *button : hordasButtons) {
        button->draw();
    }
}

void Buttons::addSuperficieButtons(SDL_Texture *pradera, SDL_Texture *lava,
                                   SDL_Texture *desierto,
                                   SDL_Texture *glaciar) {
    Button *praderaButton = new SuperficieButton(0, "pradera", pradera,
                                                 mousePosition, renderer,
                                                 editor);
    buttons.push_back(praderaButton);

    Button *lavaButton = new SuperficieButton(1, "lava", lava, mousePosition,
                                              renderer, editor);
    buttons.push_back(lavaButton);

    Button *desiertoButton = new SuperficieButton(2, "desierto", desierto,
                                                  mousePosition, renderer,
                                                  editor);
    buttons.push_back(desiertoButton);

    Button *glaciarButton = new SuperficieButton(3, "glaciar", glaciar,
                                                 mousePosition, renderer,
                                                 editor);
    buttons.push_back(glaciarButton);
}

void Buttons::addNuevaHordaButton(SDL_Texture *texture) {
    Button *button = new NuevaHordaButton(texture, mousePosition, renderer,
                                          editor);
    buttons.push_back(button);
}

void Buttons::cleanHordasButtons() {
    if (hordasButtons.empty())
        return;
    for (Button *button : hordasButtons) {
        delete button;
    }
    hordasButtons = std::list<Button *>();
}

void Buttons::addEnemigosButton(int horda) {
    Button *button = new AgregarEnemigoButton(horda, "abmonible",
                                              textureLoader.getTexture(11),
                                              mousePosition, renderer, editor);
    hordasButtons.push_back(button);

    Button *deleteAbmonible = new EliminarEnemigoButton(horda, "abmonible",
                                                   textureLoader.getTexture(12),
                                                   mousePosition, renderer,
                                                   editor);
    hordasButtons.push_back(deleteAbmonible);
}