#include "UpgradeView.h"
#include "ViewConstants.h"
#include "../Common/SpriteNamesConfig.h"
#include "../../../Common/Lock.h"

#define UPGRADE_BG_W 264
#define UPGRADE_BG_H 170

#define START_X_ICON 22
#define START_Y_ICON 80

#define PADLOCK_W 64
#define PADLOCK_H 76

#define UPGRADE_ICON_SIZE 50
#define PADDING_ICON 30

#define FONT_UPGRD "../Resources/font.ttf"
#define FONT_UPGRD_SIZE 10

#define MSG_EXP "Experiencia: "
#define MSG_DAMAGE "Damage: "
#define MSG_RANGO "Rango: "
#define MSG_IMPACTO "Alcance de impacto: "
#define MSG_FREEZE "Ralentizado: "

#define MSG_EXP_X 25
#define MSG_EXP_Y 35
#define MSG_DAMAGE_X 25
#define MSG_DAMAGE_Y 50
#define MSG_RANGE_X 114
#define MSG_RANGE_Y 50
#define MSG_IMPACT_X 25
#define MSG_IMPACT_Y 65

#define INDEX_DAMAGE 0
#define INDEX_RANGE 1
#define INDEX_IMPACT 2

UpgradeView::UpgradeView(Renderer &r, TextureLoader &tl,
                         TowerView *t, int &command, MousePosition &mp) :
        renderer(r), tl(tl), tower(t), cmd(command), mousePosition(mp),
        background(PADDING_HUD, PADDING_HUD, UPGRADE_BG_W, UPGRADE_BG_H,
        tl.getTexture(UPGRADE_BACKGROUND), renderer),
        padlock(START_X_ICON + 2*UPGRADE_ICON_SIZE
                + 2*PADDING_ICON, START_Y_ICON, PADLOCK_W,
                PADLOCK_H, tl.getTexture(CANDADO), renderer),
        textColor(SDL_Color{255, 255, 255, 0xFF}) {
    font = TTF_OpenFont(FONT_UPGRD, FONT_UPGRD_SIZE);
    key = tower->getKey();
    this->addButtons();
    this->update();
}

UpgradeView::~UpgradeView() {
    TTF_CloseFont(font);
    for (auto &element : messages)
        delete element;
    for (auto &element : buttons)
        delete element;
}

void UpgradeView::draw() {
    background.draw(0, 0);
    padlock.draw(0, 0);
    for (auto &button : buttons)
        button->draw();
    for (auto &msg : messages)
        msg->draw();
}

void UpgradeView::addText() {
    for (auto &element : messages)
        delete element;

    std::string msg;
    TextView *t;

    msg = MSG_EXP + std::to_string(tower->getExp());
    t = new TextView(renderer, font, msg, textColor);
    t->setDestXY(MSG_EXP_X, MSG_EXP_Y);
    messages.push_back(t);

    msg = MSG_DAMAGE + std::to_string(tower->getDamage());
    t = new TextView(renderer, font, msg, textColor);
    t->setDestXY(MSG_DAMAGE_X, MSG_DAMAGE_Y);
    messages.push_back(t);

    int rangeX = MSG_IMPACT_X;
    int rangeY = MSG_IMPACT_Y;
    if (key == TORRE_FUEGO | key == TORRE_AGUA) {
        rangeX = MSG_RANGE_X;
        rangeY = MSG_RANGE_Y;
    }

    msg = MSG_RANGO + std::to_string(tower->getRange());
    t = new TextView(renderer, font, msg, textColor);
    t->setDestXY(rangeX, rangeY);
    messages.push_back(t);

    if (key == TORRE_FUEGO) {
        msg = MSG_IMPACTO + std::to_string(tower->getCollateralRange());
        t = new TextView(renderer, font, msg, textColor);
        t->setDestXY(MSG_IMPACT_X, MSG_IMPACT_Y);
        messages.push_back(t);
    } else if (key == TORRE_AGUA) {
        msg = MSG_FREEZE + std::to_string(tower->getFreezePercent());
        t = new TextView(renderer, font, msg, textColor);
        t->setDestXY(MSG_IMPACT_X, MSG_IMPACT_Y);
        messages.push_back(t);
    }
}

void UpgradeView::addButtons() {
    buttons.push_back(new InstantButton(renderer, tl, DAMAGE, mousePosition,
                                        START_X_ICON, START_Y_ICON,
                                        UPGRADE_ICON_SIZE,UPGRADE_ICON_SIZE,
                                        cmd));
    buttons.push_back(new InstantButton(renderer, tl, RANGE, mousePosition,
                                        START_X_ICON + UPGRADE_ICON_SIZE
                                        + PADDING_ICON, START_Y_ICON,
                                        UPGRADE_ICON_SIZE,UPGRADE_ICON_SIZE,
                                        cmd));

    if (key == TORRE_FUEGO) {
        buttons.push_back(new InstantButton(renderer, tl, IMPACT, mousePosition,
                                            START_X_ICON + 2*UPGRADE_ICON_SIZE
                                            + 2*PADDING_ICON, START_Y_ICON,
                                            UPGRADE_ICON_SIZE,UPGRADE_ICON_SIZE,
                                            cmd));
    } else if (key == TORRE_AGUA) {
        buttons.push_back(new InstantButton(renderer, tl, FREEZE, mousePosition,
                                            START_X_ICON + 2*UPGRADE_ICON_SIZE
                                            + 2*PADDING_ICON, START_Y_ICON,
                                            UPGRADE_ICON_SIZE,UPGRADE_ICON_SIZE,
                                            cmd));
    }
}

void UpgradeView::update() {
    this->addText();
    buttons[INDEX_DAMAGE]->setTotalProgressBar(tower->getUpgradeDamage());
    buttons[INDEX_DAMAGE]->setPartProgressBar(tower->getExp());

    buttons[INDEX_RANGE]->setTotalProgressBar(tower->getUpgradeRange());
    buttons[INDEX_RANGE]->setPartProgressBar(tower->getExp());

    if (key == TORRE_FUEGO) {
        buttons[INDEX_IMPACT]->setTotalProgressBar(tower->getUpgradeImpact());
        buttons[INDEX_IMPACT]->setPartProgressBar(tower->getExp());
    } else if (key == TORRE_AGUA) {
        buttons[INDEX_IMPACT]->setTotalProgressBar(tower->getUpgradeFreeze());
        buttons[INDEX_IMPACT]->setPartProgressBar(tower->getExp());
    }
}

bool UpgradeView::isClicked() {
    int x = mousePosition.getPosX();
    int y = mousePosition.getPosY();
   return  !(x < PADDING_HUD || x > (PADDING_HUD + UPGRADE_BG_W) ||
      y < PADDING_HUD || y > (PADDING_HUD + UPGRADE_BG_H)) &&
    mousePosition.isActive();
}

void UpgradeView::onClick() {
    for (auto &button : buttons) {
        if (button->isClicked()) {
            button->click();
            mousePosition.deactivate();
        }
    }
}

int UpgradeView::getId() {
    return tower->getId();
}

int UpgradeView::getElement() {
    return tower->getKey();
}
