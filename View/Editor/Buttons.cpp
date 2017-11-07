#include "Buttons.h"
#include "AgregarCaminoButton.h"
#include "AgregarTierraFirmeButton.h"
#include "AgregarPortalEntradaButton.h"
#include "AgregarPortalSalidaButton.h"

Buttons::Buttons(MousePosition &mousePosition, Renderer &renderer,
                 Editor &editor, TextureLoader &textureLoader, KeyboardInput
                 &keyboardInput) : mousePosition(
        mousePosition), renderer(renderer), editor(editor), textureLoader(
        textureLoader), keyboardInput(keyboardInput) {}


Buttons::~Buttons() {
    for (Image *image : images)
        delete image;
}

void Buttons::draw() {
    int i = 0;
    for (Image *image : images) {
        image->draw(i);
        i++;
    }
}

void Buttons::addInitialButtons() {
    using namespace std::placeholders; //Esto lo uso en el botón de crear horda
    Image *praderaButton = new SuperficieButton(PRADERA, textureLoader.getTexture(
            PRADERA), mousePosition, renderer, editor);
    images.push_back(praderaButton);

    Image *lavaButton = new SuperficieButton(VOLCAN,
                                             textureLoader.getTexture(VOLCAN),
                                             mousePosition, renderer, editor);
    images.push_back(lavaButton);

    Image *desiertoButton = new SuperficieButton(DESIERTO, textureLoader.getTexture(
            DESIERTO), mousePosition, renderer, editor);
    images.push_back(desiertoButton);

    Image *glaciarButton = new SuperficieButton(GELIDO, textureLoader.getTexture(
            GELIDO), mousePosition, renderer, editor);
    images.push_back(glaciarButton);

    Image *pathTileButton = new AgregarCaminoButton(
            textureLoader.getTexture(PATH_TILE_EDITOR), mousePosition, renderer,
            editor);
    images.push_back(pathTileButton);

    Image *structureTileButton = new AgregarTierraFirmeButton(
            textureLoader.getTexture(STRUCTURE_TILE_EDITOR), mousePosition,
            renderer, editor);
    images.push_back(structureTileButton);

    Image *spawnTileButton = new AgregarPortalEntradaButton(
            textureLoader.getTexture(PORTAL_ENTRADA_EDITOR), mousePosition,
            renderer, editor);
    images.push_back(spawnTileButton);

    Image *exitTileButton = new AgregarPortalSalidaButton(
            textureLoader.getTexture(PORTAL_SALIDA_EDITOR), mousePosition,
            renderer, editor);
    images.push_back(exitTileButton);

    Image *button = new NuevaHordaButton(
            textureLoader.getTexture(AGREGAR_HORDA_BTN), mousePosition,
            renderer, editor, std::bind(&Buttons::addEnemigosButton, this, _1));
    images.push_back(button);
}

void Buttons::addEnemigosButton(int horda) {
    Image *enemigoImg = new EnemigoImage(horda, textureLoader.getTexture(
            ABMONIBLE_EDITOR), renderer);
    images.push_back(enemigoImg);

    Image *deleteAbmonible = new EliminarEnemigoButton(horda, ABMONIBLE_KEY,
                                                       textureLoader.getTexture(
                                                               ENEMIGO_RESTA),
                                                       mousePosition, renderer,
                                                       editor);
    images.push_back(deleteAbmonible);

    Image *agregarAbmonible = new AgregarEnemigoButton(horda, ABMONIBLE_KEY,
                                              textureLoader
            .getTexture(
            ENEMIGO_SUMA), mousePosition, renderer, editor);
    images.push_back(agregarAbmonible);

    /*Image *cantidad = new ContadorEnemigosInput(horda, ABMONIBLE_KEY,
                                                textureLoader.getTexture(FONT),
                                                renderer, editor);
    images.push_back(cantidad);

    Image *eliminarHordaButton = new EliminarHordaButton(horda, textureLoader.getTexture(
            ELIMINAR_HORDA_BTN), mousePosition, renderer, editor);
    images.push_back(eliminarHordaButton);*/
}

bool Buttons::isAnyClicked() {
    for (auto& image : images) {
        if (image->isClicked())
            return true;
    }
    return false;
}