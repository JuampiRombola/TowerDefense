//
// Created by juampi on 10/23/17.
//

#include "View.h"

View::View(){}
View::~View() {}

void View::setXY(int x, int y) {
    this->x = x;
    this->y = y;
}


int View::getX() {
    return this->x;
}

int View::getY() {
    return this->y;
}

std::string View::onClick() {
    return "";
}
