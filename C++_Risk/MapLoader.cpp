#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "MapLoader.h"
#include <algorithm>
using namespace std;

MapLoader::MapLoader() {

}

MapLoader::MapLoader(std::string fileDirectory) {
	ifstream inputfilestream;
	inputfilestream.open(fileDirectory);

	string line;

	bool hasTerritories = false;
	bool hasMap = false;
	bool hasContinents = false;
	int lineV = 0;
	
	
	map = new Map();

	while (getline(inputfilestream, line)) {
		
		


		//if [continent] header is found, line is not empty, [Territories] header is not found 
		if (hasContinents && !line.empty() && !hasTerritories) {

			//Enters the below if statement after all continents are created
			if (line.find("[Territories]") != string::npos) {//string::npos indicates no match type as it is static member which holds a value of -1
				
				hasTerritories = true;
				continue;//forces the next iteration to occur instead of terminating
			}
			Continent* continent = new Continent(); //new continent created
			stringstream ss(line);
			string word;
			vector<string> lineVector; //holds continent name at index=0 and continent value at index=1

			while (getline(ss, word, '=')) {
				lineVector.push_back(word);
			}

			continent->setContinentName(lineVector.at(0));
			continent->setContinentValue(stoi(lineVector.at(1))); //stoi refers to string to integer conversion
			map->setContainedContinentInMap(continent);

		}

		//if the [Territory] header is found and line is not empty, start reading//  
		if (hasTerritories && !line.empty()) {

			

			//create a country based on the information provided by the line
			Country* territory = new Country();
			stringstream ss(line);
			string word;
			/*
			lineVector holds 4 values
			countryname at index=0
			coordinateX at index=1
			coordinateY at index=2
			continentOfContinent at index=3
			*/
			vector<string> lineVector;
			//store each read word in the line into a vector
			while (getline(ss, word, ',')) {
				lineVector.push_back(word);
			}
			//set Country's member values based on the words that are read
			if (!map->containsCountry(lineVector.at(0))) {

				territory->setCountryName(lineVector.at(0));
				territory->setCoordinateX(stoi(lineVector.at(1))); //converting X string to an integer value
				territory->setCoordinateY(stoi(lineVector.at(2))); //converting Y string to an integer value
				territory->setContinentName(lineVector.at(3)); //setting the countries continent name
				
				//Storing country contained in the given continent
				map->getContinentByName(lineVector.at(3))->setContainedCountriesInContinent(territory);
				
				//Storing country contained in the given map
				map->setContainedCountryInMap(territory); 
			}
			else {
				std::cout << "Error: Duplicate country.";
				system("pause"); //only for demo!
				exit(0);
			}
		}


		//Checks for [Map],[Continent] and [Territories] headers to validate map
		//cout << "Entered into No condition" << endl;
		if (line.find("[Map]") != string::npos) { //find returns The position of the first character of the first match.
			
			hasMap = true;
		}
		if (line.find("[Continents]") != string::npos) {
			hasContinents = true;

		}
	
	}//end of while loop

	//Setting neighboring countries and neighboring continents
	hasTerritories = false;
	inputfilestream.clear(); //clear fail and error of bits
	inputfilestream.seekg(0, std::ios::beg); //back to the start
	while (getline(inputfilestream, line)) {
		
		//if the [Territory] header is found, start reading
		if (hasTerritories && !line.empty()) {
			stringstream ss(line);
			string word;
			vector<string> lineVector;
			//store each read word in the line into a vector
			while (getline(ss, word, ',')) {
				lineVector.push_back(word);
			}

			Country* territory = map->getCountryByName(lineVector.at(0));//holds the i-th country
			//Adding all neighboring countries to country starting at index=4
			for (unsigned int i = 4; i < lineVector.size(); i++) {
				territory->setNeighboringCountry(map->getCountryByName(lineVector.at(i)));
			}
			for (unsigned int i = 0; i < map->getContainedCountryInMap().size(); i++) {
				for (unsigned int j = 0; j < territory->getNeighboringCountries().size(); j++) {
					// stores the continent of the given territory
					Continent* currentCont = map->getContinentByName(territory->getContinentName());
					
					//stores the neighboring continent of the neighboring territory
					Continent* neighborCont = map->getContinentByName(territory->getNeighboringCountries().at(j)->getContinentName());
					
					//if territory's continent is not the same as territory's neighboring territory continent, then add the neighboring continent to the vector
					if (territory->getContinentName().compare(territory->getNeighboringCountries().at(j)->getContinentName()) != 0) {
						currentCont->setNeighboringContinents(neighborCont);
						//cout << currentCont->getNameOfContinent() << " is neighbors with " << neighborCont->getNameOfContinent() << endl;
					}
				}
			}

			// Only For DEMO
			/*
			std::cout << "Country name is: " << territory->getCountryName() << endl;
			std::cout << "X: " << territory->getCoordinateX() << " Y: " << territory->getCoordinateY() << endl;
			std::cout << "Continent: " << territory->getContinentName() << endl;
			std::cout << "Neighbors: ";
			*/
			for (unsigned i = 0; i<territory->getNeighboringCountries().size(); i++) {
				//ONLY FOR DEMO!
				//std::cout << territory->getNeighboringCountries().at(i)->getCountryName() << " ";
			}
			//std::cout << endl;
			
		}

		if (line.find("[Territories]") != string::npos && hasMap && hasContinents) {
			hasTerritories = true;

		}
	}//end of while loop

	//If no checks are passed, map is invalid.
	if (!hasMap || !hasContinents || !hasTerritories) {
		std::cout << "Invalid map.";
		//exit(0); will be commented out for DEMO
	}

	//Map is valid, printing info
	//Check for number of countries
		//std::cout << "Number of countries loaded: " << map->getContainedCountryInMap().size() << endl;
	
	//Check neighbors to check graph connectivity
	//map->getContainedCountryInMap().at(0)->visitCountry(*map);
	
		//cout << "Is map fully Connected? :"<<map->isMapFullyConnected()<<endl;
	
	this->map = map;

}

//Accessor
Map* MapLoader::getMap() {
	return map;
}

//Mutator 
