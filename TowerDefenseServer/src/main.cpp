#include <thread> 
#include <chrono>

#include "Commands/BuildTowerCommand.h"
#include "Commands/CastSpellCommand.h"
#include "TowerDefenseGame.h"
#include "GameConfiguration.h"


int main(int argc, char** argv)
{
	std::string s("/home/tino/Dropbox/taller1/net_towerdefense/TowerDefenseServer/config.yaml");
	GameConfiguration cfg(s);

	uint freq = 0;
	if (argc == 2)
		freq = atoi(*(argv + 1));


	TowerDefenseGame game(freq, cfg);
	std::thread gameClock(&TowerDefenseGame::Run, &game);

	//std::this_thread::sleep_for (std::chrono::milliseconds(100));

	/*CastSpellCommand spell(Rayos, 1);
	CastSpellCommand spell1(Rayos, 1);
	CastSpellCommand spell2(Rayos, 1);
	CastSpellCommand spell3(Rayos, 1);*/
	BuildTowerCommand tower(Ground, 2, 5);
	
	if (!game.Ended()){
		//game.QueueCommand(&spell);
		//game.QueueCommand(&spell1);
		//game.QueueCommand(&spell2);
		//game.QueueCommand(&spell3);
		game.QueueCommand(&tower);
	}

	gameClock.join();
	return 0;
}

