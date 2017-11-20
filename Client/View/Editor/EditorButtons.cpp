#include <iostream>
#include "EditorButtons.h"
#include "AgregarCaminoButton.h"
#include "AgregarTierraFirmeButton.h"
#include "AgregarPortalEntradaButton.h"
#include "AgregarPortalSalidaButton.h"
#include "DisminuirPaddingButton.h"
#include "AumentarPaddingButton.h"
#include "ContadorHordasInput.h"

EditorButtons::EditorButtons(MousePosition &mousePosition, Renderer &renderer,
                             Editor &editor, TextureLoader &textureLoader)
        : mousePosition(mousePosition), padding(0), renderer(renderer),
          editor(editor), textureLoader(textureLoader), hordaToDelete(-1) {}


EditorButtons::~EditorButtons() {
    for (Image *image : images)
        delete image;
}

void EditorButtons::draw() {
    int i = 0;
    for (Image *image : images) {
        image->draw(i, padding);
        i++;
    }
    if (hordaToDelete >= 0) {
        for (auto it = images.begin(); it != images.end();) {
            if ((*it)->belongsToHorda(hordaToDelete)) {
                delete *it;
                it = images.erase(it);
            } else {
                it++;
            }
        }
        hordaToDelete = -1;
    }
}

void EditorButtons::addInitialButtons() {
    using namespace std::placeholders; //Esto lo uso en el botón de crear horda
    Image *praderaButton = new SuperficieButton(PRADERA,
                                                textureLoader.getTexture(
                                                        PRADERA), mousePosition,
                                                renderer, editor);
    images.push_back(praderaButton);

    Image *lavaButton = new SuperficieButton(VOLCAN,
                                             textureLoader.getTexture(VOLCAN),
                                             mousePosition, renderer, editor);
    images.push_back(lavaButton);

    Image *desiertoButton = new SuperficieButton(DESIERTO,
                                                 textureLoader.getTexture(
                                                         DESIERTO),
                                                 mousePosition, renderer,
                                                 editor);
    images.push_back(desiertoButton);

    Image *glaciarButton = new SuperficieButton(GELIDO,
                                                textureLoader.getTexture(
                                                        GELIDO), mousePosition,
                                                renderer, editor);
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
            renderer, editor,
            std::bind(&EditorButtons::addEnemigosButton, this, _1));
    images.push_back(button);

    Image *altoIcon = new Image(ALTO_BUTTON_X, ALTO_BUTTON_Y, ALTO_BUTTON_WIDTH,
                                ALTO_BUTTON_HEIGHT,
                                textureLoader.getTexture(ALTO_MAPA), renderer);
    images.push_back(altoIcon);

    Image *aumentarAlto = new AumentarAltoMapaButton(
            textureLoader.getTexture(ENEMIGO_SUMA), mousePosition, renderer,
            editor);
    images.push_back(aumentarAlto);

    Image *disminuirAlto = new DisminuirAltoMapaButton(
            textureLoader.getTexture(ENEMIGO_RESTA), mousePosition, renderer,
            editor);
    images.push_back(disminuirAlto);

    Image *anchoIcon = new Image(ANCHO_BUTTON_X, ANCHO_BUTTON_Y,
                                 ANCHO_BUTTON_WIDTH, ANCHO_BUTTON_HEIGHT,
                                 textureLoader.getTexture(ANCHO_MAPA),
                                 renderer);
    images.push_back(anchoIcon);


    Image *aumentarAncho = new AumentarAnchoMapaButton(
            textureLoader.getTexture(ENEMIGO_SUMA), mousePosition, renderer,
            editor);
    images.push_back(aumentarAncho);

    Image *disminuirAncho = new DisminuirAnchoMapaButton(
            textureLoader.getTexture(ENEMIGO_RESTA), mousePosition, renderer,
            editor);
    images.push_back(disminuirAncho);

    Image *saveButton = new GuardarButton(textureLoader.getTexture(SAVE_BUTTON),
                                          mousePosition, renderer, editor);
    images.push_back(saveButton);

    Image *scrollUp = new AumentarPaddingButton(padding,
                                                textureLoader.getTexture(
                                                        ARROW_UP_EDITOR),
                                                mousePosition, renderer);
    images.push_back(scrollUp);

    Image *scrollDown = new DisminuirPaddingButton(padding,
                                                   textureLoader.getTexture(
                                                           ARROW_DOWN_EDITOR),
                                                   mousePosition, renderer);
    images.push_back(scrollDown);
}

void EditorButtons::addEnemigosButton(int horda) {
    using namespace std::placeholders;
    Image *contadorHorda = new ContadorHordasInput(horda,
                                                  textureLoader.getTexture(
                                                          FONT), renderer);
    images.push_back(contadorHorda);
    addEnemigoButton(horda, ABMONIBLE_KEY, ABMONIBLE_EDITOR);
    addEnemigoButton(horda, ESPECTRO_KEY, ESPECTRO_EDITOR);
    addEnemigoButton(horda, DEMONIO_VERDE_KEY, DEMONIO_VERDE_EDITOR);
    addEnemigoButton(horda, HALCON_SANGRIENTO_KEY, HALCON_SANGRIENTO_EDITOR);
    addEnemigoButton(horda, NO_MUERTO_KEY, NO_MUERTO_EDITOR);
    addEnemigoButton(horda, HOMBRE_CABRA_KEY, HOMBRE_CABRA_EDITOR);
    addTiempoEntreHorda(horda);
    Image *eliminarHordaButton = new EliminarHordaButton(horda,
                                                         textureLoader.getTexture(
                                                                 ELIMINAR_HORDA_BTN),
                                                         mousePosition,
                                                         renderer, editor,
                                                         std::bind(
                                                                 &EditorButtons::deleteButtonsOfHorda,
                                                                 this, _1));
    images.push_back(eliminarHordaButton);
}

void EditorButtons::addEnemigoButton(int horda, std::string enemigoKey,
                                     int texture) {
    Image *enemigoImg = new EnemigoImage(horda,
                                         textureLoader.getTexture(texture),
                                         renderer);
    images.push_back(enemigoImg);

    Image *deleteAbmonible = new EliminarEnemigoButton(horda, enemigoKey,
                                                       textureLoader.getTexture(
                                                               ENEMIGO_RESTA),
                                                       mousePosition, renderer,
                                                       editor);
    images.push_back(deleteAbmonible);

    Image *agregarAbmonible = new AgregarEnemigoButton(horda, enemigoKey,
                                                       textureLoader.getTexture(
                                                               ENEMIGO_SUMA),
                                                       mousePosition, renderer,
                                                       editor);
    images.push_back(agregarAbmonible);

    Image *cantidad = new ContadorEnemigosInput(horda, enemigoKey,
                                                textureLoader.getTexture(FONT),
                                                renderer, editor);
    images.push_back(cantidad);
}

void EditorButtons::addTiempoEntreHorda(int horda) {
    Image *clockImg = new EnemigoImage(horda,
                                       textureLoader.getTexture(CLOCK_EDITOR),
                                       renderer);
    images.push_back(clockImg);

    Image *aumentarTiempo = new AumentarTiempoButton(horda,
                                                     textureLoader.getTexture(
                                                             ENEMIGO_SUMA),
                                                     mousePosition, renderer,
                                                     editor);
    images.push_back(aumentarTiempo);

    Image *disminuirTiempo = new DisminuirTiempoButton(horda,
                                                       textureLoader.getTexture(
                                                               ENEMIGO_RESTA),
                                                       mousePosition, renderer,
                                                       editor);
    images.push_back(disminuirTiempo);

    Image *contadorTiempo = new ContadorTiempoInput(horda,
                                                    textureLoader.getTexture(
                                                            FONT), renderer,
                                                    editor);
    images.push_back(contadorTiempo);
}

void EditorButtons::deleteButtonsOfHorda(int horda) {
    /*for (auto it = images.begin(); it != images.end();) {
        if ((*it)->belongsToHorda(horda)) {
            delete *it;
            it = images.erase(it);
        } else {
            it++;
        }
    }*/
    hordaToDelete = horda;
}

bool EditorButtons::isAnyClicked() {
    for (auto &image : images) {
        if (image->isClicked())
            return true;
    }
    return false;
}