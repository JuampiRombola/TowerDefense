#include "FireTowerView.h"
#include "../Common/SpriteNamesConfig.h"

#define FTOWER_W 63
#define FTOWER_H 104
#define FTOWER_START_X 0
#define FTOWER_START_Y 0
#define FTOWEROFFSET_X (-32)
#define FTOWEROFFSET_Y 92

#define FIRE_W 23
#define FIRE_H 45
#define FIRE_START_X 0
#define FIRE_START_Y 109
#define FIREOFFSET_X (-64)
#define FIREOFFSET_Y 134

#define FTOWER_COLUMNS 30
#define FTOWER_ROWS 1

FireTowerView::FireTowerView(TextureLoader &textures, Renderer &renderer) :
        spriteTower(textures.getTexture(FIRE_TOWER), renderer,
                    FTOWER_W, FTOWER_H,
                    FTOWER_START_X, FTOWER_START_Y,
                    FTOWER_COLUMNS, FTOWER_ROWS),
        spriteFire(textures.getTexture(FIRE_TOWER), renderer,
                   FIRE_W, FIRE_H,
                   FIRE_START_X, FIRE_START_Y,
                   FTOWER_COLUMNS, FTOWER_ROWS) {

    spriteTower.setDestRect(x, y, FTOWER_W + FTOWER_W / 2,
                            FTOWER_H + FTOWER_H / 2);
    spriteTower.setOffsetXY(FTOWEROFFSET_X, FTOWEROFFSET_Y);

    spriteFire.setDestRect(x, y, FIRE_W + FIRE_W / 2,
                           FIRE_H + FIRE_H / 2);
    spriteFire.setOffsetXY(FIREOFFSET_X, FIREOFFSET_Y);
}

FireTowerView::~FireTowerView() {}

void FireTowerView::draw(Uint32 ticks) {
    spriteTower.nextAndDraw(ticks);
    spriteFire.nextAndDraw(ticks);
}

void FireTowerView::setXY(int x, int y) {
    View::setXY(x, y);
    spriteTower.setDestXY(x, y);
    spriteFire.setDestXY(x, y);
}