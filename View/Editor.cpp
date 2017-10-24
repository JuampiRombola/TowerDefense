#include "Editor.h"
#include <iostream>

Editor::Editor() = default;

Editor::~Editor() = default;

void Editor::setSuperficie(const std::string &superficie) {
    this->superficie = superficie;
}

void Editor::agregarEnemigo(int horda, std::string enemigo) {
    this->hordas.at(horda).push_back(enemigo);
}

void Editor::eliminarEnemigo(int horda, std::string enemigo) {
    for (std::vector<std::string>::iterator it = hordas.at(horda).begin();
         it != hordas.at(horda).end(); ++it) {
        if (*it == enemigo)
            this->hordas.at(horda).erase(it);
    }
}

void Editor::agregarHorda() {
    this->hordas.emplace_back();
}

void Editor::eliminarHorda(int horda) {
    std::vector<std::vector<std::string>>::iterator it = hordas.begin();
    for (int i = 0; i < horda; ++i) {
        ++it;
    }
    hordas.erase(it);
}

unsigned int Editor::getCantidadHordas() {
    return this->hordas.size();
}

void Editor::exportar() {
    std::cout << "Superficie: " << superficie << "\n";
    for (unsigned int i = 0; i < hordas.size(); ++i) {
        std::cout << "Horda " << (i + 1) << "\n";
        for (std::string enemigo : hordas.at(i)) {
            std::cout << enemigo << "\n";
        }
    }
}