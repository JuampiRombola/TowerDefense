#include "GameButtons.h"
#include "UpRightButton.h"
#include "ViewConstants.h"

#define TOTAL_BUTTONS 13
#define FIRST_BUTTON 13
#define FIRST_SPELL_BUTTON 8
#define BLANK_SPACE 9
#define CANT_TOWERS 4

#define TRANSPARENCY 212
#define BUTTONSOFFSET 200
#define SPELLOFFSET_1 4
#define SPELLOFFSET_2 5

#define INDEX_EXIT 0
#define INDEX_PING 1

GameButtons::GameButtons(Window &w, MousePosition &mousePosition,
                         Renderer &renderer,
                         TextureLoader &textureLoader, int &cmd) :
        window(w), mousePosition(mousePosition),
        renderer(renderer), textureLoader(textureLoader), cmd(cmd),
        decoTowers(textureLoader.getTexture(MARQUESINA), renderer),
        decoSpells(textureLoader.getTexture(MARQUESINA), renderer) {
    barUpRight.push_back(new UpRightButton(window, CMD_EXIT, cmd,
               textureLoader.getTexture(EXIT_BUTTON),
               textureLoader.getTexture(TRANSPARENCY),
               mousePosition, renderer, barUpRight.size() + 1));
    barUpRight.push_back(new UpRightButton(window, CMD_PING, cmd,
               textureLoader.getTexture(PING_BUTTON),
               textureLoader.getTexture(TRANSPARENCY),
               mousePosition, renderer, barUpRight.size() + 1));
    decoTowers.setSourceRect(0, 0, MARQUESINA_W, MARQUESINA_H);
    decoSpells.setSourceRect(0, 0, MARQUESINA_W, MARQUESINA_H);
    decoTowers.setDestRect(0, 0, MARQUESINA_W, MARQUESINA_H);
    decoSpells.setDestRect(0, 0, MARQUESINA_W, MARQUESINA_H);
    this->initFakeButtons();
}

GameButtons::~GameButtons() {
    for (auto &tower : towers)
        delete tower;
    for (auto &spell : spells)
        delete spell;
    for (auto &element : barUpRight)
        delete element;
    for (auto &button : fakeButtons)
        delete button;
}

void GameButtons::addTowerButtons(int key) {
    WaitActionButton *b;
    int y = window.getHeight() - PADDING_HUD - HUD_BUTTON_Y;
    int towerX = static_cast<int>(window.getWidth() - PADDING_HUD -
            (FIRST_BUTTON - towers.size()) * HUD_BUTTON_X);
    b = new WaitActionButton(renderer, textureLoader, key + BUTTONSOFFSET,
                         mousePosition, towerX, y,
                         HUD_ICON_SIZE, HUD_ICON_SIZE, cmd);
    towers.push_back(b);

    int spellX = static_cast<int>(window.getWidth() - PADDING_HUD -
            (FIRST_SPELL_BUTTON - spells.size()) * HUD_BUTTON_X);
    int spellKey = key + SPELLOFFSET_1 + 1*key;

    b = new WaitActionButton(renderer, textureLoader, spellKey+BUTTONSOFFSET,
                             mousePosition, spellX, y,
                             HUD_ICON_SIZE, HUD_ICON_SIZE, cmd);
    spells.push_back(b);

    spellX = static_cast<int>(window.getWidth() - PADDING_HUD -
            (FIRST_SPELL_BUTTON - spells.size()) * HUD_BUTTON_X);
    spellKey = key + SPELLOFFSET_2 + 1*key;
    b = new WaitActionButton(renderer, textureLoader, spellKey+BUTTONSOFFSET,
                             mousePosition, spellX, y,
                             HUD_ICON_SIZE, HUD_ICON_SIZE, cmd);
    spells.push_back(b);
}

bool GameButtons::isAnyClicked() {
    for (auto &tower : towers) {
        if (tower->isClicked() && tower->isFullProgressBar())
            return true;
    }
    for (auto &spell : spells) {
        if (spell->isClicked() && spell->isFullProgressBar())
            return true;
    }
    return (barUpRight[INDEX_PING]->isClicked());
}

void GameButtons::draw() {
    decoTowers.drawEuclidian();
    decoSpells.drawEuclidian();
    for (auto &button : barUpRight)
        button->draw(0, 0);
    for (auto &fake : fakeButtons)
        fake->draw();
    for (auto &tower : towers)
        tower->draw();
    for (auto &spell : spells)
        spell->draw();
}

void GameButtons::initFakeButtons() {
    for (int i=0; i <= TOTAL_BUTTONS; ++i) {
        if (i == BLANK_SPACE) continue;

        int x = window.getWidth() - PADDING_HUD - i*HUD_BUTTON_X;
        int y = window.getHeight() - PADDING_HUD - HUD_BUTTON_Y;

        if (i == 5) { // es la mitad de la barra de spells
            decoSpells.setDestXY(x - MARQUESINA_OFFSET_X,
                                 y - MARQUESINA_H);
        }

        if (i == 12) { // es la mitad de la barra de torres
            decoTowers.setDestXY(x - MARQUESINA_OFFSET_X,
                                 y - MARQUESINA_H);
        }

        fakeButtons.push_back(
                new PadlockButton(renderer, textureLoader,
                                  mousePosition, x, y,
                                  HUD_ICON_SIZE, HUD_ICON_SIZE));
    }
}

bool GameButtons::isAnyFakeClicked() {
    for (auto &fake : fakeButtons) {
        if (fake->isClicked())
            return true;
    }
    return false;
}

bool GameButtons::exitClicked() {
    return (barUpRight[INDEX_EXIT]->isClicked());
}

void GameButtons::setCooldown(int key, Uint32 cd) {
    if (key <= CMD_AIR_TOWER) {
        for (auto &tower : towers) {
            if (tower->getKey() == key) {
                tower->setTotalProgressBar(cd);
                tower->setPartProgressBar(0);
            }
        }
    }
    if (key >= CMD_TERRAFORMING) {
        for (auto &spell : spells) {
            if (spell->getKey() == key) {
                spell->setTotalProgressBar(cd);
                spell->setPartProgressBar(0);
            }
        }
    }
}

void GameButtons::clickButton(SDL_Keycode sym) {
    int index = 0;
    switch (sym) {
        case SDLK_q:
            index = 0;
            break;
        case SDLK_w:
            index = 1;
            break;
        case SDLK_e:
            index = 2;
            break;
        case SDLK_r:
            index = 3;
            break;
        case SDLK_f:
            index = INDEX_PING;
            break;
        case SDLK_1:
            index = 0;
            break;
        case SDLK_2:
            index = 1;
            break;
        case SDLK_3:
            index = 2;
            break;
        case SDLK_4:
            index = 3;
            break;
        case SDLK_5:
            index = 4;
            break;
        case SDLK_6:
            index = 5;
            break;
        case SDLK_7:
            index = 6;
            break;
        case SDLK_8:
            index = 7;
            break;
        default:break;
    }
    if (sym == SDLK_q || sym == SDLK_w || sym == SDLK_e || sym == SDLK_r) {
        if (index < towers.size())
            towers[index]->click();
    } else if (sym == SDLK_f) {
        barUpRight[INDEX_PING]->click();
    } else {
        if (index < spells.size())
            spells[index]->click();
    }
}
