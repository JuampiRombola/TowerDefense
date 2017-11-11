#include "TowerView.h"
#include "../Common/SpriteNamesConfig.h"

TowerView::TowerView(int id, int key, TextureLoader &textures, 
                     Renderer &renderer) :
        id(id), key(key), exp(0),
        cfg(textures.getConfig(key)),
        spriteTower(textures.getTexture(key), renderer,
                    cfg["TOWER_W"].as<int>(),
                    cfg["TOWER_H"].as<int>(),
                    cfg["TOWER_START_X"].as<int>(),
                    cfg["TOWER_START_Y"].as<int>(),
                    cfg["TOWER_COLUMNS"].as<int>(),
                    cfg["TOWER_ROWS"].as<int>()),
        spriteFire(textures.getTexture(key), renderer,
                   cfg["POWER_W"].as<int>(),
                   cfg["POWER_H"].as<int>(),
                   cfg["POWER_START_X"].as<int>(),
                   cfg["POWER_START_Y"].as<int>(),
                   cfg["POWER_COLUMNS"].as<int>(),
                   cfg["POWER_ROWS"].as<int>()) {

    spriteTower.setDestRect(x, y,
                            cfg["TOWER_DST_W"].as<int>(),
                            cfg["TOWER_DST_H"].as<int>());
    spriteTower.setOffsetXY(cfg["TOWER_OFFSET_X"].as<int>(),
                            cfg["TOWER_OFFSET_Y"].as<int>());

    spriteFire.setDestRect(x, y,
                           cfg["POWER_DST_W"].as<int>(),
                           cfg["POWER_DST_H"].as<int>());
    spriteFire.setOffsetXY(cfg["POWER_OFFSET_X"].as<int>(),
                           cfg["POWER_OFFSET_Y"].as<int>());
}

void TowerView::draw(Uint32 ticks) {
    spriteTower.nextAndDraw(ticks);
    spriteFire.nextAndDraw(ticks);
}

void TowerView::setXY(int x, int y) {
    View::setXY(x, y);
    spriteTower.setDestXY(x, y);
    spriteFire.setDestXY(x, y);
}

std::string TowerView::onClick() {
    return std::move(std::to_string(key) + " " + std::to_string(exp));
}

int TowerView::getId() {
    return id;
}
