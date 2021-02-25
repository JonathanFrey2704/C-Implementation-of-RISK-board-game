
#include <iostream>
#include <ctime>
#include "DiceRoller.h"

using namespace std;
//Constructor
DiceFacility::DiceFacility() {
	this->dices.resize(3);//set the size of the dice vector to 3


	//3 Dices created and stored in the dices vector
	this->dices[0]= Dice();
	this->dices[1]= Dice();
	this->dices[2]= Dice();
}

//Accessor
vector<Dice> DiceFacility::getDices(){
	return this->dices;
}

vector<int> DiceFacility::getDiceRolledValues() {
	return this->diceRolledValues;
}

int DiceFacility::getNumOfDiceToBeRolled() {
	return this->numOfDiceToBeRolled;
}

vector<int> DiceFacility::getNumOfTimesRolled() {
	return this->numTimesRolled;
}

vector<float> DiceFacility::getPercentRolled() {
	return this->percentRolled;
}

//Mutator
void DiceFacility::setDices(vector<Dice> dices) {
	this->dices = dices;
}

void DiceFacility::setNumOfDiceToBeRolled(int numOfDice) {
	this->numOfDiceToBeRolled = numOfDice;
}

void DiceFacility::setDiceRolledValues(vector<int> diceRolledValues) {
	this->diceRolledValues = diceRolledValues;
}

void DiceFacility::setNumOfTimesRolled(vector<int> numOfTimesRolled) {
	this->numTimesRolled = numOfTimesRolled;
}

void DiceFacility::setPercentRolled(vector<float> percentRolled) {
	this->percentRolled = percentRolled;
}

//Other methods
void DiceFacility::sortMax(vector<int> diceRolledValues) {

	int tempValue;
	this->diceRolledValues = diceRolledValues;

	for (unsigned i = 0; i < this->diceRolledValues.size(); i++) {

		for (unsigned j = 0; j < this->diceRolledValues.size(); j++) {

			if (this->diceRolledValues[j] > this->diceRolledValues[i]) {
				tempValue = this->diceRolledValues[i];
				//swap values
				this->diceRolledValues[i] = this->diceRolledValues[j];
				this->diceRolledValues[j] = tempValue;
			}
		}
	}
}

void DiceFacility::roll(int numOfDiceToBeRolled) {

	for (int i = 0; i < numOfDiceToBeRolled; i++) {
		this->diceRolledValues[i] = this->dices[i].getDiceValue(); //storing dice values in another vector

		this->numTimesRolled[this->diceRolledValues[i] - 1]++; //value -1 to get the right index
	}

	//sortMax
	this->sortMax(this->diceRolledValues);
}

void DiceFacility::diceRollStats() {
	cout.setf(ios::fixed);cout.setf(ios::showpoint);cout.precision(2);

	if (this->totalRolls == 0) {
		for (unsigned i = 0; i < percentRolled.size(); i++) {
			
			cout << i + 1 << " was rolled " << percentRolled[i] << " percent of the time" << endl;
		}
	}
	else{
		for (unsigned i = 0; i < percentRolled.size(); i++) {
			this->percentRolled[i] = ((float)this->numTimesRolled[i] / this->totalRolls) * 100;
			cout << i + 1 << " was rolled " << percentRolled[i] << " percent of the time" << endl;
		}
	}
}




vector<int> DiceFacility::roll(int numArmies, string playerType)
{
	srand((int)time(0));

	//Variable declarations
	int numDice, rolled, temp;
	static int attackerDice;

	if (playerType == "attacker") {//If the attacker called his dice roll 
		cout << "ATTACKER" << endl;
		cout << "----------------------------------------------------------------------------" << endl;

		//Prompts the attacker to enter the number of dice to roll
		cout << "Enter the number of dice to roll [1-3]: ";
		cin >> numDice;

		while (numDice > 3 || numDice < 1)//Ensures that the number entered is not out of bounds
		{
			cout << "Invalid number of dice! Try again." << endl;
			cin >> numDice;
		}
		if (numDice > numArmies - 1) {//Ensures that the attacker doesn't use all of his armies
			cout << "You only have " << numArmies << " armies. Since you must keep one, " << numArmies - 1 << " dice will be rolled." << endl;
			numDice = numArmies - 1;
		}
		attackerDice = numDice;//Stores the number of dice that the attacker rolled
	}
	else if (playerType == "defender") {//If the defender called his dice roll
		cout << "DEFENDER" << endl;
		cout << "----------------------------------------------------------------------------" << endl;

		//Prompts the defender to enter the number of dice to roll
		cout << "Enter the number of dice to roll [1-2]: ";
		cin >> numDice;

		while (numDice > 2 || numDice < 1)//Ensures that the number entered is not out of bounds
		{
			cout << "Invalid number of dice! Try again." << endl;
			cin >> numDice;
		}

		if (numDice > numArmies) {//Ensures that the number of dice doesn't exceed the number of armies
			cout << "You only have 1 army. One die will be rolled instead." << endl;
			numDice = 1;
		}
		if (numDice > attackerDice)//Ensures that the defender doesn't roll more dice than the attacker
		{
			cout << "You cannot roll more dice than the attacker. " << attackerDice << " dice will be rolled instead." << endl;
			numDice = attackerDice;
		}
	}
	diceRolledValues.resize(numDice);
	numTimesRolled.resize(6);

	//Simulates the dice roll
	for (int i = 0; i < numDice; i++)
	{
		rolled = (rand() % 6) + 1;
		diceRolledValues[i] = rolled;
		numTimesRolled[rolled - 1] += 1;
		totalRolls += 1;
	}

	//Sorts the dice rolled in descending order
	for (int i = 0; i < numDice - 1; i++)
	{
		for (int j = 0; j < numDice - 1 - i; j++)
			if (diceRolledValues[j] < diceRolledValues[j + 1])
			{
				temp = diceRolledValues[j + 1];
				diceRolledValues[j + 1] = diceRolledValues[j];
				diceRolledValues[j] = temp;
			}
	}

	diceRollStats();
	//Displays the values of the dice rolled
	cout << "Values Rolled:";
	for (int i = 0; i < numDice; i++)
		cout << " " << diceRolledValues[i];
	cout << endl;
	cout << "----------------------------------------------------------------------------" << endl;
	return diceRolledValues;
}





/*
void DiceFacility::roll()
{
	srand((int)time(0));

	int numDice, rolled, temp;
	int diceRolled[3];

	cout << "Enter the number of dice to roll: ";
	cin >> numDice;

	while (numDice > 3 || numDice < 1)
	{
		cout << "Invalid number of dice! Try again.";
		cin >> numDice;
	}

	for (int i = 0; i < numDice; i++)
	{
		rolled = (rand() % 6) + 1;
		diceRolled[i] = rolled;
		numTimesRolled[rolled - 1] += 1;
		totalRolls += 1;
	}

	for (int i = 0; i < numDice - 1; i++)
	{
		for (int j = 0; j < numDice - 1 - i; j++)
			if (diceRolled[j] > diceRolled[j + 1])
			{
				temp = diceRolled[j + 1];
				diceRolled[j + 1] = diceRolled[j];
				diceRolled[j] = temp;
			}
	}
}
void DiceFacility::numRolls()
{
	cout.setf(ios::fixed);cout.setf(ios::showpoint);cout.precision(2);

	for (int i = 0; i < 6; i++)
	{
		percentRolled[i] = ((float)numTimesRolled[i] / totalRolls) * 100;
		cout << i + 1 << " was rolled " << percentRolled[i] << " percent of the time" << endl;
	}
}
*/ 
