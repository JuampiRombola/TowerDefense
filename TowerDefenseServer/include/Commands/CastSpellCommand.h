#ifndef _CAST_SPELL_COMMAND_
#define _CAST_SPELL_COMMAND_

#include "Commands/Command.h"
class Map;

enum Spell { Terraforming, Grieta, Meteorito, MuroDeFuego, Congelacion, Ventisca, Tornado, Rayos };

class CastSpellCommand : public Command {
private:
	unsigned int _xPos;
	unsigned int _yPos;
	unsigned int _unitId;
	Spell _spell;
	void _CastTerraforming(Map* map);
	void _CastGrieta(Map* map);
	void _CastMeteorito(Map* map);
	void _CastMuroDeFuego(Map* map);
	void _CastCongelacion(Map* map);
	void _CastVentisca(Map* map);
	void _CastTornado(Map* map);
	void _CastRayos(Map* map);

public:
	CastSpellCommand(Spell spell, unsigned int x, unsigned int y);
	CastSpellCommand(Spell spell, uint unitId);
	~CastSpellCommand();
	void Execute(Map* map);
	Spell GetSpellType();
};

#endif