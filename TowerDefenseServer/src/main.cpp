#include <thread> 
#include <chrono>


#include "TowerDefenseGame.h"


int main(int argc, char** argv)
{
	TowerDefenseGame game;
	std::thread gameClock(&TowerDefenseGame::Run, &game);

	std::this_thread::sleep_for (std::chrono::milliseconds(3000));

	

	gameClock.join();
	return 0;
}

