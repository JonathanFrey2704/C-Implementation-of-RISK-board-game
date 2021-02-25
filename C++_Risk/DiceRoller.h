#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Dice.h"
using namespace std;

class DiceFacility
{
public:
	//Constructors
	DiceFacility();

	//Accessors
	vector<Dice> getDices();
	vector<int> getDiceRolledValues();

	vector<int> getNumOfTimesRolled();
	vector<float> getPercentRolled();

	int getNumOfDiceToBeRolled();
	


	//Mutators
	void setDices(vector<Dice> dices);
	void setNumOfDiceToBeRolled(int numOfDice);
	void setDiceRolledValues(vector<int> diceRolledValues);
	
	void setNumOfTimesRolled(vector<int> numTimesRolled);
	void setPercentRolled(vector<float> percentRolled);

	//Other methods
	void sortMax(vector<int> diceRolledValues);
	void roll(int numOfDiceToBeRolled);
	vector<int> roll(int numArmies, string type);
	void diceRollStats();

	/*
	void roll();
	void numRolls();
	*/
private:
	//Attributes
	vector<Dice> dices;
	vector<int> diceRolledValues;
	vector<float> percentRolled;
	vector<int> numTimesRolled;

	int numOfDiceToBeRolled;
	int totalRolls = 0;

	
	/*
	int numTimesRolled[6] = {};
	int diceRolled[3];
	int totalRolls = 0;
	float percentRolled[6] = {};
	*/
};