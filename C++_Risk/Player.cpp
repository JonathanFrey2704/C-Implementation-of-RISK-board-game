#include "Player.h"

#include <vector>

//Constructor

Player::Player() {
	this->hand = Hand();
}
Player::Player(int ownerNum) {
	this->ownerNum = ownerNum;
}


//Accessor
int Player::getOwnerNum() {
	return ownerNum;
}

vector<Country*> Player::getOwnedCountries() {
	return ownedCountries;
}

DiceFacility& Player::getDiceFacility() {
	return this->df;
}


Hand Player::getHand() {
	
	return this->hand;
	
}



int Player::getNumOfArmies() {
	return this->numOfArmies;
}

//Mutator
void Player::setOwnerNum(int ownerNum) {
	this->ownerNum = ownerNum;
}
void Player::setOwnedCountry(Country* country) {
	this->ownedCountries.push_back(country);
}

void Player::setDiceFacility(DiceFacility df) {
	this->df = df;
}

void Player::setHand(Hand hand) {
	this->hand = hand;
}

void Player::setNumOfArmies(int numOfArmies) {
	this->numOfArmies = numOfArmies;
}

//Other methods

void Player::attack1()
{
	cout << "Attack Phase" << endl;
}
void Player::fortify() {

}
void Player::reinforce() {

}

void Player::printPlayerOwnedCountries() {
	for (unsigned i = 0; i < this->getOwnedCountries().size(); i++) {
		cout << "Player " << this->getOwnerNum() << " owns country: " << this->getOwnedCountries()[i]->getCountryName() <<" with numOfArmies: " << this->getOwnedCountries()[i]->getNumOfArmies() <<endl;
	}

	cout << "Player " << this->getOwnerNum() << " owns a total of : " << this->getOwnedCountries().size() << endl;

}



//====================================================================================================
//ATTACK PHASE METHODS
//====================================================================================================
void Player::attack() {
	//Variable declarations
	string confirm;
	int number = 1, numToAttack;
	vector<int> attDice, defDice;

	attacker = this;

	cout << "----------------------------------------------------------------------------" << endl;
	cout << "PLAYER " << attacker->getOwnerNum() << " ATTACK PHASE" << endl;
	cout << "----------------------------------------------------------------------------" << endl;

	//Prompts the user to see if they want to attack
	cout << "Do you want to attack someone? [y/n] ";
	cin >> confirm;

	while (confirm != "y" && confirm != "n")//Validates the user's response
	{
		cout << "That is not a valid response! Please try again." << endl;
		cin >> confirm;
	}

	while (confirm == "y")//Loops while the player wants to attack
	{
		//Variable declarations
		vector<Country*> myCountries = attacker->getOwnedCountries();
		vector<Country*> neighbors;

		//Displays the countries the user owns
		cout << "----------------------------------------------------------------------------" << endl;
		cout << "COUNTRIES YOU OWN" << endl;
		cout << "----------------------------------------------------------------------------" << endl;
		for (int i = 0; i < myCountries.size(); i++)
		{
			cout << number << ") " << myCountries[i]->getCountryName() << " [" << myCountries[i]->getNumOfArmies() << " armies]" << endl;
			number++;
		}
		//Displays the countries the user can attack from
		cout << "----------------------------------------------------------------------------" << endl;
		cout << "COUNTRIES YOU CAN ATTACK FROM" << endl;
		cout << "----------------------------------------------------------------------------" << endl;
		number = 1;
		for (int i = 0; i < myCountries.size(); i++)
		{
			if (myCountries[i]->getNumOfArmies() >= 2)//Checks if the country has enough armies to attack
			{
				neighbors = myCountries[i]->getNeighboringCountries();
				for (int j = 0; j < neighbors.size(); j++)//Checks if the country has at least 1 neighbor that can be attacked
				{
					//Make sure neighbor has armies and doesn't belong to the user
					if ((neighbors[j]->getNumOfArmies() > 0) && (neighbors[j]->getOwnerNumber() != attacker->getOwnerNum()))
					{
						canAttackFrom.push_back(myCountries[i]);
						cout << number << ") " << myCountries[i]->getCountryName() << " [" << myCountries[i]->getNumOfArmies() << " armies]" << endl;
						number++;
						break;
					}
				}
			}
		}

		if (canAttackFrom.size() == 0)//Exits if the player can't attack
		{
			cout << "You have no countries that you can attack from. Your turn will end now." << endl;
			return;
		}
		//Prompts the user for the country to attack from and validates their response
		cout << "\nEnter the number that is associated with the country you want to attack from: ";
		cin >> numToAttack;
		while (numToAttack > number - 1 || numToAttack < 1)
		{
			cout << "That is not a valid number! Try again." << endl;
			cin >> numToAttack;
		}

		attackingCountry = canAttackFrom[numToAttack - 1];
		neighbors = attackingCountry->getNeighboringCountries();

		//Displays the neighbors of the selected country that can be attacked
		cout << "----------------------------------------------------------------------------" << endl;
		cout << "From " << attackingCountry->getCountryName() << " you can attack the following countries: " << endl;

		number = 1;
		for (int i = 0; i < neighbors.size(); i++)
		{
			if ((neighbors[i]->getNumOfArmies() > 0) && (neighbors[i]->getOwnerNumber() != attacker->getOwnerNum()))
			{
				cout << number << ") " << neighbors[i]->getCountryName() << " [" << neighbors[i]->getNumOfArmies() << " armies]" << endl;
				canAttack.push_back(neighbors[i]);
				number++;
			}
		}

		//Prompts the user for the country to attack and validates their response
		cout << "\nEnter the number that is associated with the country you want to attack: ";
		cin >> numToAttack;
		while (numToAttack > number - 1 || numToAttack < 1)
		{
			cout << "That is not a valid number! Try again." << endl;
			cin >> numToAttack;
		}

		defendingCountry = canAttack[numToAttack - 1];
		defender = defendingCountry->getPlayer();//Gets the player that owns the defending country

		cout << "\nAttacking " << defendingCountry->getCountryName() << " from " << attackingCountry->getCountryName() << endl;
		cout << "----------------------------------------------------------------------------" << endl;
		cout << "DICE ROLLING" << endl;
		cout << "----------------------------------------------------------------------------" << endl;

		//Gets the dice that the attacker and defender rolled
		attDice = attacker->getDiceFacility().roll(attackingCountry->getNumOfArmies(), "attacker");
		defDice = defender->getDiceFacility().roll(defendingCountry->getNumOfArmies(), "defender");

		//Compares the dice rolled
		cout << "DICE COMPARING" << endl;
		cout << "----------------------------------------------------------------------------" << endl;
		compare(attDice, defDice);

		//Prompts the user to see if they want to attack
		cout << "Do you want to attack someone? [y/n] ";
		cin >> confirm;

		while (confirm != "y" && confirm != "n")//Validates the user's response
		{
			cout << "That is not a valid response! Please try again." << endl;
			cin >> confirm;
		}

		//Resets the variables
		canAttack.clear();
		canAttackFrom.clear();
		number = 1;
	}

	cout << "----------------------------------------------------------------------------" << endl;
	cout << "END OF TURN" << endl;
	cout << "----------------------------------------------------------------------------" << endl;
}
//removes a country from the player's owned countries
void Player::removeCountry(Country country)
{
	for (int i = 0; i < ownedCountries.size(); i++)
	{
		if (ownedCountries[i]->getCountryName() == country.getCountryName())
			ownedCountries.erase(ownedCountries.begin() + i);
	}
}
//Compares the values of the dice rolled and calls the conquer function to change ownership if the attack is successful 
void Player::compare(vector<int> attDice, vector<int> defDice)
{
	cout << "Player " << attacker->getOwnerNum() << "(Attacker) vs Player " << defender->getOwnerNum() << "(Defender) for " << defendingCountry->getCountryName() << endl;
	for (int i = 0; i < defDice.size(); i++)
	{
		//The attacker's die was higher than the defender's die
		if (attDice[i] > defDice[i]) {
			cout << "\n" << attDice[i] << " is greater than " << defDice[i] << endl;
			cout << "Player " << defender->getOwnerNum() << " loses an army!";

			defendingCountry->setNumOfArmies(defendingCountry->getNumOfArmies() - 1);
			cout << " He has " << defendingCountry->getNumOfArmies() << " armies left." << endl;

			if (defendingCountry->getNumOfArmies() == 0)//Checks if the defender ran out of armies and calls conquer
			{
				cout << "----------------------------------------------------------------------------" << endl;
				cout << "RESULT" << endl;
				cout << "----------------------------------------------------------------------------" << endl;
				cout << "Player " << defender->getOwnerNum() << " ran out of armies. " << defendingCountry->getCountryName() << " now belongs to Player " << attacker->getOwnerNum() << "!" << endl;
				conquer();
				return;
			}
		}
		//The attacker's die was lower than the defender's die
		else {
			cout << "\n" << attDice[i] << " is not greater than " << defDice[i] << endl;
			cout << "Player " << attacker->getOwnerNum() << " loses an army!";

			attackingCountry->setNumOfArmies(attackingCountry->getNumOfArmies() - 1);//Decreases the number of armies
			cout << " He has " << attackingCountry->getNumOfArmies() << " armies left." << endl;
		}
	}
	cout << "----------------------------------------------------------------------------" << endl;
	cout << "RESULT" << endl;
	cout << "----------------------------------------------------------------------------" << endl;
	cout << "Player " << defender->getOwnerNum() << " managed to defend " << defendingCountry->getCountryName() << "." << endl;
	cout << "----------------------------------------------------------------------------" << endl;
}
//Changes the ownership of a country and moves armies to it
void Player::conquer()
{
	cout << "----------------------------------------------------------------------------" << endl;
	cout << "MOVING ARMIES TO CONQUERED COUNTRY" << endl;
	cout << "----------------------------------------------------------------------------" << endl;

	int numToMove;
	//Prompts the user for the number of armies to move
	cout << "Select the number of armies [1 - " << attackingCountry->getNumOfArmies() - 1 << "] you want to move to " << defendingCountry->getCountryName() << ": " << endl;
	cin >> numToMove;

	//Validates the number of armies selected
	while (numToMove > attackingCountry->getNumOfArmies() - 1 || numToMove < 1)
	{
		cout << "Invalid number of armies! Try again." << endl;
		cout << "Select the number of armies [1 - " << attackingCountry->getNumOfArmies() - 1 << "] you want to move to " << defendingCountry->getCountryName() << ": ";
		cin >> numToMove;
	}

	cout << "You moved " << numToMove << " armies to " << defendingCountry->getCountryName() << " from " << attackingCountry->getCountryName() << "." << endl;
	cout << "----------------------------------------------------------------------------" << endl;

	//Displays the countries owned by the player before conquering
	cout << "COUNTRIES OWNED BY PLAYER " << attacker->getOwnerNum() << " BEFORE CONQUERING " << defendingCountry->getCountryName() << endl;
	cout << "----------------------------------------------------------------------------" << endl;
	attacker->printPlayerOwnedCountries2();

	//Changes ownership of the country
	attacker->setOwnedCountry(defendingCountry);
	defendingCountry->setOwnerNumber(attacker->getOwnerNum());
	defendingCountry->setPlayer(attacker);

	//Moves the selected number of armies
	defendingCountry->setNumOfArmies(numToMove);
	attackingCountry->setNumOfArmies(attackingCountry->getNumOfArmies() - numToMove);

	cout << "----------------------------------------------------------------------------" << endl;
	cout << "COUNTRIES OWNED BY PLAYER " << attacker->getOwnerNum() << " AFTER CONQUERING " << defendingCountry->getCountryName() << endl;
	cout << "----------------------------------------------------------------------------" << endl;
	attacker->printPlayerOwnedCountries2();

	//Displays the countries owned by the defender before and after being conquered
	cout << "----------------------------------------------------------------------------" << endl;
	cout << "COUNTRIES OWNED BY PLAYER " << defender->getOwnerNum() << " BEFORE LOSING " << defendingCountry->getCountryName() << endl;
	cout << "----------------------------------------------------------------------------" << endl;
	defender->printPlayerOwnedCountries2();

	defender->removeCountry(*defendingCountry);//Removes the conquered army from the defender's array

	cout << "----------------------------------------------------------------------------" << endl;
	cout << "COUNTRIES OWNED BY PLAYER " << defender->getOwnerNum() << " AFTER LOSING " << defendingCountry->getCountryName() << endl;
	cout << "----------------------------------------------------------------------------" << endl;
	defender->printPlayerOwnedCountries2();
	cout << "----------------------------------------------------------------------------" << endl;
}

//Displays all of the countries that the player owns
void Player::printPlayerOwnedCountries2() {
	for (int i = 0; i < this->getOwnedCountries().size(); i++) {
		cout << i + 1 << ") " << this->getOwnedCountries()[i]->getCountryName() << " with " << this->getOwnedCountries()[i]->getNumOfArmies() << " armies." << endl;
	}

	cout << "Player " << this->getOwnerNum() << " owns a total of : " << this->getOwnedCountries().size() << endl;

}
