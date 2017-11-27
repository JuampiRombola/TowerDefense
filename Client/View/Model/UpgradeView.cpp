#include "UpgradeView.h"
#include "ViewConstants.h"
#include "../Common/SpriteNamesConfig.h"
#include "../../../Common/Lock.h"

#define UPGRADE_BG_W 264
#define UPGRADE_BG_H 185

#define START_X_ICON 22
#define START_Y_ICON 95

#define PADLOCK_W 61
#define PADLOCK_H 73

#define UPGRADE_ICON_SIZE 47
#define PADDING_ICON 32

#define FONT_UPGRD "../Resources/font.ttf"
#define FONT_UPGRD_SIZE 10

#define MSG_EXP "Experiencia: "
#define MSG_LVL "Nivel: "
#define MSG_FREQ "Frecuencia(s): "
#define MSG_DAMAGE "Damage: "
#define MSG_RANGO "Rango: "
#define MSG_IMPACTO "Rango impacto: "
#define MSG_IMPACTO2 "Damage I: "
#define MSG_FREEZE "Ralentizado %: "
#define MSG_FREEZE2 "Duracion: "
#define MSG_FLYDAMAGE "Damage aereo: "

#define MSG1_1_X 25
#define MSG1_1_Y 35
#define MSG2_1_X 25
#define MSG2_1_Y 50
#define MSG2_2_X 160
#define MSG2_2_Y 50
#define MSG3_1_X 25
#define MSG3_1_Y 65
#define MSG3_2_X 160
#define MSG3_2_Y 65
#define MSG4_1_X 25
#define MSG4_1_Y 80
#define MSG4_2_X 160
#define MSG4_2_Y 80

#define INDEX_DAMAGE 0
#define INDEX_RANGE 1
#define INDEX_IMPACT 2

UpgradeView::UpgradeView(Renderer &r, TextureLoader &tl, TowerView *t,
                         int &command, MousePosition &mp, bool isMine) :
        renderer(r), tl(tl), tower(t), cmd(command), mousePosition(mp),
        background(PADDING_HUD, PADDING_HUD, UPGRADE_BG_W, UPGRADE_BG_H,
        tl.getTexture(UPGRADE_BACKGROUND), renderer),
        padlock(START_X_ICON + 2*UPGRADE_ICON_SIZE
                + 2*PADDING_ICON, START_Y_ICON, PADLOCK_W,
                PADLOCK_H, tl.getTexture(CANDADO), renderer),
        textColor(SDL_Color{255, 255, 255, 0xFF}), active(isMine) {
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
    t->setDestXY(MSG1_1_X, MSG1_1_Y);
    messages.push_back(t);

    msg = MSG_DAMAGE + std::to_string(tower->getDamage());
    t = new TextView(renderer, font, msg, textColor);
    t->setDestXY(MSG2_1_X, MSG2_1_Y);
    messages.push_back(t);

    msg = MSG_RANGO + std::to_string(tower->getRange());
    t = new TextView(renderer, font, msg, textColor);
    t->setDestXY(MSG2_2_X, MSG2_2_Y);
    messages.push_back(t);

    Uint32 f = tower->getFrequency() / 1000;
    if (f == 0) f = 1;
    msg = MSG_FREQ + std::to_string(f);
    t = new TextView(renderer, font, msg, textColor);
    t->setDestXY(MSG3_1_X, MSG3_1_Y);
    messages.push_back(t);

    int rangeX = MSG3_2_X;
    int rangeY = MSG3_2_Y;
    if (key == ELEMENTAL_EARTH) {
        rangeX = MSG4_1_X;
        rangeY = MSG4_1_Y;
    }

    msg = MSG_LVL + std::to_string(tower->getLevel());
    t = new TextView(renderer, font, msg, textColor);
    t->setDestXY(rangeX, rangeY);
    messages.push_back(t);

    if (key == ELEMENTAL_FIRE) {
        msg = MSG_IMPACTO + std::to_string(tower->getCollateralRange());
        t = new TextView(renderer, font, msg, textColor);
        t->setDestXY(MSG4_1_X, MSG4_1_Y);
        messages.push_back(t);

        msg = MSG_IMPACTO2 + std::to_string(tower->getCollateralDamage());
        t = new TextView(renderer, font, msg, textColor);
        t->setDestXY(MSG4_2_X, MSG4_2_Y);
        messages.push_back(t);
    } else if (key == ELEMENTAL_WATER) {
        msg = MSG_FREEZE + std::to_string(tower->getFreezePercent());
        t = new TextView(renderer, font, msg, textColor);
        t->setDestXY(MSG4_1_X, MSG4_1_Y);
        messages.push_back(t);

        msg = MSG_FREEZE2 + std::to_string(tower->getFreezeDuration());
        t = new TextView(renderer, font, msg, textColor);
        t->setDestXY(MSG4_2_X, MSG4_2_Y);
        messages.push_back(t);
    } else if (key == ELEMENTAL_AIR) {
        msg = MSG_FLYDAMAGE + std::to_string(tower->getFlyDamage());
        t = new TextView(renderer, font, msg, textColor);
        t->setDestXY(MSG4_1_X, MSG4_1_Y);
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

    if (key == ELEMENTAL_FIRE) {
        buttons.push_back(new InstantButton(renderer, tl, IMPACT, mousePosition,
                                            START_X_ICON + 2*UPGRADE_ICON_SIZE
                                            + 2*PADDING_ICON, START_Y_ICON,
                                            UPGRADE_ICON_SIZE,UPGRADE_ICON_SIZE,
                                            cmd));
    } else if (key == ELEMENTAL_WATER) {
        buttons.push_back(new InstantButton(renderer, tl, FREEZE, mousePosition,
                                            START_X_ICON + 2*UPGRADE_ICON_SIZE
                                            + 2*PADDING_ICON, START_Y_ICON,
                                            UPGRADE_ICON_SIZE,UPGRADE_ICON_SIZE,
                                            cmd));
    }
    if (!active) {
        for (auto &button : buttons)
            button->desactivate();
    }
}

void UpgradeView::update() {
    this->addText();
    buttons[INDEX_DAMAGE]->setTotalProgressBar(tower->getUpgradeDamage());
    buttons[INDEX_DAMAGE]->setPartProgressBar(tower->getExp());

    buttons[INDEX_RANGE]->setTotalProgressBar(tower->getUpgradeRange());
    buttons[INDEX_RANGE]->setPartProgressBar(tower->getExp());

    if (key == ELEMENTAL_FIRE) {
        buttons[INDEX_IMPACT]->setTotalProgressBar(tower->getUpgradeImpact());
        buttons[INDEX_IMPACT]->setPartProgressBar(tower->getExp());
    } else if (key == ELEMENTAL_WATER) {
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
