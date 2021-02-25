#include "Map.h"
#include <algorithm>
#include "Player.h"
/*Map implementation----------------------------------------------------------------------------------------*/

//Constructor
Map::Map() {

}

Map::Map(string mapName, vector<Country*> countryVector, vector<Continent*> continentVector) {

	this->mapName = mapName;
	this->containedCountriesInMap = countryVector;
	this->containedContinentsInMap = continentVector;
}
//Accessor

string Map::getMapName() {
	return this->mapName;
}
vector<Continent*> Map::getContainedContinentInMap() {
	return containedContinentsInMap;
}
vector<Country*> Map::getContainedCountryInMap() {
	return containedCountriesInMap;
}
Continent* Map::getContinentByName(string contName) {

	for (unsigned int i = 0; i < containedContinentsInMap.size(); i++) {
		if (containedContinentsInMap[i]->getContinentName() == contName) {
			return containedContinentsInMap[i]; //continent exists
		}
	}

	return NULL; //continent doesn't exist
}

Country* Map::getCountryByName(string cName) {

	for (unsigned int i = 0; i < containedCountriesInMap.size(); i++) {
		if (containedCountriesInMap[i]->getCountryName() == cName) {
			return containedCountriesInMap[i]; //country exists
		}
	}

	return NULL; //country doesn't exist
}

//Mutator

void Map::setMapName(string mapName) {
	this->mapName = mapName;
}

void Map::setContainedContinentInMap(Continent* continent) {
	containedContinentsInMap.push_back(continent);
}
void Map::setContainedCountryInMap(Country* country) {
	containedCountriesInMap.push_back(country);
}

//Other methods
bool Map::containsCountry(string countryName) {
	for (unsigned int i = 0; i < containedCountriesInMap.size(); i++) {
		if (containedCountriesInMap[i]->getCountryName() == countryName) {
			return true; //country is already in the map
		}
	}

	return false; //country is not in the map
}

void Map::DFSForCountries(Country* country, vector<Country*> &visited) { //&visited is a reference parameter which means values can be changed

	visited.push_back(country); //stores country to a new vector of pointers of type country

	for (unsigned int i = 0; i < country->getNeighboringCountries().size(); i++) {

		//end(visited) returns an iterators to one-past-the-end of the container. The element just before is then the last element in the vector.
		if (find(begin(visited), end(visited), country->getNeighboringCountries()[i]) == end(visited)) {//compared to end(visited) since there's only one country in the vector

			DFSForCountries(country->getNeighboringCountries()[i], visited); //traverse to the neighboring country
		}
	}
}

void Map::DFSForContinents(Continent* continent, vector<Continent*> &visited) {

	visited.push_back(continent);

	for (unsigned int i = 0; i < continent->getNeighboringContinents().size(); i++) {

		//end(visited) returns an iterators to one-past-the-end of the container. The element just before is then the last element in the vector.
		if (find(begin(visited), end(visited), continent->getNeighboringContinents()[i]) == end(visited)) {//compared to end(visited) since there's only one continent in the vector

			DFSForContinents(continent->getNeighboringContinents()[i], visited); //traverse to the neighboring continent
		}
	}



}

bool Map::isCountryInMultipleContinent() {

	//check the first continent
	for (unsigned int i = 0; i < containedContinentsInMap.size(); i++) {

		//check the next continent
		for (unsigned int j = i + 1; j < containedContinentsInMap.size(); j++) {

			//check the first continent's countries
			for (unsigned int k = 0; k < containedContinentsInMap[i]->getContainedCountriesInContinent().size(); k++) {

				//check the next continent's countries
				for (unsigned int l = 0; l < containedContinentsInMap[j]->getContainedCountriesInContinent().size(); l++) {

					if ((containedContinentsInMap[i]->getContainedCountriesInContinent()[k]->getCountryName()) == (containedContinentsInMap[j]->getContainedCountriesInContinent()[l]->getCountryName())) {

						return true; // a country is an present in two continents
					}
				}
			}


		}

	}

	return false;
}

bool Map::isMapFullyConnected() {

	//if map contains no continents or no countries
	if (containedContinentsInMap.size() == 0 || containedCountriesInMap.size() == 0) {
		return false;
	}

	vector<Country*> visitedCountries; //empty visitedCountries vector
	DFSForCountries(containedCountriesInMap[0], visitedCountries);

	vector<Continent*> visitedContinents; //empty visitedContinents vector
	DFSForContinents(containedContinentsInMap[0], visitedContinents);

	//If the size of visitedCountries and visitedContinents equal to their respective containedCountriesInMap and containedContinentsInMap sizes, 
	//then map is connected as every country and every continent is visited
	if (visitedCountries.size() == containedCountriesInMap.size() && visitedContinents.size() == containedContinentsInMap.size()) {
		return true;
	}
	else {
		return false;
	}
}

bool Map::isMapValid() {
	//Map is valid if a country is present in Only one continent and the map is connected
	return (!isCountryInMultipleContinent() && isMapFullyConnected());

}

/*Continent implementation----------------------------------------------------------------------------------------*/

//Constructor
Continent::Continent() {

}

Continent::Continent(string contName, int continentValue) {
	this->continentName = contName;
	this->continentValue = continentValue;
}


//Accessor
vector<Country*>   Continent::getContainedCountriesInContinent() {
	return containedCountriesInContinent;

}
string Continent::getContinentName() {
	return continentName;
}
int Continent::getContinentValue() {
	return continentValue;
}
vector<Continent*> Continent::getNeighboringContinents() {
	return neighboringContinents;
}

//Mutator
void Continent::setContainedCountriesInContinent(Country* country) {
	containedCountriesInContinent.push_back(country);
}
void Continent::setContinentName(string contName) {
	continentName = contName;
}
void Continent::setContinentValue(int contValue) {
	continentValue = contValue;
}
void Continent::setNeighboringContinents(Continent* continent) {
	neighboringContinents.push_back(continent);
}

//Other methods

/*Country implementation----------------------------------------------------------------------------------------*/

//Constructor
Country::Country() {
	this->numOfArimes = 0;
}
Country::Country(string ctryName) {
	countryName = ctryName;
	this->ownerNumber++; //increments for the next number to be held by another player

}

Country::Country(string countryName, int numOfArmies, int coordX, int coordY, string contName, int ownerNum) {
	this->countryName = countryName;
	this->numOfArimes = numOfArmies;
	this->coordinateX = coordX;
	this->coordinateY = coordY;
	this->continentName = contName;
	this->ownerNumber = ownerNum;

	
}



//Accessor
string Country::getContinentName() {
	return continentName;
}
int Country::getCoordinateX() {
	return coordinateX;
}
int Country::getCoordinateY() {
	return coordinateY;
}
string Country::getCountryName() {
	return countryName;
}
vector<Country*> Country::getNeighboringCountries() {
	return neighboringCountries;
}
int Country::getNumOfArmies() {
	return numOfArimes;
}
int Country::getOwnerNumber() {
	return ownerNumber;
}
bool Country::getVisited() {
	return visited;
}



//Mutator
void Country::setContinentName(string contName) {
	continentName = contName;
}
void Country::setCoordinateX(int x) {
	coordinateX = x;
}
void Country::setCoordinateY(int y) {
	coordinateY = y;
}
void Country::setCountryName(string ctryName) {
	countryName = ctryName;
}
void Country::setNeighboringCountry(Country* c) {
	neighboringCountries.push_back(c);
}
void Country::setNumOfArmies(int armies) {
	numOfArimes = armies;
}
void Country::setOwnerNumber(int num) {
	ownerNumber = num;
}
void Country::setVisited(bool v) {
	visited = v;
}



//Other methods
void Country::addArmies(int armies) {
	this->numOfArimes += armies;
}



//USED IN ATTACK PHASE
//Methods to get and set the player that owns the country
Player* Country::getPlayer()
{
	return owner;
}
void Country::setPlayer(Player *player)
{
	owner = player;
}


void Country::visitCountry(Map map) {
	static int visits = 0;

	for (unsigned int i = 0; i < this->getNeighboringCountries().size(); i++) {

		if (this->getNeighboringCountries().at(i)->getVisited() == false) {//false by default
			this->getNeighboringCountries().at(i)->setVisited(true);
			this->getNeighboringCountries().at(i)->visitCountry(map);
			visits++;

		}
	}

	if (visits == map.getContainedCountryInMap().size()) {
		cout << "Map connectivity validated." << endl;
	}
}

