#include "Editor.h"
#include <iostream>

Editor::Editor(MapView &map, TextureLoader &textureLoader,
               Renderer &renderer) : superficie(PRADERA), map(map),
                                     textureLoader(textureLoader), renderer
                                                           (renderer) {
};

Editor::~Editor() {
    for (auto& portal : portales)
        delete portal;
}

void Editor::setSuperficie(const int superficie) {
    this->superficie = superficie;
    map.setEnvTile(superficie);
}

void Editor::agregarEnemigo(int horda, std::string enemigo) {
    this->hordas.at(horda).push_back(enemigo);
}

void Editor::eliminarEnemigo(int horda, std::string enemigo) {
    for (std::vector<std::string>::iterator it = hordas.at(horda).begin();
         it != hordas.at(horda).end(); ++it) {
        if (*it == enemigo)
            this->hordas.at(horda).erase(it);
    }
}

void Editor::agregarHorda() {
    this->hordas.emplace_back();
}

void Editor::eliminarHorda(int horda) {
    std::vector<std::vector<std::string>>::iterator it = hordas.begin();
    for (int i = 0; i < horda; ++i) {
        ++it;
    }
    hordas.erase(it);
}

unsigned int Editor::getCantidadHordas() {
    return this->hordas.size();
}

unsigned int Editor::getCantidadEnemigosEnHorda(std::string enemigo,
                                                int horda) {
    if (horda >= getCantidadHordas())
        return 0;
    unsigned int total = 0;
    // enemigo2 es un nombre horrible. Pero se que va a terminar siendo un
    // map y este ciclo va a desaparecer. Así que whatever.
    for (auto& enemigo2 : hordas.at(horda)) {
        if (enemigo == enemigo2)
            ++total;
    }
    return total;
}

std::string& Editor::getNombre() {
    return this->nombre;
}

void Editor::exportar() {
    std::cout << "Nombre: " << nombre << "\n";
    std::cout << "Superficie: " << superficie << "\n";
    for (unsigned int i = 0; i < hordas.size(); ++i) {
        std::cout << "Horda " << (i + 1) << "\n";
        for (std::string enemigo : hordas.at(i)) {
            std::cout << enemigo << "\n";
        }
    }
}

void Editor::waitForPathTile() {
    using namespace std::placeholders;
    mapFunction = std::bind(&MapView::addPathTile, &map, _1, _2);
}

void Editor::waitForStructureTile() {
    using namespace std::placeholders;
    mapFunction = std::bind(&MapView::addStructureTile, &map, _1, _2);
}

void Editor::waitForSpawnPortalTile() {
    using namespace std::placeholders;
    mapFunction = std::bind(&Editor::addSpawnTile, this, _1, _2);
}

void Editor::waitForExitPortalTile() {
    using namespace std::placeholders;
    mapFunction = std::bind(&Editor::addExitTile, this, _1, _2);
}

void Editor::applyTileFunction(int x, int y) {
    if (mapFunction && map.isValidTile(x, y))
        mapFunction(x, y);
}

void Editor::unbindWaitingFunction() {
    mapFunction = std::function<void(int, int)>();
}

void Editor::addSpawnTile(int x, int y) {
    PortalView * portal = new PortalEntradaView(textureLoader, renderer);
    portal->setXY(x, y);
    portales.push_back(portal);
    unbindWaitingFunction();
}

void Editor::addExitTile(int x, int y) {
    PortalView * portal = new PortalSalidaView(textureLoader, renderer);
    portal->setXY(x, y);
    portales.push_back(portal);
    unbindWaitingFunction();
}

void Editor::draw() {
    Uint32 ticks = SDL_GetTicks();
    map.draw(ticks);
    for (auto& portal : portales)
        portal->draw(ticks);
}