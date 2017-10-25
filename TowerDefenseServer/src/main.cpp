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

		std::this_thread::sleep_for (std::chrono::milliseconds(4000));

	if (!game.Ended()){
		game.QueueCommand(std::shared_ptr<Command>(new CastSpellCommand(Grieta, 1, 0)));
		game.QueueCommand(std::shared_ptr<Command>(new BuildTowerCommand(Ice, 2, 5)));
	}

	gameClock.join();
	return 0;
}

