#include "MousePosition.h"

MousePosition::MousePosition(int &x, int &y) :
        x(x), y(y), active(false), marked(false) {}

MousePosition::~MousePosition() = default;

int MousePosition::getPosX() {
    return x;
}

int MousePosition::getPosY() {
    return y;
}

bool MousePosition::isActive() {
    return active;
}

void MousePosition::activate() {
    active = true;
}

void MousePosition::deactivate() {
    active = false;
}

bool MousePosition::isMarked() {
    return marked;
}

void MousePosition::activateMark() {
    marked = true;
}

void MousePosition::desactivateMark() {
    marked = false;
}
