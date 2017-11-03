#include "Buttons.h"
#include "AgregarCaminoButton.h"

Buttons::Buttons(MousePosition &mousePosition, Renderer &renderer,
                 Editor &editor, TextureLoader &textureLoader, KeyboardInput
                 &keyboardInput) : mousePosition(
        mousePosition), renderer(renderer), editor(editor), textureLoader(
        textureLoader), keyboardInput(keyboardInput), nextId(0) {}


// QUE ASCOOOOOOOOOO
Buttons::~Buttons() {
    for (Button *button : buttons) {
        delete button;
    }
    for (Button *button : hordasButtons) {
        delete button;
    }
    for (Image *image : images) {
        delete image;
    }
}

// QUE ASCOOOOOOOOOO X2 (Bah, toda la clase es horrible)
void Buttons::draw() {
    for (Button *button : buttons) {
        button->draw();
    }
    for (Button *button : hordasButtons) {
        button->draw();
    }
    // Será este el que tiene que quedar? Help Martín
    for (Image *image : images) {
        image->draw();
    }
}

void Buttons::addSuperficieButtons() {
    Button *praderaButton = new SuperficieButton(++nextId, 0, PRADERA,
                                                 textureLoader.getTexture(PRADERA),
                                                 mousePosition,
                                                 renderer, editor);
    buttons.push_back(praderaButton);

    Button *lavaButton = new SuperficieButton(++nextId, 1, VOLCAN,
                                              textureLoader.getTexture(VOLCAN),
                                              mousePosition, renderer, editor);
    buttons.push_back(lavaButton);

    Button *desiertoButton = new SuperficieButton(++nextId, 2, DESIERTO,
                                                  textureLoader.getTexture
                                                          (DESIERTO),
                                                  mousePosition,
                                                  renderer, editor);
    buttons.push_back(desiertoButton);

    Button *glaciarButton = new SuperficieButton(++nextId, 3, GELIDO,
                                                 textureLoader.getTexture
                                                         (GELIDO),
                                                 mousePosition,
                                                 renderer, editor);
    buttons.push_back(glaciarButton);

    Button *pathTileButton = new AgregarCaminoButton(++nextId, textureLoader
            .getTexture(VOLCAN_PATH), mousePosition, renderer, editor);
    buttons.push_back(pathTileButton);

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
    Button *enemigoImg = new DoNothingButton(++nextId, horda, textureLoader
            .getTexture(ABMONIBLE_EDITOR), mousePosition, renderer);
    hordasButtons.push_back(enemigoImg);

    Button *button = new AgregarEnemigoButton(++nextId, horda, "abmonible",
                                              textureLoader.getTexture(ENEMIGO_SUMA),
                                              mousePosition, renderer, editor);
    hordasButtons.push_back(button);

    Image *cantidad = new ContadorEnemigosInput(horda, "abmonible",
                                                textureLoader.getTexture(FONT),
                                                renderer, editor);
    images.push_back(cantidad);

    Button *deleteAbmonible = new EliminarEnemigoButton(++nextId, horda,
                                                        "abmonible",
                                                        textureLoader.getTexture(
                                                                ENEMIGO_RESTA),
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