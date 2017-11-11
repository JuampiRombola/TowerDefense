#include "DepthLevel.h"

DepthLevel::DepthLevel() : portalEntrada(nullptr), portalSalida(nullptr) {}

void DepthLevel::addPortalEntrada(PortalView *portal) {
    portalEntrada = portal;
}

void DepthLevel::addPortalSalida(PortalView *portal) {
    portalSalida = portal;
}

void DepthLevel::addSpell(SpellView *spell) {
    spells.push_back(spell);
}

void DepthLevel::addTower(TowerView *tower) {
    towers.push_back(tower);
}

void DepthLevel::addUnit(UnitView *unit) {
    units.push_back(unit);
}

TowerView *DepthLevel::getTower(int id) {
    for (auto tower : towers)
        if (tower->getId() == id) return tower;
}

UnitView *DepthLevel::getUnit(int id) {
    for (auto unit : units)
        if (unit->getId() == id) return unit;
}

void DepthLevel::removeUnit(int id) {
    units.remove_if([&id] (UnitView *unit) {return unit->getId() == id;});
}

void DepthLevel::draw(Uint32 time) {
    if (portalEntrada) portalEntrada->draw(time);

    //Remuevo las unidades que ya estan muertas
    units.remove_if([] (UnitView *unit) {return unit->isDead();}); //Estoy perdiendo memoria

    // Dibujo unidades
    for (auto unit : units)
        unit->draw(time);
        
    // Dibujo torres
    for (auto tower : towers)
        tower->draw(time);
    
    // Remuevo los spells que terminaron
    spells.remove_if([] (SpellView *spell) {return spell->hasFinished();}); //Estoy perdiendo memoria
    
    // Dibujo spells
    for (auto spell : spells)
        spell->draw(time);
    
    if (portalSalida) portalSalida->draw(time);
}

std::string DepthLevel::onCLick(int x, int y) {
    std::string result;
    for (auto tower : towers) {
        if (tower->getX() == x) {
            result.append(tower->onClick());
            return std::move(result);
        }
    }

    for (auto unit : units) {
        if (unit->getX() == x)
            if (!result.empty())
                result.append(",");
            result.append(unit->onClick());
    }
    return std::move(result);
}

