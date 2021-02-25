#pragma once
#include<iostream>

#include "Hand.h"
#include "DiceRoller.h"
#include "Map.h"
class Country;
class Map;
class Continent;

#include <vector>


using namespace std;
//using std::vector;




class Player {
public:
	//Constructor
	Player();
	Player(int ownerId);

	//Accessor
	int getOwnerNum();

	vector< Country* > getOwnedCountries();

	DiceFacility& getDiceFacility();

	Hand getHand();
	int getNumOfArmies();
	
		
	//Mutator
	void setOwnerNum(int ownerNum);
	void setOwnedCountry(Country* country);
	

	void setDiceFacility(DiceFacility df);

	void setHand(Hand hand);

	void setNumOfArmies(int numOfArmies);


	//Other methods
	void printPlayerOwnedCountries();




	/*
		Hand object;
		DiceFacility object1;
	*/
		void fortify();
		void attack();
		void reinforce();
		
		void attack1(); //dummy attack
		//ATTACK PHASE METHODS
		void removeCountry(Country country);//Removes the country from ownedCountries
		void printPlayerOwnedCountries2();

		
		
//private:
	//Attributes
	vector<Country*> ownedCountries;
	int ownerNum;
	DiceFacility df;
	Hand hand;
	int numOfArmies;
	int null = -1;

	

	//Attack phase members
	Country *defendingCountry;
	Country *attackingCountry;

	Player *attacker;
	Player *defender;
	vector<Country*> canAttack;
	vector<Country*> canAttackFrom;
	

	
	void compare(vector<int> att, vector<int> def);
	void conquer();
	
};
