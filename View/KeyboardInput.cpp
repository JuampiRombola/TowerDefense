#include "KeyboardInput.h"

KeyboardInput::KeyboardInput(std::string &text) : text(text), activeId(0) {};

KeyboardInput::~KeyboardInput() = default;

void KeyboardInput::setInput(std::string &input) {
    this->text = input;
}

void KeyboardInput::addCharacter(char newChar) {
    this->text += newChar;
}