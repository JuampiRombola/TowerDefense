#include <string>
#include <iostream>

#include <cstdlib>
#include <ctime>

#include "Map.h"

Map::Map(uint sideLength, std::string mapJsonConfig) 
: _sideLength(sideLength), _tiles()
{

	//
	// Aca levantariamos de archivo el mapa creado
	// en el editor de mapas, ahora en cambio armo un
	// mapa de manera random (lo mas tonto del mundo)
	//
	// Donde deje estaba probando hacer un mapa solo de 
	// caminos con orientacion derecha y abajo y intentando
	// poner el spawn en el (0,0) para despues spawnear bichos
	// y ver como paso a paso caminan por el path que hay
	//

	PathTile* tile; 
	std::srand(std::time(0)); // use current time as seed for random generator
	int random_variable = 0;
	for (int i = 0; (uint) i < _sideLength; i++)
	{
		_tiles.push_back(new std::vector<ITile*>(sideLength));
		for (int j = 0; (uint) j < sideLength; j++)
		{
			random_variable = std::rand() % 2;
    		ITile* newTile = NULL;
    		switch (random_variable){
    			case 0:
    				tile = new PathTile(right);
    				newTile = tile;
    				if (i == 0 && j == 0) _spawnTile = tile;
    				break;
    			case 1:
    				newTile = new PathTile(down);
    				break;
    		}
    		(*_tiles[i])[j] = newTile;		
		}
	}
}

Map::~Map(){
	for (int i = 0; (uint) i < _sideLength; i++)
	{
		std::vector<ITile*> *row = _tiles[i];
		for (int j = 0; (uint) j < _sideLength; j++)
		{
			ITile *tile = (*row)[j];
			delete tile;
		}
		delete row;
	}
}

void Map::DebugPrint(){
	for (int i = 0; (uint) i < _sideLength; i++)
	{
		std::vector<ITile*> *row = _tiles[i];
		for (int j = 0; (uint) j < _sideLength; j++)
		{
			ITile *tile = (*row)[j];
			std::cout << tile->GetSymbol();
		}
		std::cout << '\n';
	}
}

void Map::SpawnUnit(IEnviormentUnit* unit){

}
