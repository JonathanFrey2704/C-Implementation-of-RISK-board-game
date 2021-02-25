#include "Dice.h"
#include <vector>
#include <string>
#include <ctime>
//Constructor
Dice::Dice() {
	 //sets the values for a dice
}

//Accessor
int Dice::getDiceValue() {
	unsigned seed = time(0);
	srand(seed);

	return rand() % 6 + 1;//random value from the range of 1 to 6 (inclusive)

}

vector<int> Dice::getDice() {
	return this->dice;
}

//Mutator
void Dice::setDice(vector<int> dice) {
	this->dice = dice;
}

//Other methods
