#ifndef _CAST_SPELL_COMMAND_
#define _CAST_SPELL_COMMAND_

#include "../Commands/Command.h"
#include "../../../../Common/Protocolo.h"
class Map;
class TowerDefenseGame;

class CastSpellCommand : public Command {
private:
	int _xPos;
	int _yPos;
	int _unitId;
	CAST_SPELL_TYPE _spell;
	bool _CastTerraforming(Map* map, TowerDefenseGame* game);
	bool _CastGrieta(Map* map, TowerDefenseGame* game);
	bool _CastMeteorito(Map* map, TowerDefenseGame* game);
	bool _CastMuroDeFuego(Map* map, TowerDefenseGame* game);
	bool _CastCongelacion(Map* map, TowerDefenseGame* game);
	bool _CastVentisca(Map* map, TowerDefenseGame* game);
	bool _CastTornado(Map* map, TowerDefenseGame* game);
	bool _CastRayos(Map* map, TowerDefenseGame* game);

public:
	CastSpellCommand(CAST_SPELL_TYPE spell, uint x, uint y);
	CastSpellCommand(CAST_SPELL_TYPE spell, uint unitId);
	~CastSpellCommand();
	bool Execute(Map* map, TowerDefenseGame* game, ThreadSafeQueue<GameNotification*>& notifications);
	//CommandVM GetViewModel();
};

#endif