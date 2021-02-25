#pragma once
#include <vector>
#include <string>
#include "Player.h"
#include "GameStart.h"

class StartupPhase {
public:
	//Constructor
	StartupPhase(GameStart gs);

	//Accessor
	vector<Player> getPlayerOrder();
	GameStart getGameStart();

	//Mutator
	void setPlayerOrder(vector<Player> playerOrder);
	void setGameStart(GameStart gs);

	//Other methods
	void assignCountriesToPLayers();
	void assignArmiesToPlayers();
	void assignPlayerOrder();
	
	

//private:
	//Attributes
	vector<Player> playerOrder;
	GameStart gs;

};