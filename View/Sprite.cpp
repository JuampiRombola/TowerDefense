//
// Created by juampi on 10/19/17.
//

#include "Sprite.h"

Sprite::Sprite(SDL_Texture *texture, Renderer &renderer) :
        texture(texture), renderer(renderer), offsetX(0), offsetY(0) {}

Sprite::~Sprite() {}

void Sprite::draw() {
    renderer.copy(texture, &srcRect, &dstRect, offsetX, offsetY);
}

void Sprite::setSourceXY(int x, int y) {
    srcRect.x = x;
    srcRect.y = y;
}

void Sprite::setDestXY(int x, int y) {
    dstRect.x = x;
    dstRect.y = y;
}

void Sprite::setSourceRect(int x, int y, int w, int h) {
    srcRect.x = x;
    srcRect.y = y;
    srcRect.w = w;
    srcRect.h = h;
}

void Sprite::setDestRect(int x, int y, int w, int h) {
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = w;
    dstRect.h = h;
}

void Sprite::setOffsetXY(int x, int y) {
    offsetX = x;
    offsetY = y;
}
