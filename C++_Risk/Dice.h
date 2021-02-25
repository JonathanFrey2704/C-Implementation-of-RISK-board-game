#pragma once

#include <string>
#include <vector>
using namespace std;
class Dice {

public:
	//Constructor
	Dice();
	

	//Accessor
	int getDiceValue();
	vector<int> getDice();

	//Mutator
	void setDice(vector<int> dice);

	//Other methods

private:
	//Attributes
	vector<int> dice;

};