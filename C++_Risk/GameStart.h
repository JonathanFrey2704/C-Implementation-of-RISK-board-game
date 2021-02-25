#pragma once
#include "dirent.h"
#include <sys/stat.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "Map.h"
#include "MapLoader.h"
#include "Player.h"
#include "DiceRoller.h"
#include "Deck.h"
#include "Hand.h"
using namespace std;

class GameStart {

public:
	//Constructor
	GameStart();

	//Accessor
	vector<string> getVectorString();

	vector<Player> getPlayers();
	vector<DiceFacility> getDfs();
	vector<Hand> getHands();
	MapLoader getMapLoader();
	Deck getDeck();

	vector<Player> getPlayerOrder();
	
	//Mutator
	void setVectorString(vector<string> vs);
	
	void setPlayers(vector<Player> players);
	void setDfs(vector<DiceFacility> dfs);
	void setHands(vector<Hand> hands);

	void setMapLoader(string mapName);

	
	

	//Other methods
	
	void storeMapsFromDir(char *dir_name);
	void printMapOptions();
	void gameUI();
	
	void assignPlayerOrder();
	void assignCountriesToPLayers();
	void assignArmiesToPlayers();

	friend class StartupPhase;
	
//private: 
	//Attributes
	vector<string> vs;//holds all possible map files in a given directory

	vector<Player> players;
	vector<DiceFacility> dfs;
	vector<Hand> hands;
	vector<Player> playerOrder;

	MapLoader mapLoader;
	Deck deck;

};