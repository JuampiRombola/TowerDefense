#include "ShotView.h"

#define SHOT_FIRE_W 129
#define SHOT_FIRE_H 129
#define SHOT_FIRE_START_X 0
#define SHOT_FIRE_START_Y 0
#define SHOT_FIRE_COLUMNS 16
#define SHOT_FIRE_ROWS 1
#define SHOT_FIRE_OFFSET_X 46
#define SHOT_FIRE_OFFSET_Y 200

#define EXPLOSION_FIRE_W 129
#define EXPLOSION_FIRE_H 89
#define EXPLOSION_FIRE_START_X 0
#define EXPLOSION_FIRE_START_Y 169
#define EXPLOSION_FIRE_COLUMNS 5
#define EXPLOSION_FIRE_ROWS 1
#define EXPLOSION_FIRE_OFFSET_X 0
#define EXPLOSION_FIRE_OFFSET_Y 0
#define EXPLOSION_FIRE_TPS 100

#define SHOT_OFFSET_X 50
#define SHOT_OFFSET_Y 70

ShotView::ShotView(int key, TextureLoader &textures, Renderer &renderer) :
        renderer(renderer),
        spriteShot(textures.getTexture(key), renderer,
                      SHOT_FIRE_W, SHOT_FIRE_H,
                      SHOT_FIRE_START_X, SHOT_FIRE_START_Y,
                      SHOT_FIRE_COLUMNS, SHOT_FIRE_ROWS),
        spriteExplosion(textures.getTexture(key), renderer,
                    EXPLOSION_FIRE_W, EXPLOSION_FIRE_H,
                    EXPLOSION_FIRE_START_X, EXPLOSION_FIRE_START_Y,
                    EXPLOSION_FIRE_COLUMNS, EXPLOSION_FIRE_ROWS),
        traveledDistanceX(0), traveledDistanceY(0) {
    currentState = DISABLE;
    spriteShot.setDestRect(x, y, SHOT_FIRE_W * 2, SHOT_FIRE_H * 2);
    spriteShot.setOffsetXY(SHOT_FIRE_OFFSET_X, SHOT_FIRE_OFFSET_Y);

    spriteExplosion.setDestRect(x, y, EXPLOSION_FIRE_W * 2,
                                EXPLOSION_FIRE_H * 2);
    spriteExplosion.setOffsetXY(EXPLOSION_FIRE_OFFSET_X,
                                EXPLOSION_FIRE_OFFSET_Y);
    spriteExplosion.setTimePerSprite(EXPLOSION_FIRE_TPS);
}

void ShotView::draw(Uint32 ticks) {
    if (currentState == DISABLE) return;
    if (currentState == EXPLOSION) {
        if (spriteExplosion.getCurrentSprite() != EXPLOSION_FIRE_COLUMNS) {
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
    spriteShot.setOffsetXY(SHOT_FIRE_OFFSET_X, SHOT_FIRE_OFFSET_Y);
    spriteExplosion.setOffsetXY(EXPLOSION_FIRE_OFFSET_X,
                                EXPLOSION_FIRE_OFFSET_Y);
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
    totalDistanceX = dstX - cx + SHOT_FIRE_OFFSET_X - SHOT_OFFSET_X;
    totalDistanceY = dstY - cy + SHOT_FIRE_OFFSET_Y - SHOT_OFFSET_Y;
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
    int offsetX = spriteShot.getOffsetX() + EXPLOSION_FIRE_OFFSET_X;
    int offsetY = spriteShot.getOffsetY() + EXPLOSION_FIRE_OFFSET_Y;
    spriteExplosion.setOffsetXY(offsetX, offsetY);
}
