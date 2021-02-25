#pragma once
/*
 * Deck.h
 *
 *  Created on: Oct. 2, 2018
 *      Author: Jonathan Frey
 */

#ifndef DECK_H_
#define DECK_H_

#include<iostream>
#include<vector>
#include "Card.h"
#include "Hand.h"

using namespace std;

//DONE

class Deck {

public:
	//Constructor
	Deck();
	Deck(int numOfCountries);

	//Accessor
	vector<Card> getCardsInDeck();
	vector<Hand> getHands();

	//Mutator
	void setCardsInDeck(vector<Card> cards);
	void setHands(vector<Hand> hands);

	//Other methods
	void draw(Hand &h);
	void addCardsInDeck(int numOfCountries);
	void addEqualCardsInDeck(int numOfCountries);
	void printAllCardsInDeck(vector<Card> cardsInDeck);

	friend class StartupPhase;
	
//private:
	//Attributes
	vector<Card> cardsInDeck;
	vector<Hand> hands;

};


#endif /* DECK_H_ */