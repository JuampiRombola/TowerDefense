#include <iostream>
#include <algorithm>
#include "DepthLevel.h"

DepthLevel::DepthLevel()  : _unitsMutex(), _spellsMutex(), _towersMutex(),
                            portalEntrada(nullptr), portalSalida(nullptr) {}

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
}

void DepthLevel::addPortalEntrada(PortalView *portal) {
    portalEntrada = portal;
}

void DepthLevel::addPortalSalida(PortalView *portal) {
    portalSalida = portal;
}

void DepthLevel::addSpell(SpellView *spell) {
    std::lock_guard<std::mutex> lock(_spellsMutex);
    spells.push_back(spell);
}

void DepthLevel::addTower(TowerView *tower) {
    std::lock_guard<std::mutex> lock(_towersMutex);
    towers.push_back(tower);
}

void DepthLevel::addUnit(UnitView *unit) {
    std::lock_guard<std::mutex> lock(_unitsMutex);
    units.push_back(unit);
}

TowerView *DepthLevel::getTower(int id) {
    std::lock_guard<std::mutex> lock(_towersMutex);
    for (auto tower : towers)
        if (tower->getId() == id) return tower;
}

UnitView *DepthLevel::getUnit(int id) {
    std::lock_guard<std::mutex> lock(_unitsMutex);
    for (auto unit : units)
        if (unit->getId() == id) return unit;
}

void DepthLevel::removeUnit(int id) {
    std::lock_guard<std::mutex> lock(_unitsMutex);
    units.remove_if([&id] (UnitView *unit) {return unit->getId() == id;});
}

void DepthLevel::draw(Uint32 time) {
    if (portalEntrada) portalEntrada->draw(time);

    //Remuevo las unidades que ya estan muertas
   /* for (auto it = units.begin(); it != units.end(); ){
        if ((*it)->isDead()) {
            delete (*it);
            it = units.erase(it);
        } else {
            (*it)->draw(time);
            ++it;
        }
    }*/

    {    
        std::lock_guard<std::mutex> lock(_unitsMutex);

        units.erase(std::remove_if(units.begin(),
                                  units.end(),
                                  [](UnitView* x)
                                   
                                   {
                                       if (x->isDead()){
                                           delete x;
                                           return true;
                                       }
                                       return false;}),
                   units.end());
        
    
        for (auto it = units.begin(); it != units.end(); ++it){
            UnitView* u = *it;
            u->draw(time);
        }

    }
    
    {
        std::lock_guard<std::mutex> lock(_towersMutex);

        // Dibujo torres
        for (auto tower : towers)
            tower->draw(time); 
    }

    
    // Remuevo los spells que terminaron
    
    {
        std::lock_guard<std::mutex> lock(_spellsMutex);
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
    }

    
    if (portalSalida) portalSalida->draw(time);
}

TowerView* DepthLevel::onCLick(int x, int y) {
    std::lock_guard<std::mutex> lock(_towersMutex);
    for (auto tower : towers) {
        if (tower->getX() == x)
            return tower;
    }
    return nullptr;
}

