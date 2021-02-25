#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Player.h"

class Player;
class Continent;
class Country;

using namespace std;

/*Map declaration----------------------------------------------------------------------------------------*/
class Map {
public:
	//Constructor
	Map();

	Map(string mapName, vector<Country*> countryVector, vector<Continent*> continentVector);
	
	//Accessor
	vector<Country*> getContainedCountryInMap();
	vector<Continent*> getContainedContinentInMap();
	string getMapName();

	//Mutator
	void setContainedContinentInMap(Continent* continent);
	void setContainedCountryInMap(Country* country);
	void setMapName(string mapName);


	//Other methods
	Country* getCountryByName(string countryName);
	Continent* getContinentByName(string contName);

	bool containsCountry(string countryName);
	bool isMapValid();
	bool isMapFullyConnected();

	

//private:

	//Attributes
	string mapName;
	vector<Continent*> containedContinentsInMap;
	vector<Country*> containedCountriesInMap;

	void DFSForCountries(Country* country, vector<Country*> &visited);
	void DFSForContinents(Continent* continent, vector<Continent*> &visited);
	bool isCountryInMultipleContinent();
};

/*Continent declaration----------------------------------------------------------------------------------------*/

class Continent {
public:
	//Constructor
	Continent();

	//Will be used for DEMO
	Continent(string contName, int continentValue);

	//Accessor
	string getContinentName();
	vector<Continent*> getNeighboringContinents();
	vector<Country*> getContainedCountriesInContinent();
	int getContinentValue();

	//Mutator
	void setContinentName(string contName);
	void setNeighboringContinents(Continent* continent);
	void setContainedCountriesInContinent(Country* country);
	void setContinentValue(int contValue);

	//Other methods
	friend Map;
private:
	//Attribute
	string continentName;
	vector<Continent*> neighboringContinents;
	vector<Country*> containedCountriesInContinent;
	int continentValue;
};


/*Country declaration----------------------------------------------------------------------------------------*/

class Country {
public:
	//Constructor
	Country();
	Country(string countryName);

	//Will be used for DEMO
	Country(string countryName, int numOfArmies, int coordX, int coordY, string contName, int ownerNum);

	//Accessor
	int getNumOfArmies();
	int getOwnerNumber();
	string getCountryName();
	string getContinentName();
	int getCoordinateX();
	int getCoordinateY();
	bool getVisited();
	vector<Country*> getNeighboringCountries();
	
	


	//Mutator
	void setNumOfArmies(int numOfArmies);
	void setOwnerNumber(int ownerNumber);
	void setCountryName(string countryName);
	void setContinentName(string continentName);
	void setCoordinateX(int coordinateX);
	void setCoordinateY(int coordinateY);
	void setNeighboringCountry(Country* country);
	void setVisited(bool v);
	

	
	//USED IN ATTACK PHASE
	//Setter and getter for the player that owns the country
	Player* getPlayer();
	void setPlayer(Player *player);
	

	//Other methods
	void visitCountry(Map m);
	void addArmies(int armies);

private:
	//Attributes
	int numOfArimes;
	int ownerNumber = 0;

	string countryName;
	string continentName;

	// neighboringCountries is a vector variable that holds pointers of type country
	//countries adjacent to the given country
	vector<Country*> neighboringCountries;

	int coordinateX;
	int coordinateY;

	bool visited;

	//USED IN ATTACK PHASE
	Player *owner;//Player that owns the country

};