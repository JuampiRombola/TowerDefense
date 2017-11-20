#include <iostream>
#include "Horda.h"

Horda::Horda(int id) : id(id), tiempo(0) {
    cantidadEnemigos[ABMONIBLE_KEY] = 0;
    cantidadEnemigos[ESPECTRO_KEY] = 0;
    cantidadEnemigos[DEMONIO_VERDE_KEY] = 0;
    cantidadEnemigos[HALCON_SANGRIENTO_KEY] = 0;
    cantidadEnemigos[NO_MUERTO_KEY] = 0;
    cantidadEnemigos[HOMBRE_CABRA_KEY] = 0;
}

int Horda::getId() {
    return id;
}

void Horda::agregarEnemigo(std::string enemigo) {
    cantidadEnemigos[enemigo] += 1;
}

void Horda::eliminarEnemigo(std::string enemigo) {
    if (cantidadEnemigos[enemigo] == 0)
        return;
    cantidadEnemigos[enemigo] -= 1;
}

std::string Horda::exportar() {
    std::stringstream msg;
    msg << "tiempo: " << tiempo << "\n";
    for (std::pair<std::string, int> enemigo : cantidadEnemigos) {
        msg << "   " << enemigo.first << ": " << enemigo.second << "\n";
    }
    return msg.str();
}

unsigned int Horda::getCantidadEnemigosDeTipo(std::string enemigo) {
    return cantidadEnemigos[enemigo];
}

unsigned int Horda::getCantidadEnemigos() {
    unsigned int cantidadTotal = 0;
    for (std::pair<std::string, int> enemigo : cantidadEnemigos) {
        cantidadTotal += enemigo.second;
    }
    return cantidadTotal;
}

void Horda::aumentarTiempo() {
    ++tiempo;
}

void Horda::disminuirTiempo() {
    if (tiempo == 0)
        return;
    --tiempo;
}

int Horda::getTiempo() {
    return tiempo;
}