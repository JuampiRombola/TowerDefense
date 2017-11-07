#include "Horda.h"

Horda::Horda(int id) : id(id) {
    cantidadEnemigos[ABMONIBLE_KEY] = 0;
}

int Horda::getId() {
    return id;
}

void Horda::agregarEnemigo(std::string enemigo) {
    cantidadEnemigos[enemigo] += 1;
}

void Horda::eliminarEnemigo(std::string enemigo) {
    cantidadEnemigos[enemigo] += 1;
    if (cantidadEnemigos[enemigo] < 0)
        cantidadEnemigos[enemigo] = 0;
}

std::string Horda::exportar() {
    std::stringstream msg;
    for (std::pair<std::string, int> enemigo : cantidadEnemigos) {
        msg << enemigo.first << ": " << enemigo.second << "\n";
    }
    return msg.str();
}

unsigned int Horda::getCantidadEnemigosDeTipo(std::string enemigo) {
    return cantidadEnemigos[enemigo];
}