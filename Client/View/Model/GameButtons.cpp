#include "GameButtons.h"
#include "SpellButton.h"
#include "UpRightButton.h"

#define TRANSPARENCY 212
#define BUTTONSOFFSET 200
#define SPELLOFFSET_1 4
#define SPELLOFFSET_2 5

GameButtons::GameButtons(Window &w, MousePosition &mousePosition,
                         Renderer &renderer,
                         TextureLoader &textureLoader, int &cmd) :
        window(w), mousePosition(mousePosition),
        renderer(renderer), textureLoader(textureLoader), cmd(cmd) {
    barUpRight.push_back(new UpRightButton(window, CMD_PING, cmd,
               textureLoader.getTexture(PING_BUTTON),
               textureLoader.getTexture(TRANSPARENCY),
               mousePosition, renderer, barUpRight.size() + 1));
}

GameButtons::~GameButtons() {
    for (auto &tower : towers)
        delete tower;
    for (auto &spell : spells)
        delete spell;
    for (auto &element : barUpRight)
        delete element;
}

void GameButtons::addTowerButtons(int key) {
    towers.push_back(new NewTowerButton(window, key, cmd,
                     textureLoader.getTexture(key + BUTTONSOFFSET),
                     textureLoader.getTexture(TRANSPARENCY),
                     mousePosition, renderer, towers.size() + 1));
    int spellKey = key + SPELLOFFSET_1 + 1*key;
    spells.push_back(
            new SpellButton(window, spellKey, cmd,
                            textureLoader.getTexture(spellKey+BUTTONSOFFSET),
                            textureLoader.getTexture(TRANSPARENCY),
                            mousePosition, renderer, spells.size() + 1));
    spellKey = key + SPELLOFFSET_2 + 1*key;
    spells.push_back(
            new SpellButton(window, spellKey, cmd,
                            textureLoader.getTexture(spellKey+BUTTONSOFFSET),
                            textureLoader.getTexture(TRANSPARENCY),
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
    for (auto &button : barUpRight) {
        if (button->isClicked())
            return true;
    }
    return false;
}

void GameButtons::draw() {
    for (auto &tower : towers)
        tower->draw(0, 0);
    for (auto &spell : spells)
        spell->draw(0, 0);
    for (auto &button : barUpRight)
        button->draw(0, 0);
}
