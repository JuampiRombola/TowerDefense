#include <thread> 
#include <chrono>

#include "BuildTowerCommand.h"

#include "TowerDefenseGame.h"


int main(int argc, char** argv)
{
	if (argc != 2)
		return 0;

	uint freq = atoi(*(argv + 1));


	TowerDefenseGame game(freq);
	std::thread gameClock(&TowerDefenseGame::Run, &game);

	std::this_thread::sleep_for (std::chrono::milliseconds(1000));

	BuildTowerCommand cmd(Ground);

	game.QueueCommand(cmd);

	gameClock.join();
	return 0;
}

