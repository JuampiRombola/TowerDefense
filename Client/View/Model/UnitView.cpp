#include "UnitView.h"

#define PIXELS 40

UnitView::UnitView(int id, int key, TextureLoader &textures, 
                   Renderer &renderer) :
        id(id), key(key), health(10),
        cfg(textures.getConfig(key)),
        spriteWalking(textures.getTexture(key), renderer,
                      cfg["WALKING_W"].as<int>(),
                      cfg["WALKING_H"].as<int>(),
                      cfg["WALKING_START_X"].as<int>(),
                      cfg["WALKING_START_Y"].as<int>(),
                      cfg["WALKING_COLUMNS"].as<int>(),
                      cfg["WALKING_ROWS"].as<int>()),
        spriteDying(textures.getTexture(key), renderer,
                    cfg["DYING_W"].as<int>(),
                    cfg["DYING_H"].as<int>(),
                    cfg["DYING_START_X"].as<int>(),
                    cfg["DYING_START_Y"].as<int>(),
                    cfg["DYING_COLUMNS"].as<int>(),
                    cfg["DYING_ROWS"].as<int>()),
        accumulatedDisplacement(0), otherSpeedDisplacement(0) {
    currentDirection = SE;
    this->setCurrentDirection();
    currentState = WALKING;

    spriteWalking.setDestRect(x, y,
                              cfg["WALKING_W"].as<int>(),
                              cfg["WALKING_H"].as<int>());
    spriteWalking.setOffsetXY(cfg["WALKING_OFFSET_X"].as<int>(),
                              cfg["WALKING_OFFSET_Y"].as<int>());

    spriteDying.setDestRect(x, y,
                            cfg["DYING_W"].as<int>(),
                            cfg["DYING_H"].as<int>());
}

void UnitView::setXY(int x, int y) {
    View::setXY(x, y);
    spriteWalking.setDestXY(x, y);
    int offsetX = cfg["WALKING_OFFSET_X"].as<int>();
    int offsetY = cfg["WALKING_OFFSET_Y"].as<int>();
    if (currentDirection == SO || currentDirection == NO)
        offsetX -= PIXELS * 2;
    if (currentDirection == NE || currentDirection == NO)
        offsetY -= PIXELS;
    spriteWalking.setOffsetXY(offsetX, offsetY);
}

void UnitView::draw(Uint32 ticks) {
    if (currentState == WALKING) {
        if (accumulatedDisplacement + otherSpeedDisplacement < PIXELS) {
            this->setNumberOfPixelsToMove(ticks);
            this->setOffsetXY();
        }
        spriteWalking.setStartXStartY(cfg["WALKING_START_X"].as<int>(),
                                      cfg["WALKING_START_Y"].as<int>()
                                      + currentDirection *
                                        cfg["WALKING_H"].as<int>());
        spriteWalking.setTimePerSprite(timePerPixel);
        spriteWalking.nextAndDraw(ticks);
    } else if (currentState == DYING) {
        if ((spriteDying.getCurrentSprite() + 1)
            == cfg["DYING_COLUMNS"].as<int>())
            currentState = DEAD;
        spriteDying.nextAndDraw(ticks);
    } else if (currentState == FROZEN) {
        spriteWalking.draw();
        if ((ticks - initTime) >= freezeTime) {
            lastTime = ticks;
            this->finishFreeze();
        }
    }
}

void UnitView::move(int x, int y, int nextX, int nextY) {
    if (currentState == FROZEN) currentState = WALKING;
    this->setXY(x, y);
    this->nextX = nextX;
    this->nextY = nextY;
    initTime = SDL_GetTicks();
    isFirstStep = true;
    accumulatedDisplacement = 0;
    otherSpeedDisplacement = 0;
}

void UnitView::setNumberOfPixelsToMove(Uint32 currentTime) {
    Uint32 elapsedTime = currentTime - initTime;
    int displacement = elapsedTime / timePerPixel + otherSpeedDisplacement;
    currentDisplacement = displacement - (accumulatedDisplacement +
                                            otherSpeedDisplacement);

    if (isFirstStep && (displacement >= (PIXELS / 2)))
        currentDisplacement = (PIXELS / 2) - (accumulatedDisplacement +
                                              otherSpeedDisplacement);

    if (displacement >= PIXELS)
        currentDisplacement = PIXELS - (accumulatedDisplacement +
                                        otherSpeedDisplacement);

    accumulatedDisplacement += currentDisplacement;
    lastTime = currentTime;
}

void UnitView::setOffsetXY() {
    int x = spriteWalking.getOffsetX() + (directionX * currentDisplacement)*2;
    int y = spriteWalking.getOffsetY() + directionY * currentDisplacement;
    spriteWalking.setOffsetXY(x, y);
    if (isFirstStep && ((accumulatedDisplacement +
                         otherSpeedDisplacement) == (PIXELS / 2))) {
        isFirstStep = false;
        this->calculateNewDirection();
    }
}

void UnitView::calculateNewDirection() {
    if (nextX == x) {
        if (nextY > y)
            currentDirection = SO;
        else
            currentDirection = NE;
    }

    if (nextY == y) {
        if (nextX > x)
            currentDirection = SE;
        else
            currentDirection = NO;
    }
    this->setCurrentDirection();
}

void UnitView::setCurrentDirection() {
    if (currentDirection == NO) {
        directionX = 1;
        directionY = 1;
    }
    if (currentDirection == SO) {
        directionX = 1;
        directionY = -1;
    }
    if (currentDirection == SE) {
        directionX = -1;
        directionY = -1;
    }
    if (currentDirection == NE) {
        directionX = -1;
        directionY = 1;
    }
}

void UnitView::enableDying() {
    currentState = DYING;
    spriteDying.setDestXY(x, y);
    spriteDying.setTimePerSprite(timePerPixel);
    spriteDying.setStartXStartY(cfg["DYING_START_X"].as<int>(),
                                cfg["DYING_START_Y"].as<int>()
                                + currentDirection *
                                  cfg["DYING_H"].as<int>());
    int offsetX = spriteWalking.getOffsetX() +
            cfg["DYING_OFFSET_X"].as<int>();
    int offsetY = spriteWalking.getOffsetY() +
            cfg["DYING_OFFSET_Y"].as<int>();
    spriteDying.setOffsetXY(offsetX, offsetY);
}

int UnitView::getId() {
    return id;
}

bool UnitView::isDead() {
    return (currentState == DEAD);
}

void UnitView::setSpeed(Uint32 newSpeed) {
    timePerPixel = newSpeed / PIXELS;
    initTime = lastTime;
    otherSpeedDisplacement += accumulatedDisplacement;
    accumulatedDisplacement = 0;
}

void UnitView::totalFreeze(Uint32 t) {
    if (currentState == DYING || currentState == DEAD) return;
    initTime = SDL_GetTicks();
    freezeTime = t;
    currentState = FROZEN;
}

void UnitView::finishFreeze() {
    currentState = WALKING;
    initTime = lastTime;
    otherSpeedDisplacement += accumulatedDisplacement;
    accumulatedDisplacement = 0;
}
