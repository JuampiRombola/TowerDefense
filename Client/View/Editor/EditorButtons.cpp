#include <iostream>
#include "EditorButtons.h"
#include "AgregarCaminoButton.h"
#include "AgregarTierraFirmeButton.h"
#include "AgregarPortalEntradaButton.h"
#include "AgregarPortalSalidaButton.h"
#include "DisminuirPaddingButton.h"
#include "AumentarPaddingButton.h"
#include "ContadorHordasInput.h"
#include "AumentarTiempoEnemigosButton.h"
#include "DisminuirTiempoEnemigosButton.h"
#include "ContadorTiempoEnemigosInput.h"
#include "EliminarTerrenoButton.h"
#include "SalidaButton.h"

EditorButtons::EditorButtons(MousePosition &mousePosition,
                             Renderer &renderer,
                             Editor &editor,
                             TextureLoader &textureLoader) :
        mousePosition(mousePosition),
        padding(0), renderer(renderer),
        editor(editor),
        textureLoader(textureLoader),
        hordaToDelete(-1) {
    this->addBackground();
}


EditorButtons::~EditorButtons() {
    for (Image *image : images)
        delete image;
    for (auto sprite : backgrounds)
        delete sprite;
}

void EditorButtons::draw() {
    for (auto sprite : backgrounds)
        sprite->drawEuclidian();

    this->limitPadding();

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
    Image *praderaButton = new SuperficieButton(PRADERA, textureLoader.getTexture(PRADERA),
                                                mousePosition, renderer, editor);
    images.push_back(praderaButton);

    Image *lavaButton = new SuperficieButton(VOLCAN, textureLoader.getTexture(VOLCAN),
                                             mousePosition, renderer, editor);
    images.push_back(lavaButton);

    Image *desiertoButton = new SuperficieButton(DESIERTO, textureLoader.getTexture(DESIERTO),
                                                 mousePosition, renderer, editor);
    images.push_back(desiertoButton);

    Image *glaciarButton = new SuperficieButton(GELIDO, textureLoader.getTexture(GELIDO),
                                                mousePosition, renderer, editor);
    images.push_back(glaciarButton);

    Image *pathTileButton = new AgregarCaminoButton(textureLoader.getTexture(PATH_TILE_EDITOR),
                                                    mousePosition, renderer, editor);
    images.push_back(pathTileButton);

    Image *structureTileButton = new AgregarTierraFirmeButton(
            textureLoader.getTexture(STRUCTURE_TILE_EDITOR), mousePosition, renderer, editor);
    images.push_back(structureTileButton);

    Image *spawnTileButton = new AgregarPortalEntradaButton(
            textureLoader.getTexture(PORTAL_ENTRADA_EDITOR), mousePosition, renderer, editor);
    images.push_back(spawnTileButton);

    Image *exitTileButton = new AgregarPortalSalidaButton(
            textureLoader.getTexture(PORTAL_SALIDA_EDITOR), mousePosition, renderer, editor);
    images.push_back(exitTileButton);

    Image *deleteStructureButton = new EliminarTerrenoButton(
            textureLoader.getTexture(GOMA), mousePosition, renderer, editor);
    images.push_back(deleteStructureButton);

    Image *aumentarAlto = new AumentarAltoMapaButton(textureLoader.getTexture(AGRANDAR_ALTO),
                                                     mousePosition, renderer, editor);
    images.push_back(aumentarAlto);

    Image *disminuirAlto = new DisminuirAltoMapaButton(textureLoader.getTexture(ACHICAR_ALTO),
                                                       mousePosition, renderer, editor);
    images.push_back(disminuirAlto);


    Image *aumentarAncho = new AumentarAnchoMapaButton(textureLoader.getTexture(AGRANDAR_ANCHO),
                                                       mousePosition, renderer, editor);
    images.push_back(aumentarAncho);

    Image *disminuirAncho = new DisminuirAnchoMapaButton(textureLoader.getTexture(ACHICAR_ANCHO),
                                                         mousePosition, renderer, editor);
    images.push_back(disminuirAncho);

    Image *saveButton = new GuardarButton(textureLoader.getTexture(GUARDAR), mousePosition,
                                          renderer, editor);
    images.push_back(saveButton);

    Image *exitButton = new SalidaButton(textureLoader.getTexture(SALIDA_EDITOR), mousePosition,
                                          renderer, editor);
    images.push_back(exitButton);

    Image *button = new NuevaHordaButton(padding, textureLoader.getTexture(NUEVA_HORDA), mousePosition,
                                 renderer, editor,
                                 std::bind(&EditorButtons::addEnemigosButton, this, _1));
    images.push_back(button);

    Image *scrollUp = new AumentarPaddingButton(padding, textureLoader.getTexture(SCROLL_UP),
                                                mousePosition, renderer);
    images.push_back(scrollUp);

    Image *scrollDown = new DisminuirPaddingButton(padding,
                                                   textureLoader.getTexture(SCROLL_DOWN),
                                                   mousePosition, renderer);
    images.push_back(scrollDown);
}

void EditorButtons::addEnemigosButton(int horda) {
    using namespace std::placeholders;
    Image *contadorHorda = new ContadorHordasInput(horda, textureLoader.getTexture(FONT), renderer);
    images.push_back(contadorHorda);
    addEnemigoButton(horda, ABMONIBLE_KEY, ABMONIBLE_EDITOR);
    addEnemigoButton(horda, ESPECTRO_KEY, ESPECTRO_EDITOR);
    addEnemigoButton(horda, DEMONIO_VERDE_KEY, DEMONIO_VERDE_EDITOR);
    addEnemigoButton(horda, HALCON_SANGRIENTO_KEY, HALCON_SANGRIENTO_EDITOR);
    addEnemigoButton(horda, NO_MUERTO_KEY, NO_MUERTO_EDITOR);
    addEnemigoButton(horda, HOMBRE_CABRA_KEY, HOMBRE_CABRA_EDITOR);
    addTiempoEntreEnemigos(horda);
    addTiempoEntreHorda(horda);
    Image *eliminarHordaButton = new EliminarHordaButton(horda, textureLoader.getTexture(
            ELIMINAR_HORDA_BTN), mousePosition, renderer, editor, std::bind(
            &EditorButtons::deleteButtonsOfHorda, this, _1));
    images.push_back(eliminarHordaButton);
}

void EditorButtons::addEnemigoButton(int horda, std::string enemigoKey, int texture) {
    Image *enemigoImg = new EnemigoImage(horda, textureLoader.getTexture(texture), renderer);
    images.push_back(enemigoImg);

    Image *deleteAbmonible = new EliminarEnemigoButton(horda, enemigoKey,
                                                       textureLoader.getTexture(ENEMIGO_RESTA),
                                                       mousePosition, renderer, editor);
    images.push_back(deleteAbmonible);

    Image *agregarAbmonible = new AgregarEnemigoButton(horda, enemigoKey,
                                                       textureLoader.getTexture(ENEMIGO_SUMA),
                                                       mousePosition, renderer, editor);
    images.push_back(agregarAbmonible);

    Image *cantidad = new ContadorEnemigosInput(horda, enemigoKey, textureLoader.getTexture(FONT),
                                                renderer, editor);
    images.push_back(cantidad);
}

void EditorButtons::addTiempoEntreHorda(int horda) {
    Image *clockImg = new EnemigoImage(horda, textureLoader.getTexture(CLOCK_EDITOR), renderer);
    images.push_back(clockImg);

    Image *aumentarTiempo = new AumentarTiempoHordaButton(horda,
                                                          textureLoader.getTexture(ENEMIGO_SUMA),
                                                          mousePosition, renderer, editor);
    images.push_back(aumentarTiempo);

    Image *disminuirTiempo = new DisminuirTiempoHordaButton(horda,
                                                            textureLoader.getTexture(ENEMIGO_RESTA),
                                                            mousePosition, renderer, editor);
    images.push_back(disminuirTiempo);

    Image *contadorTiempo = new ContadorTiempoHordaInput(horda, textureLoader.getTexture(FONT),
                                                         renderer, editor);
    images.push_back(contadorTiempo);
}

void EditorButtons::addTiempoEntreEnemigos(int horda) {
    Image *clockImg = new EnemigoImage(horda, textureLoader.getTexture(CLOCK_ENEMIES_EDITOR),
                                       renderer);
    images.push_back(clockImg);

    Image *aumentarTiempo = new AumentarTiempoEnemigosButton(horda,
                                                             textureLoader.getTexture(ENEMIGO_SUMA),
                                                             mousePosition, renderer, editor);
    images.push_back(aumentarTiempo);

    Image *disminuirTiempo = new DisminuirTiempoEnemigosButton(horda, textureLoader.getTexture(
            ENEMIGO_RESTA), mousePosition, renderer, editor);
    images.push_back(disminuirTiempo);

    Image *contadorTiempo = new ContadorTiempoEnemigosInput(horda, textureLoader.getTexture(FONT),
                                                            renderer, editor);
    images.push_back(contadorTiempo);

}

void EditorButtons::deleteButtonsOfHorda(int horda) {
    hordaToDelete = horda;
}

bool EditorButtons::isAnyClicked() {
    for (auto &image : images) {
        if (image->isClicked())
            return true;
    }
    return false;
}

void EditorButtons::addBackground() {
    Sprite *s = new Sprite(textureLoader.getTexture(BG_ESCENARIO), renderer);
    s->setSourceRect(0, 0, BG_BUTTONS_W, BG_BUTTONS_H);
    s->setDestRect(0, 0, BG_BUTTONS_DST_W, BG_BUTTONS_DST_H);
    s->setAlphaMod(220);
    backgrounds.push_back(s);

    s = new Sprite(textureLoader.getTexture(BG_RECURSOS), renderer);
    s->setSourceRect(0, 0, BG_BUTTONS_W, BG_BUTTONS_H);
    s->setDestRect(BG_BUTTONS_DST_W + BG_PADDING, 0,
                   BG_BUTTONS_DST_W, BG_BUTTONS_DST_H);
    s->setAlphaMod(220);
    backgrounds.push_back(s);

    s = new Sprite(textureLoader.getTexture(BG_HERRAMIENTAS), renderer);
    s->setSourceRect(0, 0, BG_BUTTONS_W, BG_BUTTONS_H);
    s->setDestRect(2*BG_BUTTONS_DST_W + 2*BG_PADDING, 0,
                   BG_BUTTONS_DST_W, BG_BUTTONS_DST_H);
    s->setAlphaMod(220);
    backgrounds.push_back(s);

    s = new Sprite(textureLoader.getTexture(BG_SCROLL), renderer);
    s->setSourceRect(0, 0, BG_SCROLL_W, BG_SCROLL_H);
    s->setDestRect(0, renderer.getWindowHeight() - BG_SCROLL_DST_H,
                   BG_SCROLL_DST_W, BG_SCROLL_DST_H);
    s->setAlphaMod(220);
    backgrounds.push_back(s);

    s = new Sprite(textureLoader.getTexture(SCROLL_BAR), renderer);
    s->setSourceRect(0, 0, SCROLL_BAR_W, SCROLL_BAR_H);
    s->setDestRect(0, renderer.getWindowHeight() - SCROLL_BAR_Y
                      - SCROLL_BAR_DST_H, SCROLL_BAR_DST_W, SCROLL_BAR_DST_H);
    s->setAlphaMod(220);
    backgrounds.push_back(s);
}

void EditorButtons::limitPadding() {
    int cantHordas = static_cast<int>((images.size() -
                     TOTAL_MAIN_BUTTONS)/BUTTONS_PER_HORDA);
    if (cantHordas == 1)
        padding = 0;
    else if (cantHordas < padding + 1)
        padding = static_cast<unsigned int>(cantHordas - 1);
}
