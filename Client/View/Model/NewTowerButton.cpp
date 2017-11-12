#include "NewTowerButton.h"
#include "../../include/NetCommands/NewTowerCommand.h"

NewTowerButton::NewTowerButton(std::string element, SDL_Texture *texture,
                               MousePosition &mousePosition, Renderer &renderer,
                               CommandDispatcher &dispatcher)
        : element(element), dispatcher(dispatcher),
          Button(0, 0, TOWER_BUTTON_WIDTH, TOWER_BUTTON_HEIGHT, texture,
                 mousePosition, renderer) {}

void NewTowerButton::draw(int number) {
    button.x = number * TOWER_BUTTON_WIDTH;
    Button::draw(number);
}

void NewTowerButton::click() {
//Acá tengo que bindear la función throwCommand a algún lado para que se
// ejecute en el ciclo del main de la vista
}

void NewTowerButton::throwCommand(int tileX, int tileY) {
    auto* command = new NewTowerCommand(element, tileX, tileY);
    dispatcher.QueueCommand(command);
}