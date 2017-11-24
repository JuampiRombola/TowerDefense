#ifndef TOWERDEFENSE_UPGRADEVIEW_H
#define TOWERDEFENSE_UPGRADEVIEW_H


#include "../Common/Renderer.h"
#include "TowerView.h"
#include "../Common/Image.h"
#include "../Common/MousePosition.h"
#include "InstantButton.h"
#include "TextView.h"
#include <vector>
#include <SDL_ttf.h>

class UpgradeView {
private:
    Renderer &renderer;
    TextureLoader &tl;
    TowerView *tower;
    int &cmd;
    MousePosition &mousePosition;
    int key;
    Image background;
    Image padlock;
    SDL_Color textColor;
    TTF_Font *font;
    std::vector<InstantButton*> buttons;
    std::vector<TextView *> messages;
    bool active;

public:
    UpgradeView(Renderer &r, TextureLoader &tl, TowerView *t,
                int &command, MousePosition &mp, bool isMine);
    ~UpgradeView();
    void draw();
    void addText();
    void addButtons();
    void update();
    bool isClicked();
    void onClick();
    int getId();
    int getElement();
};


#endif //TOWERDEFENSE_UPGRADEVIEW_H
