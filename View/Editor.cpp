#include "Editor.h"

Editor::Editor(Renderer &renderer, Buttons &buttons) :
        renderer(renderer), buttons(buttons) {}

Editor::~Editor() = default;

void Editor::draw() {
    buttons.draw();
}
