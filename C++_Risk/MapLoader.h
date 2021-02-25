#pragma once
#include "Map.h"
using namespace std;
class MapLoader {
public:
	//Constructor
	MapLoader();
	MapLoader(string fileDirectory);
	

	//Accessor
	Map* getMap();

	//Mutator
	

//private:
	//Attributes
	Map* map;
};