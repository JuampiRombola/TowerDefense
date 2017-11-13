#include "GameButtons.h"
#include "SpellButton.h"

#define BUTTONSOFFSET 200

GameButtons::GameButtons(Window &w, MousePosition &mousePosition,
                         Renderer &renderer,
                         TextureLoader &textureLoader,
                         CommandDispatcher &dispatcher) :
        window(w), mousePosition(mousePosition),
        renderer(renderer), textureLoader(textureLoader),
        dispatcher(dispatcher) {}

GameButtons::~GameButtons() {
    for (auto &tower : towers)
        delete tower;
    for (auto &spell : spells)
        delete spell;
}

void GameButtons::addTowerButtons(int key, int &cmd) {
    towers.push_back(new NewTowerButton(window, key, cmd,
                     textureLoader.getTexture(key + BUTTONSOFFSET),
                     mousePosition, renderer, towers.size() + 1));
    spells.push_back(new SpellButton(window, key, cmd,
                                        textureLoader.getTexture(key + BUTTONSOFFSET),
                                        mousePosition, renderer, spells.size() + 1));
    spells.push_back(new SpellButton(window, key, cmd,
                                        textureLoader.getTexture(key + BUTTONSOFFSET),
                                        mousePosition, renderer, spells.size() + 1));
}

bool GameButtons::isAnyClicked() {
    for (auto &tower : towers) {
        if (tower->isClicked())
            return true;
    }
    for (auto &spell : spells) {
        if (spell->isClicked())
            return true;
    }
    return false;
}

void GameButtons::draw() {
    for (Image *tower : towers)
        tower->draw(0);
    for (Image *spell : spells)
        spell->draw(0);
}
