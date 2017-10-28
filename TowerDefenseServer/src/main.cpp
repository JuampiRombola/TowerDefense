#include <thread> 
#include <chrono>

#include "Commands/BuildTowerCommand.h"
#include "Commands/CastSpellCommand.h"

#include "TowerDefenseGame.h"


int main(int argc, char** argv)
{
	uint freq = 100;
	if (argc == 2)
		freq = atoi(*(argv + 1));


	TowerDefenseGame game(freq);
	std::thread gameClock(&TowerDefenseGame::Run, &game);

		std::this_thread::sleep_for (std::chrono::milliseconds(2500));

	CastSpellCommand spell(Rayos, 1);
	CastSpellCommand spell1(Rayos, 1);
	CastSpellCommand spell2(Rayos, 1);
	CastSpellCommand spell3(Rayos, 1);
	BuildTowerCommand tower(Ice, 2, 5);
	
	if (!game.Ended()){
		game.QueueCommand(&spell);
		game.QueueCommand(&spell1);
		game.QueueCommand(&spell2);
		game.QueueCommand(&spell3);
		game.QueueCommand(&tower);
	}

	gameClock.join();
	return 0;
}

