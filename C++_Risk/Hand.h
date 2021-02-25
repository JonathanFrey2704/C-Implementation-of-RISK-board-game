#pragma once
/*
 * Cards.h
 *
 *  Created on: Oct. 2, 2018
 *      Author: Jonathan Frey
 */

#ifndef HAND_H_
#define HAND_H_

#include <iostream>
#include <vector>

#include "Card.h"
using namespace std;

//DONE

class Hand {

public:
	//Constructor
	Hand();
	Hand(vector<Card> cardsInHand);
	
	//Accessor
	vector<Card> getCardsInHand();
	
	int getTimesExchanged();

	//Mutator
	void setCardsInHand(vector<Card> vc);
	
	void setTimeExchanged(int ex);

	//Other methods
	void addCardToHand(Card c);
	void printAllCardsInHand();
	int exchange();
	int exchange2();
	

	
	/*
	vector<int> hand;
	int exchange();
	int timesExchanged = 1;
	*/

	friend class StartupPhase;
	

//private: 
	//Attributes
	vector<Card> cardsInHand;
	
	int timesExchanged = 1;


};
#endif /* HAND_H_ */