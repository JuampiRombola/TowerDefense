#include <iostream>
#include <algorithm>
#include "DepthLevel.h"

DepthLevel::DepthLevel()  : portalEntrada(nullptr), portalSalida(nullptr) {}

DepthLevel::~DepthLevel() {
    if (portalEntrada) delete portalEntrada;
    if (portalSalida) delete portalSalida;

    auto it1 = spells.begin();
    while (it1 != spells.end())
        delete (*it1++);
    auto it2 = towers.begin();
    while (it2 != towers.end())
        delete (*it2++);
    auto it3 = units.begin();
    while (it3 != units.end())
        delete (*it3++);
    auto it4 = shots.begin();
    while (it4 != shots.end())
        delete (*it4++);
    auto it5 = spellsFloor.begin();
    while (it5 != spellsFloor.end())
        delete (*it5++);
}

void DepthLevel::addPortalEntrada(PortalView *portal) {
    portalEntrada = portal;
}

void DepthLevel::addPortalSalida(PortalView *portal) {
    portalSalida = portal;
}

void DepthLevel::addSpell(SpellView *spell) {
    spells.push_back(spell);
}

void DepthLevel::addFloorSpell(SpellView *spell) {
    spellsFloor.push_back(spell);
}

void DepthLevel::addTower(TowerView *tower) {
    towers.push_back(tower);
}

void DepthLevel::addUnit(UnitView *unit) {
    units.push_back(unit);
}

void DepthLevel::addShot(ShotView *shot) {
    shots.push_back(shot);
}

TowerView *DepthLevel::getTower(int id) {
    for (auto tower : towers)
        if (tower->getId() == id) return tower;
}

UnitView *DepthLevel::getUnit(int id) {
    for (auto unit : units) {
        if (unit->getId() == id) 
            return unit;
    }
    return nullptr;
}

void DepthLevel::removeUnit(int id) {
    units.remove_if([&id] (UnitView *unit) {return unit->getId() == id;});
}

void DepthLevel::draw(Uint32 time) {
    if (portalEntrada) portalEntrada->draw(time);

    // Remuevo spells de suelo
    auto it1 = spells.begin();
    while (it1 != spells.end()) {
        if ((*it1)->hasFinished()) {
            delete (*it1);
            it1 = spells.erase(it1);
        } else
            ++it1;
    }

    // Dibujo spells de suelo
    for (auto spellFloor : spellsFloor)
        spellFloor->draw(time);

    // Dibujo unidades en sentido inverso
    for (auto it = units.rbegin(); it != units.rend(); ++it)
        (*it)->draw(time);

    //Remuevo las unidades que ya estan muertas
    units.remove_if([] (UnitView *unit) {
        if (unit->isDead()){
            delete unit;
            return true;
        }
        return false;});

    // Dibujo torres
    for (auto tower : towers)
        tower->draw(time);
    
    // Remuevo los spells que terminaron
    auto it2 = spells.begin();
    while (it2 != spells.end()) {
        if ((*it2)->hasFinished()) {
            delete (*it2);
            it2 = spells.erase(it2);
        } else
            ++it2;
    }

    // Dibujo spells
    for (auto spell : spells)
        spell->draw(time);

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

    if (portalSalida) portalSalida->draw(time);
}

TowerView* DepthLevel::onCLick(int x, int y) {
    for (auto tower : towers) {
        if (tower->getX() == x)
            return tower;
    }
    return nullptr;
}
