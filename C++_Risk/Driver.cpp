#include "Map.h"
#include "MapLoader.h"
#include<iostream>
#include"Hand.h"
#include"Deck.h"
#include "DiceRoller.h"
#include<ctime>
#include"Player.h"
#include "Dirent.h"
#include <sys/stat.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "GameStart.h"
#include "StartupPhase.h"
#include "Reinforce.h"
#include "Fortify.h"
using namespace std;


int main() {


	//GameStart & StartupPhase DEMO-------------------------------------------------------------------------------
	GameStart gs;
	gs.gameUI();
	cout << "Number of Cards in the Deck: " << gs.getDeck().getCardsInDeck().size() << endl;
	cout << "Cards in the Deck: " << endl;
	gs.getDeck().printAllCardsInDeck(gs.getDeck().getCardsInDeck());


	
	
	gs.assignPlayerOrder();
	
	
	gs.assignCountriesToPLayers();
	
	cout << "\n" << endl;

	for (unsigned i = 0; i < gs.getPlayerOrder().size(); i++) {
		gs.getPlayerOrder()[i].printPlayerOwnedCountries();
	
		cout << "\n" << endl;
	}

	

	
	gs.assignArmiesToPlayers();

	cout << "\n" << endl;

	//After adding numOfArmies

	
	for (unsigned i = 0; i < gs.getPlayerOrder().size(); i++) {
		gs.getPlayerOrder()[i].printPlayerOwnedCountries();
		cout << "\n" << endl;
	}
	
	

	//system("pause");
	
	/*
	//MainGame Loop DEMO-------------------------------------------------------------------------------
	Map *mapTemp = gs.getMapLoader().getMap();
	int controls=0;

	vector<Player> players = gs.getPlayerOrder();

	Player *p1 = &players[0];
	
	cout << "STARTING MAIN GAME LOOP........." << endl;
	do {
		for (int i = 0; i < gs.getPlayerOrder().size(); i++) {
			cout << "REINFORCEMENT PHASE.........." << endl;
			//ReinForcement phase
			cout << "Player owner num: " << gs.getPlayerOrder()[i].getOwnerNum() << endl;
			Reinforce test(gs.getPlayerOrder()[i], mapTemp);

			cout << endl << endl << endl;
			//Attack phase
			p1->attack1();
			cout << endl << endl << endl;

			//Fortification phase
			Fortify fortify1 = Fortify(gs.playerOrder[i]);

		}
		controls = 1;
		if (controls == 1)
			cout << "Player 1 controls all of the countries. He wins" << endl;

	} while (controls != 1);

	
	*/

	//Reinforcement Phase DEMO-------------------------------------------------------------------------------

	

	//testing reinforce
	Map *mapTemp = gs.getMapLoader().getMap();
	
	
	
	cout << "Player  " << gs.getPlayerOrder()[0].getOwnerNum() <<endl;
	
	
	for (int i = 0; i<5; i++)
	{
		gs.deck.draw(gs.playerOrder[0].hand);
		
	}
	gs.getPlayerOrder()[0].getHand().printAllCardsInHand();

	cout << endl;

	Reinforce test(gs.getPlayerOrder()[0], mapTemp);
	

	cout << endl << endl;
	
	
	cout << "Player  " << gs.getPlayerOrder()[1].getOwnerNum() << endl;
	
	for (int j = 0; j <3; j++)
	{
		gs.deck.draw(gs.playerOrder[1].hand);
	}
	gs.getPlayerOrder()[1].getHand().printAllCardsInHand();
	cout << endl;
	Reinforce test2(gs.getPlayerOrder()[1], mapTemp);
	
	cout << "DONE!" << endl;
	
	/*
	
	//Attack Phase DEMO-------------------------------------------------------------------------------
	
	
	//Attack Phase
	//Attack Phase
	vector<Player> players = gs.getPlayerOrder();

	Player *p1 = &players[0];
	p1->attack();
	p1->getDiceFacility().diceRollStats();
	system("pause");
	
	*/
	
	
	//Fortification Phase DEMO-------------------------------------------------------------------------------
	
	/*
	Fortify fortify1 = Fortify(gs.playerOrder[0]);
	Fortify fortify2 = Fortify(gs.playerOrder[1]);
	*/
	
return 0;
}