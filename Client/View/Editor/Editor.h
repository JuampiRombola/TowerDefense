#ifndef TOWERDEFENSE_EDITOR_H
#define TOWERDEFENSE_EDITOR_H

#include <string>
#include <vector>
#include <functional>
#include "../Model/MapView.h"
#include "../Common/SpriteNamesConfig.h"
#include "../Model/PortalView.h"
#include "../Model/PortalEntradaView.h"
#include "../Model/PortalSalidaView.h"
#include "Horda.h"
#include <list>
#include "File.h"

class Editor {
private:
    TextureLoader &textureLoader;
    Renderer &renderer;
    std::vector<Horda> hordas;
    int superficie;
    std::string nombre;
    MapView& map;
    Window& window;
    std::list<PortalView*> portales;
    std::function<void(int, int)> mapFunction;
    void validate();
    std::string exportarMapa();
    bool exitActive;
public:
    explicit Editor(MapView &map, TextureLoader &textureLoader, Renderer &renderer,
                        std::string name, Window &window);
    ~Editor();
    void setSuperficie(int superficie);
    void agregarEnemigo(int horda, std::string enemigo);
    void eliminarEnemigo(int horda, std::string enemigo);
    void agregarHorda(int id);
    void eliminarHorda(int horda);
    unsigned int getCantidadEnemigosEnHorda(std::string enemigo, int horda);
    void exportar();
    void waitForPathTile();
    void waitForStructureTile();
    void waitForSpawnPortalTile();
    void waitForExitPortalTile();
    void waitForDeleteTerrainTile();
    void applyTileFunction(int x, int y);
    void unbindWaitingFunction();
    void addPathTile(int x, int y);
    void addStructureTile(int x, int y);
    void addSpawnTile(int x, int y);
    void addExitTile(int x, int y);
    void deleteTerrainTile(int x, int y);
    void aumentarTiempoHorda(int hordaId);
    void disminuirTiempoHorda(int horda);
    int getTiempoHorda(int horda);
    void aumentarTiempoEnemigo(int hordaId);
    void disminuirTiempoEnemigo(int horda);
    int getTiempoEnemigo(int horda);
    void aumentarAnchoMapa();
    void disminuirAnchoMapa();
    void aumentarAltoMapa();
    void disminuirAltoMapa();
    void draw();
    void activateExit();
    void desactivateExit();
    bool isExitActive();
};

#endif //TOWERDEFENSE_EDITOR_H
