//
// Created by juampi on 10/23/17.
//

#include "View.h"

View::View(int key, TextureLoader &textures, Renderer &renderer) :
        sprite(textures.getTexture(key), renderer) {}

void View::setXY(int x, int y) {
    this->x = x;
    this->y = y;
    sprite.setDestXY(x, y);
}

View::~View() {
}
