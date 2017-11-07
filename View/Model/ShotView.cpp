#include "ShotView.h"

ShotView::ShotView(int key, TextureLoader &textures, Renderer &renderer) :
        cfg(textures.getConfig(key)),
        renderer(renderer),
        spriteShot(textures.getTexture(key), renderer,
                   cfg["SHOT_W"].as<int>(),
                   cfg["SHOT_H"].as<int>(),
                   cfg["SHOT_START_X"].as<int>(),
                   cfg["SHOT_START_Y"].as<int>(),
                   cfg["SHOT_COLUMNS"].as<int>(),
                   cfg["SHOT_ROWS"].as<int>()),
        spriteExplosion(textures.getTexture(key), renderer,
                        cfg["EXPLOSION_W"].as<int>(),
                        cfg["EXPLOSION_H"].as<int>(),
                        cfg["EXPLOSION_START_X"].as<int>(),
                        cfg["EXPLOSION_START_Y"].as<int>(),
                        cfg["EXPLOSION_COLUMNS"].as<int>(),
                        cfg["EXPLOSION_ROWS"].as<int>()),
        traveledDistanceX(0), traveledDistanceY(0) {
    currentState = DISABLE;
    spriteShot.setDestRect(x, y,
                           cfg["SHOT_DST_W"].as<int>(),
                           cfg["SHOT_DST_H"].as<int>());
    spriteShot.setOffsetXY(cfg["SHOT_OFFSET_X"].as<int>(),
                           cfg["SHOT_OFFSET_Y"].as<int>());

    spriteExplosion.setDestRect(x, y,
                                cfg["EXPLOSION_DST_W"].as<int>(),
                                cfg["EXPLOSION_DST_H"].as<int>());
    spriteExplosion.setOffsetXY(cfg["EXPLOSION_OFFSET_X"].as<int>(),
                                cfg["EXPLOSION_OFFSET_Y"].as<int>());
    spriteExplosion.setTimePerSprite(cfg["EXPLOSION_TPS"].as<uint>());
}

void ShotView::draw(Uint32 ticks) {
    if (currentState == DISABLE) return;
    if (currentState == EXPLOSION) {
        if (spriteExplosion.getCurrentSprite() !=
                cfg["EXPLOSION_COLUMNS"].as<int>()) {
            spriteExplosion.nextAndDraw(ticks);
        } else {
            currentState = DISABLE;
            spriteExplosion.reset();
        }

    }
    if (currentState == SHOOT) {
        this->setDistanceToMove(ticks);
        spriteShot.nextAndDraw(ticks);
    }
}

void ShotView::setXY(int x, int y) {
    View::setXY(x, y);
    spriteShot.setDestXY(x, y);
    spriteExplosion.setDestXY(x, y);
    spriteShot.setOffsetXY(cfg["SHOT_OFFSET_X"].as<int>(),
                           cfg["SHOT_OFFSET_Y"].as<int>());
    spriteExplosion.setOffsetXY(cfg["EXPLOSION_OFFSET_X"].as<int>(),
                                cfg["EXPLOSION_OFFSET_Y"].as<int>());
}

void ShotView::shoot(int fromX, int fromY, int toX, int toY, Uint32 t) {
    currentState = SHOOT;
    traveledDistanceX = 0;
    traveledDistanceY = 0;
    this->setXY(fromX, fromY);
    initTime = SDL_GetTicks();
    int cx = renderer.cartesianToIsometricX(fromX, fromY);
    int cy = renderer.cartesianToIsometricY(fromX, fromY);
    int dstX = renderer.cartesianToIsometricX(toX, toY);
    int dstY = renderer.cartesianToIsometricY(toX, toY);
    totalDistanceX = dstX - cx +
            cfg["SHOT_OFFSET_X"].as<int>() - cfg["SHOT_FLIGHT_X"].as<int>();
    totalDistanceY = dstY - cy +
            cfg["SHOT_OFFSET_Y"].as<int>() - cfg["SHOT_FLIGHT_Y"].as<int>();
    requiredTime = t;
}

void ShotView::setDistanceToMove(Uint32 ticks) {
    if (((totalDistanceX != 0) || (totalDistanceY != 0))
        && (traveledDistanceX == totalDistanceX)
        && (traveledDistanceY == totalDistanceY)) {
        this->enableExplosion();
        return;
    }
    int elapsedTime = ticks - initTime;
    int distanceX = (totalDistanceX * elapsedTime / requiredTime);
    int distanceY = (totalDistanceY * elapsedTime / requiredTime);
    if (abs(distanceX) > abs(totalDistanceX))
        distanceX = totalDistanceX;
    if (abs(distanceY) > abs(totalDistanceY))
        distanceY = totalDistanceY;
    int offsetX = spriteShot.getOffsetX() - distanceX + traveledDistanceX;
    int offsetY = spriteShot.getOffsetY() - distanceY + traveledDistanceY;
    traveledDistanceX = distanceX;
    traveledDistanceY = distanceY;
    spriteShot.setOffsetXY(offsetX, offsetY);
}

void ShotView::enableExplosion() {
    currentState = EXPLOSION;
    int offsetX = spriteShot.getOffsetX() +
            cfg["EXPLOSION_OFFSET_X"].as<int>();
    int offsetY = spriteShot.getOffsetY() +
            cfg["EXPLOSION_OFFSET_Y"].as<int>();
    spriteExplosion.setOffsetXY(offsetX, offsetY);
}
