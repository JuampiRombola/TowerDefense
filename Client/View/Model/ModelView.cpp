#include <iostream>
#include "ModelView.h"
#include "PortalEntradaView.h"
#include "PortalSalidaView.h"
#include "../../../Common/Lock.h"
#include "DepthLevelError.h"

#define INVALID_INDEX "Se esta tratandod de acceder a una posicion invalida de DepthLevel"

ModelView::ModelView(Renderer &renderer, TextureLoader &textureLoader) :
        renderer(renderer), textureLoader(textureLoader),
        map(0, 0, 0, renderer, textureLoader), mapLoaded(false),
        mapLoadedMutex(), mapLoadedCondVariable() {}

ModelView::~ModelView() {
    auto it = shots.begin();
    while (it != shots.end())
        delete (*it++);

    for (unsigned int i = 0; i < depthLevels.size(); ++i) {
        delete depthLevels[i];
    }
}


void ModelView::setMapEnvironment(int type) {
    map.setEnvTile(type);
}

void ModelView::setMapWidthHeight(int w, int h) {
    map.setWidth(w);
    map.setHeight(h);

    // Agrego 2 niveles de mas para dar la ilusion de que se
    // pueda caminar hasta los bordes del mapa
    for (int i = 0; i <= (w + h); ++i)
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
    checkIndexDepthLevel(x+y+1);
    depthLevels[x+y+1]->addPortalEntrada(p);
}


void ModelView::createPortalSalida(int x, int y) {
    PortalSalidaView *p = new PortalSalidaView(textureLoader, renderer);
    p->setXY(x, y);
    Lock(this->m);
    checkIndexDepthLevel(x+y+1);
    depthLevels[x+y+1]->addPortalSalida(p);
}

void ModelView::createUnit(int id, int key,
                           int x, int y, int toX, int toY, Uint32 t) {
    UnitView *unit = new UnitView(id, key, textureLoader, renderer);
    unit->move(x, y, toX, toY, t);
    Lock(this->m);
    checkIndexDepthLevel(x+y+1);
    depthLevels[x+y+1]->addUnit(unit);
    idDepthLevelsUnits[id] = x + y + 1;
}

void ModelView::createTower(int id, int key, int x, int y) {
    TowerView *tower = new TowerView(id, key, textureLoader, renderer);
    tower->setXY(x, y);
    Lock(this->m);
    checkIndexDepthLevel(x+y+1);
    depthLevels[x+y+1]->addTower(tower);
    idDepthLevelsTowers[id] = x + y + 1;
}

void ModelView::createSpell(int key, int x, int y, Uint32 t) {
    SpellView *spell = new SpellView(key, textureLoader, renderer);
    spell->cast(x, y, t);
    Lock(this->m);
    checkIndexDepthLevel(x+y+1);
    depthLevels[x+y+1]->addSpell(spell);
}

void ModelView::createShot(int key, int x, int y, int toX, int toY, Uint32 t) {
    ShotView *shot = new ShotView(key, textureLoader, renderer);
    shot->shoot(x, y, toX, toY, t);
    Lock(this->m);
    shots.push_back(shot);
}

void ModelView::moveUnit(int id, int x, int y, int toX, int toY, Uint32 t) {
    Lock(this->m);
    int levelIndex = idDepthLevelsUnits.at(id);
    UnitView *unit = depthLevels[levelIndex]->getUnit(id);
    checkIndexDepthLevel(levelIndex);
    depthLevels[levelIndex]->removeUnit(id);
    unit->move(x, y, toX, toY, t);
    checkIndexDepthLevel(toX+toY+1);
    depthLevels[toX+toY+1]->addUnit(unit);
    idDepthLevelsUnits[id] = toX + toY + 1;
}

void ModelView::killUnit(int id) {
    Lock(this->m);
    int levelIndex = idDepthLevelsUnits.at(id);
    checkIndexDepthLevel(levelIndex);
    UnitView *unit = depthLevels[levelIndex]->getUnit(id);
    unit->enableDying();
}

void ModelView::draw(Uint32 time) {
    Lock(this->m);

    // Dibujo mapa
    map.draw(time);

    //Dibujo por niveles
    for (auto depthLevel : depthLevels)
        depthLevel->draw(SDL_GetTicks());

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

void ModelView::checkIndexDepthLevel(int key) {
    if (key >= depthLevels.size() || key < 0)
        throw DepthLevelError(INVALID_INDEX);
}
