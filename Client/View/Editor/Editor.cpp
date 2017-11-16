#include "Editor.h"
#include <iostream>
#include <bits/ios_base.h>
#include <ios>

Editor::Editor(MapView &map, TextureLoader &textureLoader, Renderer &renderer,
               std::string name, Window &window) : superficie(PRADERA),
                                                   map(map),
                                                   textureLoader(textureLoader),
                                                   renderer(renderer),
                                                   nombre(name),
                                                   window(window) {
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
    if (!validate())
        return;
    std::stringstream fileContent;
    fileContent << "nombre: " << nombre << "\n";
    fileContent << "superficie: " << superficie << "\n";
    fileContent << map.exportar();
    fileContent << "portales: \n";
    for (auto &portal : portales) {
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
    window.showErrorMessage("", "¡El mapa se exportó con éxito!");
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
    for (auto it = portales.begin(); it != portales.end();) {
        if ((*it)->getY() >= (map.getHeight() - 1))
            it = portales.erase(it);
        else
            ++it;
    }
    map.setHeight(map.getHeight() - 1);
}

void Editor::aumentarAnchoMapa() {
    map.setWidth(map.getWidth() + 1);
}

void Editor::disminuirAnchoMapa() {
    for (auto it = portales.begin(); it != portales.end();) {
        if ((*it)->getX() >= (map.getWidth() - 1))
            it = portales.erase(it);
        else
            ++it;
    }
    map.setWidth(map.getWidth() - 1);
}

void Editor::draw() {
    Uint32 ticks = SDL_GetTicks();
    map.draw(ticks);
    for (auto &portal : portales)
        portal->draw(ticks);
}

bool Editor::validate() {
    if (hordas.empty()) {
        window.showErrorMessage("ERROR", "El mapa no posee hordas.");
        return false;
    }
    int hordaNro = 1;
    for (auto &horda : hordas) {
        if (horda.getCantidadEnemigos() == 0) {
            window.showErrorMessage("ERROR",
                                    "La horda " + std::to_string(hordaNro) +
                                    " no posee enemigos");
            return false;
        }
        ++hordaNro;
    }
    if (map.getWidth() == 0) {
        window.showErrorMessage("ERROR", "El ancho del mapa no puede ser cero");
        return false;
    }
    if (map.getHeight() == 0) {
        window.showErrorMessage("ERROR", "El alto del mapa no puede ser cero");
        return false;
    }
    if (portales.empty()) {
        window.showErrorMessage("ERROR", "El mapa no posee portales.");
        return false;
    }
    std::set<std::pair<int, int>> pathSet = map.getPathsAsSet();
    if (pathSet.empty()) {
        window.showErrorMessage("ERROR", "El mapa no posee caminos.");
        return false;
    }
    std::set<std::pair<int, int>> structureTileSet = map.getStructureTilesAsSet();
    if (structureTileSet.empty()) {
        window.showErrorMessage("ERROR", "El mapa no posee tierra firme.");
        return false;
    }
    std::set<std::pair<int, int>> portalesEntrada;
    std::set<std::pair<int, int>> portalesSalida;
    for (auto &portal : portales) {
        if (pathSet.count(
                std::pair<int, int>(portal->getX(), portal->getY())) == 0) {
            window.showErrorMessage("ERROR", "El portal que se encuentra en " +
                                             std::to_string(portal->getX()) +
                                             ", " +
                                             std::to_string(portal->getY()) +
                                             " debe estar sobre un camino.");
            return false;
        }
        if (portal->getType() == "entrada")
            portalesEntrada.emplace(portal->getX(), portal->getY());
        else
            portalesSalida.emplace(portal->getX(), portal->getY());
    }
    


    return true;
}