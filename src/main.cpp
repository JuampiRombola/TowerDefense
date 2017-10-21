#include <thread> 


#include "TowerDefenseGame.h"


int main(int argc, char** argv)
{
    TowerDefenseGame game;
    std::thread gameClock(&TowerDefenseGame::Run, &game);

   	char c = 'a';


   	do {
		std::cin.get(c);

		if (c == '+')
			game.SpawnEnemy();

	} while (!game.Ended());

    gameClock.join();
    return 0;
}

