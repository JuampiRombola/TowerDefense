#ifndef TOWERDEFENSE_HORDA_H
#define TOWERDEFENSE_HORDA_H

#include <string>
#include <map>
#include <sstream>
#include "EditorConstants.h"

class Horda {
private:
    int id;
    int tiempoEntreHordas;
    int tiempoEntreEnemigos;
    std::map<std::string, unsigned int> cantidadEnemigos;
public:
    explicit Horda(int id);
    int getId();
    void agregarEnemigo(std::string enemigo);
    void eliminarEnemigo(std::string enemigo);
    std::string exportar();
    unsigned int getCantidadEnemigosDeTipo(std::string enemigo);
    unsigned int getCantidadEnemigos();
    void aumentarTiempo();
    void disminuirTiempo();
    int getTiempo();
    void aumentarTiempoEntreEnemigos();
    void disminuirTiempoEntreEnemigos();
    int getTiempoEntreEnemigos();
};


#endif //TOWERDEFENSE_HORDA_H
