#include <thread> 
#include <chrono>

#include "../../include/Commands/BuildTowerCommand.h"
#include "../../include/Commands/CastSpellCommand.h"
#include "../../include/Commands/UpgradeTowerCommand.h"
#include "../../include/TowerDefenseGame.h"
#include "../../include/GameConfiguration.h"
#include "../../include/ViewModels/CommandVM.h"
#include "../../include/ViewModels/UnitVM.h"
#include "../../include/ViewModels/ProjectileVM.h"
#include "../../include/ViewModels/TowerVM.h"

void PrintProjectilesVms(std::vector<ProjectileVM>& projsVMs);
void PrintUnitVms(std::vector<UnitVM>& vms);
void PrintCommandVM(CommandVM& cvm);
void PrintTowerVms(std::vector<TowerVM>& towers);

int main(int argc, char** argv)
{
	std::string s("/home/tino/Dropbox/taller1/net_towerdefense/TowerDefenseServer/config.yaml");
	GameConfiguration cfg(s);

	uint clockDelaymilliseconds = 0;
	TowerDefenseGame game(clockDelaymilliseconds, cfg);
	std::thread gameClock(&TowerDefenseGame::Run, &game);

	std::this_thread::sleep_for (std::chrono::milliseconds(1500));

	CastSpellCommand spell(Rayos, 1);
	BuildTowerCommand tower(Water, 2, 5);
	UpgradeTowerCommand upgrade(2, 5, Range);
	
	game.QueueCommand(&spell);
	game.QueueCommand(&tower);
	game.QueueCommand(&upgrade);


	std::this_thread::sleep_for (std::chrono::milliseconds(1500));

	Command* executed = game.GetExecutedCommand();
	if (executed != nullptr){
		CommandVM vm = executed->GetViewModel();
		PrintCommandVM(vm);
	}

	std::vector<UnitVM> unitVms = game.GetUnitViewModels();
	PrintUnitVms(unitVms);
	std::vector<ProjectileVM> projsVMs = game.GetProjectileViewModels();
	PrintProjectilesVms(projsVMs);
	std::vector<TowerVM> towersVM = game.GetTowerViewModels();
	PrintTowerVms(towersVM);


	gameClock.join();
	return 0;
}

void PrintTowerVms(std::vector<TowerVM>& towers){
	for (auto it = towers.begin(); it != towers.end(); ++it){
		TowerVM vm = *it;
		std::cout << "Hay una torre de " << std::flush;
		switch(vm.type){
			case Air:
				std::cout << "aire" << std::flush;
				break;
			case Ground:
				std::cout << "ground" << std::flush;
				break;
			case Fire:
				std::cout << "fire" << std::flush;
				break;
			case Water:
				std::cout << "water" << std::flush;
				break;
		}
		std::cout << " en (" << vm.xPos << ", " << vm.yPos << ") de level " << vm.level 
		<< " con " << vm.experience << " xp\n" << std::flush;
	}
}


void PrintProjectilesVms(std::vector<ProjectileVM>& projs){
	//imprimir projectiles.


}
void PrintUnitVms(std::vector<UnitVM>& vms){
	for (auto it = vms.begin(); it != vms.end(); ++it){
		UnitVM vm = *it;

		switch (vm.unitType){
			case uAbmonible:
				std::cout << "Hay un Abmonible " << std::flush;
				break;
			case uDemonioVerde:
				std::cout << "Hay un DemonioVerde " << std::flush;
				break;
			case uEspectro:
				std::cout << "Hay un Espectro " << std::flush;
				break;
			case uHalconSangriento:
				std::cout << "Hay un HalconSangriento " << std::flush;
				break;
			case uHombreCabra:
				std::cout << "Hay un HombreCabra " << std::flush;
				break;
			case uNoMuerto:
				std::cout << "Hay un NoMuerto " << std::flush;
				break;
		}

		std::cout << "Id: " << vm.id << ", con " << std::flush;
		std::cout << vm.healthPoints << "HP, en (" << std::flush;
		std::cout << vm.xPos << ", " << vm.yPos << ") que esta avanzando de tile cada " << std::flush;
		std::cout << vm.stepDelay_ms << " milisegundos\n" << std::flush;
	}
}

void PrintCommandVM(CommandVM& cvm){
	switch(cvm.type){
		case BuildTower:
			std::cout << "SE CONSTRUYO UNA TORRE ";
			switch(cvm.towerType){
				case Air:
					std::cout << "DE AIRE ";break;
				case Fire:
					std::cout << "DE FUEGO ";break;
				case Water:
					std::cout << "DE AGUA ";break;
				case Ground:
					std::cout << "DE TIERRA ";break;
			}
			std::cout << "EN (" << cvm.xPos << ", " << cvm.yPos << ")\n" << std::flush;
			break;
		case UpgradeTower:
			std::cout << "SE UPGRADEO ";
			switch(cvm.upgradeType){
				case Range:
					std::cout << "EL RANGO "; break;
				case Damage:
					std::cout << "EL DANIO "; break;
				case CollateralRange:
					std::cout << "EL RANGO COLLATERAL "; break;
				case Slow:
					std::cout << "EL EFECTO DE SLOW "; break;
			}
			std::cout << "DE LA TORRE QUE ESTA EN (" << cvm.xPos << ", " << cvm.yPos << ")\n" << std::flush;
			break;
		case CastSpell:
			std::cout << "SE TIRO UN SPELL, dependiendo del spell (si es por target o posicion)";
			std::cout << " si esta seteado el unitId o las coordenadas\n";
			//falta hacer todo el switch 
			break;
	}
}