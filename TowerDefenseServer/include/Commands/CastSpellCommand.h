#ifndef _CAST_SPELL_COMMAND_
#define _CAST_SPELL_COMMAND_

#include "Commands/Command.h"
class Map;
class TowerDefenseGame;

enum Spell { Terraforming, Grieta, Meteorito, MuroDeFuego, Congelacion, Ventisca, Tornado, Rayos };

class CastSpellCommand : public Command {
private:
	uint _xPos;
	uint _yPos;
	uint _unitId;
	Spell _spell;
	bool _CastTerraforming(Map* map);
	bool _CastGrieta(Map* map);
	bool _CastMeteorito(Map* map);
	bool _CastMuroDeFuego(Map* map);
	bool _CastCongelacion(Map* map, TowerDefenseGame* game);
	bool _CastVentisca(Map* map);
	bool _CastTornado(Map* map);
	bool _CastRayos(Map* map, TowerDefenseGame* game);

public:
	CastSpellCommand(Spell spell, uint x, uint y);
	CastSpellCommand(Spell spell, uint unitId);
	~CastSpellCommand();
	bool Execute(Map* map, TowerDefenseGame* game);
	Spell GetSpellType();
};

#endif