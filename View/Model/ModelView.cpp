#include "ModelView.h"
#include "PortalEntradaView.h"
#include "PortalSalidaView.h"

ModelView::ModelView(Renderer &renderer, TextureLoader &textureLoader) :
        renderer(renderer), textureLoader(textureLoader),
        map(0, 0, 0, renderer, textureLoader) {
}

ModelView::~ModelView() {
}


void ModelView::setMapWidthHeight(int w, int h) {
    map.setWidth(w);
    map.setHeight(h);

    for (int i = 0; i < (w + h); ++i)
        depthLevels.push_back(new DepthLevel());
}

bool ModelView::isValidTile(int x, int y) {
    return map.isValidTile(x, y);
}

void ModelView::createPathTile(int x, int y) {
    map.addPathTile(x, y);
}

void ModelView::createStructureTile(int x, int y) {
    map.addStructureTile(x, y);
}

void ModelView::createPortalEntrada(int x, int y) {
    PortalEntradaView *p = new PortalEntradaView(textureLoader, renderer);
    p->setXY(x, y);
    depthLevels[(x + y - 1)]->addPortalEntrada(p);
}


void ModelView::createPortalSalida(int x, int y) {
    PortalSalidaView *p = new PortalSalidaView(textureLoader, renderer);
    p->setXY(x, y);
    depthLevels[(x + y - 1)]->addPortalSalida(p);
}

void ModelView::createUnit(int id, int key,
                           int x, int y, int toX, int toY, Uint32 t) {
    UnitView *unit = new UnitView(id, key, textureLoader, renderer);
    unit->move(x, y, toX, toY, t);
    depthLevels[(x + y - 1)]->addUnit(unit);
    idDepthLevelsUnits[id] = x + y - 1;
}

void ModelView::createTower(int id, int key, int x, int y) {
    TowerView *tower = new TowerView(id, key, textureLoader, renderer);
    tower->setXY(x, y);
    depthLevels[(x + y - 1)]->addTower(tower);
    idDepthLevelsTowers[id] = x + y - 1;
}

void ModelView::createSpell(int key, int x, int y, Uint32 t) {
    SpellView *spell = new SpellView(key, textureLoader, renderer);
    spell->cast(x, y, t);
    depthLevels[(x + y - 1)]->addSpell(spell);
}

void ModelView::createShot(int key, int x, int y, int toX, int toY, Uint32 t) {
    ShotView *shot = new ShotView(key, textureLoader, renderer);
    shot->shoot(x, y, toX, toY, t);
    shots.push_back(shot);
}

void ModelView::moveUnit(int id, int x, int y, int toX, int toY, Uint32 t) {
    int levelIndex = idDepthLevelsUnits[id];
    UnitView *unit = depthLevels[levelIndex]->getUnit(id);
    depthLevels[levelIndex]->removeUnit(id);
    unit->move(x, y, toX, toY, t);
    depthLevels[(x + y - 1)]->addUnit(unit);
}

void ModelView::killUnit(int id) {
    int levelIndex = idDepthLevelsUnits[id];
    UnitView *unit = depthLevels[levelIndex]->getUnit(id);
    unit->enableDying();
}

void ModelView::draw(Uint32 time) {
    for (auto depthLevel : depthLevels)
        depthLevel->draw(time);
    for (auto shot : shots)
        shot->draw(time);
}
