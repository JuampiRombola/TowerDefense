#ifndef TOWERDEFENSE_DEPTHLEVEL_H
#define TOWERDEFENSE_DEPTHLEVEL_H

#include <list>
#include <mutex>
#include "TowerView.h"
#include "SpellView.h"
#include "PortalView.h"
#include "UnitView.h"
#include "ShotView.h"

class DepthLevel {
private:
    PortalView *portalEntrada;
    PortalView *portalSalida;
    std::list<SpellView *> spells;
    std::list<SpellView *> spellsFloor;
    std::list<TowerView *> towers;
    std::list<UnitView *> units;
    std::list<ShotView *> shots;
    
public:
    DepthLevel();
    ~DepthLevel();
    void addPortalEntrada(PortalView *portal);
    void addPortalSalida(PortalView *portal);
    void addSpell(SpellView *spell);
    void addFloorSpell(SpellView *spell);
    void addTower(TowerView *tower);
    void addUnit(UnitView *unit);
    void addShot(ShotView *shot);
    TowerView* getTower(int id);
    UnitView* getUnit(int id);
    void removeUnit(int id);
    void draw(Uint32 time);
    TowerView* onCLick(int x, int y);
};


#endif //TOWERDEFENSE_DEPTHLEVEL_H
