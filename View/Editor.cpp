#include "Editor.h"
#include <iostream>

Editor::Editor() = default;

Editor::~Editor() = default;

void Editor::setSuperficie(const std::string &superficie) {
    std::cout << "La nueva superficie es " << superficie << "\n";
    this->superficie = superficie;
}