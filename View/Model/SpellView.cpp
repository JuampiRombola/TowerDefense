#include "SpellView.h"

#define SPELL_W 119
#define SPELL_H 160
#define SPELL_START_X 1
#define SPELL_START_Y 0
#define SPELL_COLUMNS 20
#define SPELL_ROWS 1
#define SPELL_OFFSET_X (-14)
#define SPELL_OFFSET_Y 94
#define SPELL_TPS 100
#define SPELL_TANSPARENCY 150

SpellView::SpellView(int key, TextureLoader &textures, Renderer &renderer) :
        sprite(textures.getTexture(key), renderer,
               SPELL_W, SPELL_H,
               SPELL_START_X, SPELL_START_Y,
               SPELL_COLUMNS, SPELL_ROWS) {
    sprite.setAlphaMod(SPELL_TANSPARENCY);
    isEnable = false;
    sprite.setDestRect(x, y, SPELL_W, SPELL_H);
    sprite.setOffsetXY(SPELL_OFFSET_X, SPELL_OFFSET_Y);
    sprite.setTimePerSprite(SPELL_TPS);
}

void SpellView::draw(Uint32 ticks) {
    if (!isEnable) return;
    if ((ticks - initTime) >= requiredTime) {
        isEnable = false;
        sprite.reset();
    }
    sprite.draw();
    sprite.nextAndDraw(ticks);
}

void SpellView::setXY(int x, int y) {
    View::setXY(x, y);
    sprite.setDestXY(x, y);
}

void SpellView::cast(int x, int y, Uint32 t) {
    isEnable = true;
    this->setXY(x, y);
    requiredTime = t;
    initTime = SDL_GetTicks();
}

bool SpellView::hasFinished() {
    return !isEnable;
}


