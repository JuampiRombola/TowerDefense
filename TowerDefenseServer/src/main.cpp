#include <thread> 
#include <chrono>

#include "BuildTowerCommand.h"

#include "TowerDefenseGame.h"


int main(int argc, char** argv)
{
	uint freq = 100;
	if (argc == 2)
		freq = atoi(*(argv + 1));


	TowerDefenseGame game(freq);
	std::thread gameClock(&TowerDefenseGame::Run, &game);


	if (!game.Ended()){
		game.QueueCommand(std::shared_ptr<Command>(new BuildTowerCommand(Ground, 2, 5)));
	}

	gameClock.join();
	return 0;
}

