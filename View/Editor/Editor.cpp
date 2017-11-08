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

void Editor::agregarEnemigo(int hordaId, std::string enemigo) {
    for (auto& horda : hordas) {
        if (hordaId == horda.getId())
            horda.agregarEnemigo(enemigo);
    }
}

void Editor::eliminarEnemigo(int hordaId, std::string enemigo) {
    for (auto& horda : hordas) {
        if (hordaId == horda.getId())
            horda.eliminarEnemigo(enemigo);
    }
}

void Editor::agregarHorda(int id) {
    this->hordas.emplace_back(id);
}

void Editor::eliminarHorda(int hordaId) {
    auto it = hordas.begin();
    for (auto& horda : hordas) {
        ++it;
        if (horda.getId() == hordaId)
            break;
    }
    hordas.erase(it);
}

unsigned int Editor::getCantidadHordas() {
    return static_cast<unsigned int>(this->hordas.size());
}

unsigned int Editor::getCantidadEnemigosEnHorda(std::string enemigo,
                                                int hordaId) {
    for (auto& horda : hordas) {
        if (hordaId == horda.getId())
            return horda.getCantidadEnemigosDeTipo(enemigo);
    }
    return 0;
}

std::string& Editor::getNombre() {
    return this->nombre;
}

void Editor::exportar() {
    std::cout << "Nombre: " << nombre << "\n";
    std::cout << "Superficie: " << superficie << "\n";
    unsigned int hordaNro = 0;
    for (auto& horda : hordas) {
        std::cout << "Horda " << hordaNro << "\n";
        std::cout << horda.exportar();
        ++hordaNro;
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