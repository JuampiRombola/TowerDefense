#ifndef TOWERDEFENSE_EDITOR_H
#define TOWERDEFENSE_EDITOR_H

#include <string>
#include <vector>
#include "../Model/MapView.h"
#include "../Common/SpriteNamesConfig.h"

class Editor {
private:
    std::string superficie;
    std::vector<std::vector<std::string>> hordas;
    std::string nombre;
    MapView& map;
public:
    Editor(MapView& map);
    ~Editor();
    void setSuperficie(const int superficie);
    void agregarEnemigo(int horda, std::string enemigo);
    void eliminarEnemigo(int horda, std::string enemigo);
    void agregarHorda();
    void eliminarHorda(int horda);
    unsigned int getCantidadHordas();
    std::string& getNombre();
    void exportar();
};

#endif //TOWERDEFENSE_EDITOR_H
