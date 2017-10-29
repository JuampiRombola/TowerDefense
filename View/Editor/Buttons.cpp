#include "Buttons.h"

Buttons::Buttons(MousePosition &mousePosition, Renderer &renderer,
                 Editor &editor, TextureLoader &textureLoader, KeyboardInput
                 &keyboardInput) : mousePosition(
        mousePosition), renderer(renderer), editor(editor), textureLoader(
        textureLoader), keyboardInput(keyboardInput), nextId(0) {}

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

void Buttons::addSuperficieButtons() {
    Button *praderaButton = new SuperficieButton(++nextId, 0, "pradera",
                                                 textureLoader.getTexture(PRADERA_EDITOR),
                                                 mousePosition,
                                                 renderer, editor);
    buttons.push_back(praderaButton);

    Button *lavaButton = new SuperficieButton(++nextId, 1, "lava",
                                              textureLoader.getTexture(VOLCAN_EDITOR),
                                              mousePosition, renderer, editor);
    buttons.push_back(lavaButton);

    Button *desiertoButton = new SuperficieButton(++nextId, 2, "desierto",
                                                  textureLoader.getTexture
                                                          (DESIERTO_EDITOR),
                                                  mousePosition,
                                                  renderer, editor);
    buttons.push_back(desiertoButton);

    Button *glaciarButton = new SuperficieButton(++nextId, 3, "glaciar",
                                                 textureLoader.getTexture
                                                         (GELIDO_EDITOR),
                                                 mousePosition,
                                                 renderer, editor);
    buttons.push_back(glaciarButton);

    Button *text = new TextInput(++nextId, 100, 50, 500, 0, textureLoader
            .getTexture(FONT), mousePosition, renderer);
    buttons.push_back(text);
}

void Buttons::addNuevaHordaButton() {
    Button *button = new NuevaHordaButton(++nextId, textureLoader.getTexture
                                                  (AGREGAR_HORDA_BTN),
                                          mousePosition,
                                          renderer, editor);
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
    Button *button = new AgregarEnemigoButton(++nextId, horda, "abmonible",
                                              textureLoader.getTexture(ABMONIBLE_SUMA),
                                              mousePosition, renderer, editor);
    hordasButtons.push_back(button);

    Button *deleteAbmonible = new EliminarEnemigoButton(++nextId, horda,
                                                        "abmonible",
                                                        textureLoader.getTexture(
                                                                ABMONIBLE_RESTA),
                                                        mousePosition, renderer,
                                                        editor);
    hordasButtons.push_back(deleteAbmonible);

    Button *eliminarHordaButton = new EliminarHordaButton(++nextId, horda,
                                                          textureLoader.getTexture(
                                                                  ELIMINAR_HORDA_BTN),
                                                          mousePosition,
                                                          renderer, editor);
    hordasButtons.push_back(eliminarHordaButton);
}