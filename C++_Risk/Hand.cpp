/*
 * hand.cpp
 *
 *  Created on: Oct. 4, 2018
 *      Author: jonathan
 */




#include<iostream>
#include <algorithm>


#include "Hand.h"
#include "Card.h"
#include<vector>
using namespace std;
using std::remove;

//DONE

//Constructor
Hand::Hand() {
	//this->cardsInHand = {}; //empty cards in hand
}

Hand::Hand(vector<Card> cardsInHand) {
	this->cardsInHand = cardsInHand;
}

//Accessor
vector<Card> Hand::getCardsInHand() {
	
	return this->cardsInHand;
}



int Hand::getTimesExchanged() {
	return this->timesExchanged;
}

//Mutator
void Hand::setCardsInHand(vector<Card> vc) {
	cout << "Entered setCardsInHand()!" << endl;
	this->cardsInHand = vc;
	cout << "cards is : " << this->getCardsInHand().size() << endl;
}



void Hand::setTimeExchanged(int ex) {
	
	this->timesExchanged = ex;
}
//Other methods

void Hand::printAllCardsInHand() {
	cout << "|------------------------------------|" << endl;
	cout << ".....Printing all cards in hand......." << endl;
	cout << "|------------------------------------|" << endl;
	for (int i = 0; i < this->getCardsInHand().size(); i++) {
		cout << "card [ " << i << " ] :  has a card type: "<< this->getCardsInHand()[i].getType()<<" ( " << this->getCardsInHand()[i].cardTypeName(this->getCardsInHand()[i].getType())<<" )" <<endl;
	}
}

void Hand::addCardToHand(Card c) {
	
	this->cardsInHand.push_back(c);
	
}



int Hand::exchange() {
	int cardsRemoved = 0;
	int armies;
	//If cards in hand is less than 3
	if (this->getCardsInHand().size()<3) {
		return 0; // No armies
	}
	else if (this->getCardsInHand().size() == 5 || (this->getCardsInHand().size() >= 3 || this->getCardsInHand().size() < 5)) {//if cards in hand are 5 or 3, remove 3 cards
		int numV=0;
		vector<Card> cardsVec= (this->getCardsInHand());
		cout << "Total number of cards in hand : " << this->getCardsInHand().size()<<endl;
		cout << "Please remove 3 cards of your choice in exchange for armies: " << endl;
		for (unsigned i = 0; i < this->getCardsInHand().size(); i++) {
			
			
			cout << "Would you like to remove the card : " << this->getCardsInHand()[i].getType() << " ? (Yes=1 & No=0)" << endl;
			cin >> numV;
			if (numV == 1) {
				
				cardsRemoved++;
				
				cout << "Removing card : " << this->getCardsInHand()[i].getType() << "...." << endl;
				
				
				//v.erase(std::remove(v.begin(), v.end(), 99), v.end());
				//cardsVec.erase(std::remove(cardsVec.begin(), cardsVec.end(), cardsVec.at(i)), cardsVec.end());
				
				for(int j=0;j<this->getCardsInHand().size();j++){
					if(this->getCardsInHand()[i].getType()==this->cardsInHand[j].getType()){
						this->cardsInHand[j].setType(0);
						break;
					}
					
				}
					//this->printAllCardsInHand();
				
				cardsVec.erase(cardsVec.begin() + 0);
				
			}
			else {
				continue;
			}

			if (cardsRemoved == 3) {
				
				cout << "3 cards have been removed!" << endl;

				armies = (5 * this->getTimesExchanged());
				this->timesExchanged++;
				this->printAllCardsInHand();
				return armies;

				
			}


		}

	}
	
		return 0;
	
}




int Hand::exchange2() {
	int cardsRemoved = 0;
	int armies;
	//If cards in hand is less than 3
	if (this->getCardsInHand().size() < 3) {
		return 0; // No armies
	}
	else if (this->getCardsInHand().size() == 5 || (this->getCardsInHand().size() >= 3 || this->getCardsInHand().size() < 5)) {//if cards in hand are 5 or 3, remove 3 cards
		cout << "Inside exchange2()" << endl;
		this->printAllCardsInHand();

		this->cardsInHand[1].setType(0);
		//this->printAllCardsInHand();

		
		this->cardsInHand.erase(this->cardsInHand.begin() + 1);
		//this->cardsInHand.erase(std::remove(this->cardsInHand.begin(), this->cardsInHand.end(), this->cardsInHand[0]), this->cardsInHand.end());
		
		/*
		for (int i = 0; i < this->cardsInHand.size(); i++) {
			if()
		}

		*/

		//this->printAllCardsInHand();

	}
}




/*

int Hand::exchange2() {

	int nbArmies = 0;
	if (hand.size() < 3) {
		return 0;
	}
	else {
		int infantry = 0, artillery = 0, cavalry = 0;

		for (int i = 0; i < hand.size(); i++)
		{
			if (hand[i] == 1)
				++infantry;
			else if (hand[i] == 2)
				++artillery;
			else
				++cavalry;
		}

		if (infantry >= 3 || artillery >= 3 || cavalry >= 3 || (cavalry >= 1 && infantry >= 1 && artillery >= 1))
		{

			nbArmies += timesExchanged * 5;
			timesExchanged++;
			return nbArmies;
		}
		else
			return 0;
	}


}

*/




