#include "Editor.h"
#include <iostream>
#include <bits/ios_base.h>
#include <ios>

Editor::Editor(MapView &map, TextureLoader &textureLoader, Renderer &renderer,
               std::string name) : superficie(PRADERA), map(map),
                                   textureLoader(textureLoader),
                                   renderer(renderer), nombre(name) {
};

Editor::~Editor() {
    for (auto &portal : portales)
        delete portal;
}

void Editor::setSuperficie(const int superficie) {
    this->superficie = superficie;
    map.setEnvTile(superficie);
}

void Editor::agregarEnemigo(int hordaId, std::string enemigo) {
    for (auto &horda : hordas) {
        if (hordaId == horda.getId())
            horda.agregarEnemigo(enemigo);
    }
}

void Editor::eliminarEnemigo(int hordaId, std::string enemigo) {
    for (auto &horda : hordas) {
        if (hordaId == horda.getId())
            horda.eliminarEnemigo(enemigo);
    }
}

void Editor::agregarHorda(int id) {
    this->hordas.emplace_back(id);
}

void Editor::eliminarHorda(int hordaId) {
    auto it = hordas.begin();
    for (auto &horda : hordas) {
        if (horda.getId() == hordaId)
            break;
        ++it;
    }
    hordas.erase(it);
}

unsigned int
Editor::getCantidadEnemigosEnHorda(std::string enemigo, int hordaId) {
    for (auto &horda : hordas) {
        if (hordaId == horda.getId())
            return horda.getCantidadEnemigosDeTipo(enemigo);
    }
    return 0;
}

void Editor::exportar() {
    std::stringstream fileContent;
    fileContent << "nombre: " << nombre << "\n";
    fileContent << "superficie: " << superficie << "\n";
    fileContent << map.exportar();
    fileContent << "portales: \n";
    for (auto& portal : portales) {
        fileContent << " - tipo: " << portal->getType() << "\n";
        fileContent << "   x: " << portal->getX() << "\n";
        fileContent << "   y: " << portal->getY() << "\n";
    }
    fileContent << "hordas:\n";
    unsigned int hordaNro = 0;
    for (auto &horda : hordas) {
        fileContent << " - " << horda.exportar();
        ++hordaNro;
    }
    File file(nombre + ".yaml");
    file.write(fileContent.str());
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
    PortalView *portal = new PortalEntradaView(textureLoader, renderer);
    portal->setXY(x, y);
    portales.push_back(portal);
    unbindWaitingFunction();
}

void Editor::addExitTile(int x, int y) {
    PortalView *portal = new PortalSalidaView(textureLoader, renderer);
    portal->setXY(x, y);
    portales.push_back(portal);
    unbindWaitingFunction();
}

void Editor::aumentarTiempoHorda(int hordaId) {
    for (auto &horda : hordas) {
        if (hordaId == horda.getId())
            horda.aumentarTiempo();
    }
}

void Editor::disminuirTiempoHorda(int hordaId) {
    for (auto &horda : hordas) {
        if (hordaId == horda.getId())
            horda.disminuirTiempo();
    }
}

int Editor::getTiempoHorda(int hordaId) {
    for (auto &horda : hordas) {
        if (hordaId == horda.getId())
            return horda.getTiempo();
    }
}

void Editor::aumentarAltoMapa() {
    map.setHeight(map.getHeight() + 1);
}

void Editor::disminuirAltoMapa() {
    map.setHeight(map.getHeight() - 1);
}

void Editor::aumentarAnchoMapa() {
    map.setWidth(map.getWidth() + 1);
}

void Editor::disminuirAnchoMapa() {
    map.setWidth(map.getWidth() - 1);
}

void Editor::draw() {
    Uint32 ticks = SDL_GetTicks();
    map.draw(ticks);
    for (auto &portal : portales)
        portal->draw(ticks);
}