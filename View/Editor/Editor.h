#ifndef TOWERDEFENSE_EDITOR_H
#define TOWERDEFENSE_EDITOR_H

#include <string>
#include <vector>
#include "../Model/MapView.h"
#include "../Common/SpriteNamesConfig.h"

class Editor {
private:
    std::vector<std::vector<std::string>> hordas;
    int superficie;
    std::string nombre;
    MapView& map;
public:
    explicit Editor(MapView& map);
    ~Editor();
    void setSuperficie(int superficie);
    void agregarEnemigo(int horda, std::string enemigo);
    void eliminarEnemigo(int horda, std::string enemigo);
    void agregarHorda();
    void eliminarHorda(int horda);
    unsigned int getCantidadHordas();
    unsigned int getCantidadEnemigosEnHorda(std::string enemigo, int horda);
    std::string& getNombre();
    void exportar();
};

#endif //TOWERDEFENSE_EDITOR_H
