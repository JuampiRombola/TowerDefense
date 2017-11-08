#ifndef TOWERDEFENSE_MODELVIEW_H
#define TOWERDEFENSE_MODELVIEW_H


#include "ShotView.h"
#include "MapView.h"
#include "DepthLevel.h"
#include <mutex>

#include <map>

class ModelView {
private:
    Renderer &renderer;
    TextureLoader &textureLoader;
    MapView *map;
    std::mutex m;
    std::vector<ShotView *> shots;
    std::vector<DepthLevel *> depthLevels;
    std::map<int, int> idDepthLevelsTowers;
    std::map<int, int> idDepthLevelsUnits;

public:
    ModelView(Renderer &renderer, TextureLoader &textureLoader);
    void draw(Uint32 time);
    void isClickOnMap(int x, int y);
    void createPathTile();
    void createStructureTile();
    void createPortal();
    void createUnit();
    void createTower();
    void createSpell();
    void createShot();

};


#endif //TOWERDEFENSE_MODELVIEW_H
