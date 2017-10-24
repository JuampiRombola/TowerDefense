#ifndef TOWERDEFENSE_EDITOR_H
#define TOWERDEFENSE_EDITOR_H

#include <string>
#include <vector>

class Editor {
private:
    std::string superficie;
    std::vector<std::vector<std::string>> hordas;
public:
    Editor();
    ~Editor();
    void setSuperficie(const std::string &superficie);
    void agregarEnemigo(int horda, std::string enemigo);
    void eliminarEnemigo(int horda, std::string enemigo);
    void agregarHorda();
    void eliminarHorda(int horda);
    unsigned int getCantidadHordas();
    void exportar();
};


#endif //TOWERDEFENSE_EDITOR_H
