#include "DepthLevel.h"

DepthLevel::DepthLevel() : portalEntrada(nullptr), portalSalida(nullptr) {}

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
        delete (*it1++);
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
    auto it = units.begin();
    while (it != units.end()) {
        if ((*it)->isDead()) {
            delete (*it);
            it = units.erase(it);
        } else
            ++it;
    }

    // Dibujo unidades
    for (auto unit : units)
        unit->draw(time);
        
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
        if (unit->getX() == x) {
            if (!result.empty())
                result.append(",");
            result.append(unit->onClick());
        }
    }
    return std::move(result);
}
