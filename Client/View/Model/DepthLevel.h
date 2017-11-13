#ifndef TOWERDEFENSE_DEPTHLEVEL_H
#define TOWERDEFENSE_DEPTHLEVEL_H

#include <list>
#include "TowerView.h"
#include "SpellView.h"
#include "PortalView.h"
#include "UnitView.h"

class DepthLevel {
private:
    PortalView *portalEntrada;
    PortalView *portalSalida;
    std::list<SpellView *> spells;
    std::list<TowerView *> towers;
    std::list<UnitView *> units;
    
public:
    DepthLevel();
    ~DepthLevel();
    void addPortalEntrada(PortalView *portal);
    void addPortalSalida(PortalView *portal);
    void addSpell(SpellView *spell);
    void addTower(TowerView *tower);
    void addUnit(UnitView *unit);
    TowerView* getTower(int id);
    UnitView* getUnit(int id);
    void removeUnit(int id);
    void draw(Uint32 time);
    std::string onCLick(int x, int y);
};


#endif //TOWERDEFENSE_DEPTHLEVEL_H
