#include "StartupPhase.h"
#include "GameStart.h"
#include <ctime>
#include <cstdlib>
#include "Player.h"
#include "Map.h"
//Constructor
StartupPhase::StartupPhase(GameStart gs) {
	this->gs=gs;
	int size= this->gs.getPlayers().size();
		
	
	this->playerOrder.resize(size);

		
	Player nullPlayer = Player(size+1);// size+1 value
	

	for (int i = 0; i < size; i++) {
		this->playerOrder[i] = nullPlayer;
		cout << "nullPlayer owner number: " << this->playerOrder[i].getOwnerNum() << endl;
	}
}

//Accessor
vector<Player> StartupPhase::getPlayerOrder() {
	return this->playerOrder;
}

GameStart StartupPhase::getGameStart() {
	return this->gs;
}

//Mutator
void StartupPhase::setPlayerOrder(vector<Player> playerOrder) {
	this->playerOrder= playerOrder;
}

void StartupPhase::setGameStart(GameStart gs) {
	this->gs = gs;
}

//Other methods
void StartupPhase::assignArmiesToPlayers() {
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
		cout << "Player " << this->playerOrder[i].getOwnerNum() << " has numOfArmies: " << this->playerOrder[i].getNumOfArmies() << endl; 
	}
	cout << "\n" << endl;

	cout << "Army Placement Phase...." << endl;
	


	for (unsigned i = 0; i < this->getPlayerOrder().size(); i++) {
		
		

		for (unsigned j = 0; j < this->playerOrder[i].getOwnedCountries().size(); j++) {
			if (numOfArmies!=0) {
				this->playerOrder[i].getOwnedCountries()[j]->setNumOfArmies(this->playerOrder[i].getOwnedCountries()[j]->getNumOfArmies()+1);
				numOfArmies = numOfArmies - 1;

				cout << "Player " << this->playerOrder[i].getOwnerNum() << " owns country: " << this->playerOrder[i].getOwnedCountries()[j]->getCountryName() << " with numOfArmies: " << this->playerOrder[i].getOwnedCountries()[j]->getNumOfArmies() << endl;
			}

			if (j == this->playerOrder[i].getOwnedCountries().size() - 1 && numOfArmies != 0) {
				j = 0; //restart the iteration
			}
			
		}
		cout << "\n" << endl;
		numOfArmies = numOfArmiesTemp;
		
		
	}
	cout << "End of loop!" << endl;
	cout << "End of Army Placement Phase" << endl;

}

void StartupPhase::assignCountriesToPLayers() {
	
	//Get the number of countries
	int numOfCountries = this->gs.getMapLoader().getMap()->getContainedCountryInMap().size();
	cout << "numOfCountries :" << numOfCountries << endl;
	
	int count = 0;
	vector<Country*> countriesInMapTemp;
	countriesInMapTemp.resize(numOfCountries);

	
	srand((int)time(0));
	int randIndex;
	
	
	//Storing countries in a temporary container
	for (unsigned i = 0; i < countriesInMapTemp.size(); i++) {
		//cout << "Inside for loop" << endl;
		countriesInMapTemp[i]= this->gs.getMapLoader().getMap()->getContainedCountryInMap()[i];//stores all values in the temp container
		
		
	}
	cout << "After the for loop" << endl;
	cout << "Size of countriesInMapTemp: " << countriesInMapTemp.size() << endl;
	

	
	while (count != numOfCountries) {

		for (unsigned i = 0; i< this->playerOrder.size(); i++) {
			if (countriesInMapTemp.size() == 0) {
				break;
			}
			else{

			randIndex= rand() % countriesInMapTemp.size();
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
			cout << "Player " << this->playerOrder[i].getOwnerNum() << " owns country: " << this->playerOrder[i].getOwnedCountries()[0]->getCountryName()<<endl;
			}
		}

	}
	
	

}




void StartupPhase::assignPlayerOrder() {

	//Store the numberOfPlayers
	int numOfPlayers= this->gs.getPlayers().size();
	//cout << "this->gs.getPlayers().size(): " << this->gs.getPlayers().size() << endl;
	vector<Player> playersTemp;
	playersTemp.resize(numOfPlayers);

	for (unsigned i = 0; i < playersTemp.size(); i++) {
		playersTemp[i] = this->gs.getPlayers()[i];
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
			
			//set the value to this object
			this->playerOrder[randIndex] = playersTemp[index];
			cout << "playerOrder owner number " << this->playerOrder[randIndex].getOwnerNum() << " at index :" << randIndex << endl;
			playersTemp.erase(playersTemp.begin()+index);
			
			count++;


		}



		if (count == numOfPlayers) {
			randomized = true;
		}

		
	
	}



	
	cout << "End of assigning players randomly!" << endl;
	

}

