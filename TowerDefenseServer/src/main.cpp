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

		std::this_thread::sleep_for (std::chrono::milliseconds(1000));

	CastSpellCommand spell(Grieta, 6, 7);
	BuildTowerCommand tower(Ice, 2, 5);
	
	if (!game.Ended()){
		game.QueueCommand(&spell);
		//game.QueueCommand(&tower);
	}

	gameClock.join();
	return 0;
}

