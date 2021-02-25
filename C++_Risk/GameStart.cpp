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
#include "GameStart.h"
#include <ctime>
#include <cstdlib>
using namespace std;

//Constructor
GameStart::GameStart() {
	this->vs = {};



}

//Accessor
vector<string> GameStart::getVectorString() {
	return this->vs;
}

vector<Player> GameStart::getPlayers() {
	return this->players;
}

vector<DiceFacility> GameStart::getDfs() {
	return this->dfs;
}

vector<Hand> GameStart::getHands() {
	return this->hands;
}

MapLoader GameStart::getMapLoader() {
	return this->mapLoader;
}

Deck GameStart::getDeck() {
	return this->deck;
}

vector<Player> GameStart::getPlayerOrder() {
	return this->playerOrder;
}

//Mutator
void GameStart::setVectorString(vector<string> vs) {
	this->vs = vs;
}

void GameStart::setDfs(vector<DiceFacility> dfs) {
	this->dfs = dfs;
}

void GameStart::setHands(vector<Hand> hands) {
	this->hands = hands;
}

void GameStart::setPlayers(vector<Player> players) {
	this->players = players;
}

void GameStart::setMapLoader(string mapName) {

	this->mapLoader = MapLoader(mapName);
}




//Other methods
void GameStart::storeMapsFromDir(char *dir_name) {
	DIR *dir; //pointer to an open directory
	struct dirent *entry; //files in the directory

	vector<string> vs = this->getVectorString(); //may not be needed



	   //1.open
	dir = opendir(dir_name);
	if (!dir) {
		cout << "Directory was not found\n" << endl;
		return;
	}

	//2.read
	while ((entry = readdir(dir)) != NULL) {
		if (entry->d_name[0] != '.')
		{

			string path = string(entry->d_name);
			//Commented out for DEMO!
			//cout << "Entry = " << path << endl;
			if (path.substr(path.find_last_of(".") + 1) == "map") {
				//Commented out for DEMO!
				//cout << "Yes a map exists: " << path.substr(path.find_last_of(".") + 1) << endl;

				vs.push_back(path); //stores files with .map extension

			}
			else {
				//Commented out for DEMO!
				//cout << "No a map does not exist: " << path.substr(path.find_last_of(".") + 1) << endl; 
			}

		}


	}

	this->setVectorString(vs);


	//3.close
	closedir(dir);

}

void GameStart::printMapOptions() {
	for (unsigned i = 0; i < this->vs.size(); i++) {
		cout << "[ " << i << " ] " << this->vs[i] << endl;
	}
}

void GameStart::gameUI() {
	int mapNum, numOfPlayers;
	cout << "GameStart..." << endl;
	cout << "*************************************************" << endl;
	storeMapsFromDir((char*)".");
	printMapOptions(); //show all maps in a given directory
	cout << "*************************************************" << endl;
	cout << "These are all the maps in the given directory" << endl;
	cout << "Please enter the number of the map of your choice!" << endl;
	cin >> mapNum;

	//checks whether a valid mapNum is inputed
	while (mapNum<0 || mapNum>(this->vs.size() - 1)) {
		cout << "Please enter a valid number of the map of your choice!" << endl;
		cin >> mapNum;
	}
	cout << "Chosen map is : [ " << mapNum << " ] " << this->vs.at(mapNum) << endl;
	//checking if chosen map is valid
	cout << "" << endl;
	cout << "Map validation..." << endl;
	cout << "*************************************************" << endl;

	this->setMapLoader(this->vs.at(mapNum));

	// MapLoader maploader(this->vs.at(mapNum));
	Map *map = this->mapLoader.getMap();

	map->setMapName(this->vs.at(mapNum));
	cout << "Map Name: " << map->getMapName() << endl;
	cout << "Is map fully connected? (True=1 & False=0) : " << map->isMapFullyConnected() << endl;

	if (map->isMapFullyConnected() == false) {
		cout << "Map is not fully connected!" << endl;
		system("pause");//only for DEMO
		exit(0);
	}

	cout << "Is Map valid? (True=1 & False=0) :" << map->isMapValid() << endl;

	if (map->isMapValid() == false) {
		cout << "Map is not valid!" << endl;
		system("pause"); //only for DEMO
		exit(0);
	}

	cout << "Number of Countries loaded: " << (map->getContainedCountryInMap()).size() << endl;
	cout << "*************************************************" << endl;

	cout << "Player initialization..." << endl;
	cout << "*************************************************" << endl;
	cout << "Please enter the number of players between 2(inclusive) and 6(inclusive): " << endl;
	cin >> numOfPlayers;

	//checks if the numOfPlayers is valid
	while (numOfPlayers < 2 || numOfPlayers>6) {
		cout << "Please enter a valid number of players between 2(inclusive) and 6(inclusive): " << endl;
		cin >> numOfPlayers;
	}
	cout << "Number of players is : " << numOfPlayers << endl;
	cout << "Creating players... : " << endl;


	vector<Player> players;
	players.resize(numOfPlayers); //setting the size of the players vector


	vector<DiceFacility> dfs;
	dfs.resize(numOfPlayers);//setting the size of the diceFacility vector


	vector<Hand> hands;
	hands.resize(numOfPlayers);//setting the size of the hands vector



	int numOfCountries = map->getContainedCountryInMap().size();
	Deck deck(numOfCountries); //Deck created given the number of countries available

	deck.addCardsInDeck(numOfCountries);
	this->deck = deck;//intializes the attribute

	deck.addCardsInDeck(numOfCountries);//Initializing cards in the deck randomly

	//Printing cards in the deck...
	cout << "Printing cards in the deck...." << endl;
	cout << "-------------------------------------------------------------------" << endl;
	for (unsigned i = 0; i < deck.getCardsInDeck().size(); i++) {
		cout << "Card number " << i << " is of type: " << deck.getCardsInDeck()[i].cardType(deck.getCardsInDeck()[i]) << " and type name is: " << deck.getCardsInDeck()[i].cardTypeName(deck.getCardsInDeck()[i].getType()) << endl;

	}
	cout << "-------------------------------------------------------------------" << endl;




	for (unsigned i = 0; i < players.size(); i++) {

		players[i].setOwnerNum(i + 1); //set player number
		cout << "Player " << i + 1 << " has an owner number: " << players[i].getOwnerNum() << endl;
		cout << "\n" << endl;

		players[i].setDiceFacility(dfs[i]);//set dice facility 


		cout << "Player " << i + 1 << " dice roll stats: " << endl;
		players[i].getDiceFacility().diceRollStats();
		cout << endl;

		// Card c1 = Card(1);
		 //hands[i].addCardToHand(deck.getCardsInDeck()[3]);
		players[i].setHand(hands[i]);//set empty hand of cards

		cout << "Player " << i + 1 << " empty cards in hand (size=0 for cardsInHand vector): " << players[i].getHand().getCardsInHand().size() << "\n" << endl;

		cout << "-------------------------------------------------------------------" << endl;


	}

	//Mutate attributes
	this->setDfs(dfs);
	this->setHands(hands);
	this->setPlayers(players);

	int size = this->getPlayers().size();


	this->playerOrder.resize(size);


	Player nullPlayer = Player(size + 1);// size+1 value


	for (int i = 0; i < size; i++) {
		this->playerOrder[i] = nullPlayer;
		// cout << "nullPlayer owner number: " << this->playerOrder[i].getOwnerNum() << endl;
	}


	cout << "Game Start Complete!!!..." << endl;
}

void GameStart::assignPlayerOrder() {

	//Store the numberOfPlayers
	int numOfPlayers = this->getPlayers().size();
	//cout << "this->gs.getPlayers().size(): " << this->gs.getPlayers().size() << endl;
	vector<Player> playersTemp;
	playersTemp.resize(numOfPlayers);

	for (unsigned i = 0; i < playersTemp.size(); i++) {
		playersTemp[i] = this->getPlayers()[i];
	}



	srand((unsigned)time(0));


	int randIndex;
	int count = 0;

	bool randomized = false;

	int index;



	while (randomized == false) {

		randIndex = rand() % numOfPlayers;
		//cout << "randIndex: " << randIndex << endl;
		index = rand() % playersTemp.size();


		if (this->playerOrder[randIndex].getOwnerNum() == (numOfPlayers + 1)) { //nullPlayer with an owner number of numOfPlayers+1
		   // cout << "IF STATEMENT!" << endl;
			//set the value to this object
			this->playerOrder[randIndex] = playersTemp[index];
			cout << "playerOrder owner number " << this->playerOrder[randIndex].getOwnerNum() << " at index :" << randIndex << endl;
			playersTemp.erase(playersTemp.begin() + index);

			count++;


		}



		if (count == numOfPlayers) {
			randomized = true;
		}



	}




	cout << "End of assigning players randomly!" << endl;


}

void GameStart::assignCountriesToPLayers() {

	//Get the number of countries
	int numOfCountries = this->getMapLoader().getMap()->getContainedCountryInMap().size();
	cout << "numOfCountries :" << numOfCountries << endl;

	int count = 0;
	vector<Country*> countriesInMapTemp;
	countriesInMapTemp.resize(numOfCountries);


	srand((int)time(0));
	int randIndex;


	//Storing countries in a temporary container
	for (unsigned i = 0; i < countriesInMapTemp.size(); i++) {
		//cout << "Inside for loop" << endl;
		countriesInMapTemp[i] = this->getMapLoader().getMap()->getContainedCountryInMap()[i];//stores all values in the temp container


	}
	cout << "After the for loop" << endl;
	cout << "Size of countriesInMapTemp: " << countriesInMapTemp.size() << endl;



	while (count != numOfCountries) {

		for (unsigned i = 0; i < this->playerOrder.size(); i++) {
			if (countriesInMapTemp.size() == 0) {
				break;
			}
			else {

				randIndex = rand() % countriesInMapTemp.size();
				cout << "randIndex: " << randIndex << endl;
				this->playerOrder[i].setOwnedCountry(countriesInMapTemp[randIndex]);


				countriesInMapTemp[randIndex]->setOwnerNumber(this->playerOrder[i].getOwnerNum());
				
				//USED IN ATTACK PHASE
				Player* tempPlayer = &playerOrder[i];
				countriesInMapTemp[randIndex]->setPlayer(tempPlayer);
				//===============================================
				

				count++;

				//remove the country from the vector
				countriesInMapTemp.erase(countriesInMapTemp.begin() + randIndex);
				cout << "Player " << this->playerOrder[i].getOwnerNum() << " owns country: " << this->playerOrder[i].getOwnedCountries()[0]->getCountryName() << endl;
			}
		}

	}


	for (unsigned i = 0; i < this->players.size(); i++) {
		for (unsigned j = 0; j < this->players.size(); j++) {
			if (this->players[i].getOwnerNum() == this->playerOrder[j].getOwnerNum()) {
				this->players[i] = (this->playerOrder[j]);
			}
		}
	}

}


void GameStart::assignArmiesToPlayers() {
	//First store the given number of armies for individual players
	int numOfPlayers = this->getPlayerOrder().size();
	int numOfArmies = 0;
	int numOfArmiesTemp;

	switch (numOfPlayers) {
	case 2: numOfArmies = 40; break;
	case 3: numOfArmies = 35; break;
	case 4:numOfArmies = 30; break;
	case 5:numOfArmies = 25; break;
	case 6: numOfArmies = 20; break;
	}
	numOfArmiesTemp = numOfArmies;

	for (unsigned i = 0; i < this->getPlayerOrder().size(); i++) {
		this->playerOrder[i].setNumOfArmies(numOfArmies); //setting number of armies to each player initially
	   // cout << "Player " << this->playerOrder[i].getOwnerNum() << " has numOfArmies: " << this->playerOrder[i].getNumOfArmies() << endl;
	}
	cout << "\n" << endl;

	cout << "Army Placement Phase...." << endl;



	for (unsigned i = 0; i < this->getPlayerOrder().size(); i++) {



		for (unsigned j = 0; j < this->playerOrder[i].getOwnedCountries().size(); j++) {
			if (numOfArmies != 0) {
				this->playerOrder[i].getOwnedCountries()[j]->setNumOfArmies(this->playerOrder[i].getOwnedCountries()[j]->getNumOfArmies() + 1);
				numOfArmies = numOfArmies - 1;

				// cout << "Player " << this->playerOrder[i].getOwnerNum() << " owns country: " << this->playerOrder[i].getOwnedCountries()[j]->getCountryName() << " with numOfArmies: " << this->playerOrder[i].getOwnedCountries()[j]->getNumOfArmies() << endl;
			}

			if (j == this->playerOrder[i].getOwnedCountries().size() - 1 && numOfArmies != 0) {
				j = 0; //restart the iteration
			}

		}
		cout << "\n" << endl;
		numOfArmies = numOfArmiesTemp;


	}


	for (unsigned i = 0; i < this->players.size(); i++) {
		for (unsigned j = 0; j < this->players.size(); j++) {
			if (this->players[i].getOwnerNum() == this->playerOrder[j].getOwnerNum()) {
				this->players[i] = this->playerOrder[j];
			}
		}
	}

	// cout << "End of loop!" << endl;
	cout << "End of Army Placement Phase" << endl;

}