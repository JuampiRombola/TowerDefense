#include "SpellView.h"

SpellView::SpellView(int key, TextureLoader &textures, Renderer &renderer) :
        cfg(textures.getConfig(key)),
        sprite(textures.getTexture(key), renderer,
               cfg["SPELL_W"].as<int>(),
               cfg["SPELL_H"].as<int>(),
               cfg["SPELL_START_X"].as<int>(),
               cfg["SPELL_START_Y"].as<int>(),
               cfg["SPELL_COLUMNS"].as<int>(),
               cfg["SPELL_ROWS"].as<int>()) {
    sprite.setAlphaMod(cfg["SPELL_TANSPARENCY"].as<uint>());
    isEnable = false;
    sprite.setDestRect(x, y,
                       cfg["SPELL_DST_W"].as<int>(),
                       cfg["SPELL_DST_H"].as<int>());
    sprite.setOffsetXY(cfg["SPELL_OFFSET_X"].as<int>(),
                       cfg["SPELL_OFFSET_Y"].as<int>());
    sprite.setTimePerSprite(cfg["SPELL_TPS"].as<uint>());
    sprite.setDisplayMode(cfg["SPELL_DISPLAY_MODE"].as<int>());
}

void SpellView::draw(Uint32 ticks) {
    if (!isEnable) return;
    if ((ticks - initTime) >= requiredTime) {
        isEnable = false;
        sprite.reset();
        return;
    }
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


