/*
 * deck.cpp
 *
 *  Created on: Oct. 4, 2018
 *      Author: jonathan
 */



#include<iostream>
using namespace std;

#include "Deck.h"
#include<vector>
#include "Hand.h"
#include <ctime>

//DONE


//Constructor
Deck::Deck() {
	//this->cardsInDeck = {};
}

Deck::Deck(int numOfCountries) {
	this->cardsInDeck.resize(numOfCountries);//vector is resized to the number of countries
}

//Accessor
vector<Card> Deck::getCardsInDeck() {
	return this->cardsInDeck;
}

vector<Hand> Deck::getHands() {
	return this->hands;
}

//Mutator
void Deck::setCardsInDeck(vector<Card> cards) {
	this->cardsInDeck = cards;
}

void Deck::setHands(vector<Hand> hands) {
	this->hands = hands;
}

//Other methods
void Deck::draw(Hand &hand) {

	int randIndex = rand() % this->cardsInDeck.size(); //random indexed from deck
	
	//cout << "card inside deck is: " << this->cardsInDeck[randIndex].getType() << endl;
	hand.addCardToHand(this->cardsInDeck[randIndex]); //adds cards to the hand vector
	
	//cout << "size of cardsInHand: " << hand.getCardsInHand().size() << endl;
	this->cardsInDeck.erase(this->cardsInDeck.begin() + randIndex); //erase the card from deck
	//cout << "size of deck: " << this->cardsInDeck.size() << endl;

}

/*Initializes the cards in the Deck for the game*/
void Deck::addCardsInDeck(int numOfCountries) {
	unsigned seed = time(0);
	srand(seed);

	

	this->cardsInDeck.resize(numOfCountries);

	for (int i = 0; i < numOfCountries; i++) {
		
		this->cardsInDeck[i] = rand() % 3 + 1; //randomValue ranges from 1 to 3, Artillery(1),Cavarly(2) and Infantry(3)
	}
	
}

/*FINISH FOR EQUAL SHARE OF CARDS IN DECK*/
void Deck::addEqualCardsInDeck(int numOfCountries) {
	this->cardsInDeck.resize(numOfCountries);

}

void Deck::printAllCardsInDeck(vector<Card> cardsInDeck) {
	for (int i = 0; i < cardsInDeck.size(); i++) {
		cout << "card [ " << i << " ] : " << cardsInDeck[i].cardType(cardsInDeck.at(i)) << endl;
	}
}



/*
Deck::Deck(int nbCountries) {

	deck.resize(nbCountries);
	for (int i = 0; i < nbCountries / 3; i++) {
		deck[i] = 1;
	}
	for (int i = nbCountries / 3; i < nbCountries / 3 * 2; i++) {
		deck[i] = 2;
	}
	for (int i = nbCountries / 3 * 2; i < nbCountries; i++) {
		deck[i] = 3;
	}

}


void Deck::draw(vector<int>& hand) {

	int randIndex = rand() % deck.size();
	hand.push_back(deck[randIndex]);
	deck.erase(deck.begin() + randIndex);


}

*/