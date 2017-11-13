#include "ModelView.h"
#include "PortalEntradaView.h"
#include "PortalSalidaView.h"
#include "../../../Common/Lock.h"

ModelView::ModelView(Renderer &renderer, TextureLoader &textureLoader) :
        renderer(renderer), textureLoader(textureLoader),
        map(0, 0, 0, renderer, textureLoader) {
}

ModelView::~ModelView() {
    auto it = shots.begin();
    while (it != shots.end())
        delete (*it++);

    for (unsigned int i = 0; i < depthLevels.size(); ++i)
        delete depthLevels[i];
}


void ModelView::setMapEnvironment(int type) {
    map.setEnvTile(type);
}

void ModelView::setMapWidthHeight(int w, int h) {
    map.setWidth(w);
    map.setHeight(h);

    for (int i = 1; i < (w + h); ++i)
        depthLevels.push_back(new DepthLevel());
}

bool ModelView::isValidTile(int x, int y) {
    return map.isValidTile(x, y);
}

void ModelView::createPathTile(int x, int y) {
    map.addPathTile(x, y);
}

void ModelView::createStructureTile(int x, int y) {
    Lock(this->m);
    map.addStructureTile(x, y);
}

void ModelView::createPortalEntrada(int x, int y) {
    PortalEntradaView *p = new PortalEntradaView(textureLoader, renderer);
    p->setXY(x, y);
    Lock(this->m);
    depthLevels[(x + y)]->addPortalEntrada(p);
}


void ModelView::createPortalSalida(int x, int y) {
    PortalSalidaView *p = new PortalSalidaView(textureLoader, renderer);
    p->setXY(x, y);
    Lock(this->m);
    depthLevels[(x + y)]->addPortalSalida(p);
}

void ModelView::createUnit(int id, int key,
                           int x, int y, int toX, int toY, Uint32 t) {
    UnitView *unit = new UnitView(id, key, textureLoader, renderer);
    unit->move(x, y, toX, toY, t);
    Lock(this->m);
    depthLevels[(x + y)]->addUnit(unit);
    idDepthLevelsUnits[id] = x + y;
}

void ModelView::createTower(int id, int key, int x, int y) {
    TowerView *tower = new TowerView(id, key, textureLoader, renderer);
    tower->setXY(x, y);
    Lock(this->m);
    depthLevels[(x + y)]->addTower(tower);
    idDepthLevelsTowers[id] = x + y;
}

void ModelView::createSpell(int key, int x, int y, Uint32 t) {
    SpellView *spell = new SpellView(key, textureLoader, renderer);
    spell->cast(x, y, t);
    Lock(this->m);
    depthLevels[(x + y)]->addSpell(spell);
}

void ModelView::createShot(int key, int x, int y, int toX, int toY, Uint32 t) {
    ShotView *shot = new ShotView(key, textureLoader, renderer);
    shot->shoot(x, y, toX, toY, t);
    Lock(this->m);
    shots.push_back(shot);
}

void ModelView::moveUnit(int id, int x, int y, int toX, int toY, Uint32 t) {
    Lock(this->m);
    int levelIndex = idDepthLevelsUnits[id];
    UnitView *unit = depthLevels[levelIndex]->getUnit(id);
    depthLevels[levelIndex]->removeUnit(id);
    unit->move(x, y, toX, toY, t);
    depthLevels[(toX + toY)]->addUnit(unit);
    idDepthLevelsUnits[id] = toX + toY;
}

void ModelView::killUnit(int id) {
    Lock(this->m);
    int levelIndex = idDepthLevelsUnits[id];
    UnitView *unit = depthLevels[levelIndex]->getUnit(id);
    unit->enableDying();
}

void ModelView::draw(Uint32 time) {
    Lock(this->m);

    // Dibujo mapa
    map.draw(time);

    //Dibujo por niveles
    for (auto depthLevel : depthLevels)
        depthLevel->draw(time);

    // Remuevo disparos terminados
    auto it = shots.begin();
    while (it != shots.end()) {
        if ((*it)->hasFinished()) {
            delete (*it);
            it = shots.erase(it);
        } else
            ++it;
    }

    // Dibujo disparos
    for (auto shot : shots)
        shot->draw(time);
}
