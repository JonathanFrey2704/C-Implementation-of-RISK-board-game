/*
 * reinforce.cpp
 *
 *  Created on: Oct. 30, 2018
 *      Author: jonathan
 */
#include "reinforce.h"

Reinforce::Reinforce(Player player, Map* map) {

	int nbCountriesArmies = 0, continentArmies = 0, cardsArmies = 0;

	//get number of countries owned by player then find resulting armies given

	int nbCountries = player.getOwnedCountries().size();
	if (nbCountries > 11)
		nbCountriesArmies = nbCountries / 3;
	else
		nbCountriesArmies = 3;

	//get owned countries, check if player owns one or more continents and return corresponding continent value

	vector<Country*> playerCountries = player.getOwnedCountries();
	string continentName, continentName2;
	int nbCountriesInContinent;
	int counter;
	
	
	for (unsigned i = 0; i < playerCountries.size(); i++) {

		continentName = playerCountries[i]->getContinentName();
		nbCountriesInContinent = +map->getContinentByName(continentName)->getContainedCountriesInContinent().size();
		counter = 1;

		for (unsigned e = i + 1; e < playerCountries.size(); e++) {

			continentName2 = playerCountries[e]->getContinentName();
			if (continentName == continentName2)
				counter++;
		}
		if (counter == nbCountriesInContinent)
			continentArmies += map->getContinentByName(continentName)->getContinentValue();
	}

	// trade cards for armies if necessary or if player desires to
	
	if (player.getHand().getCardsInHand().size() >= 5)
		cardsArmies = player.getHand().exchange(); ///change
	else if(player.getHand().getCardsInHand().size() <3){
		cout << "Not enough cards to exchange! " << endl;
	}
	else {
		int answer;
		cout << "Do you want to exchange your cards? Enter 1 for yes and 0 for no" << endl;
		cin >> answer;
		if (answer == 1) {
			cardsArmies = player.getHand().exchange();//change
			cout << "inside else statement for 3 cards in hand " << endl;
		}
	}

	//result

	A = nbCountriesArmies + continentArmies + cardsArmies;
	cout << "Armies given for the number of countries: " << nbCountriesArmies << endl
		<< "Armies given for the possession of a continent " << continentArmies << endl
		<< "Armies given for the exchange of cards: " << cardsArmies << endl
		<< "Total armies given: " << A << endl;



	//place armies in countries
	int nbArmies;
	int remainingArmies = A;
	for (unsigned i = 0; i < player.getOwnedCountries().size(); i++) {

		cout << "For country: " << player.getOwnedCountries()[i]->getCountryName() << " enter number of armies you want to add:" << endl;
		cin >> nbArmies;
		if (nbArmies <= remainingArmies && nbArmies > 0) {
			player.getOwnedCountries()[i]->addArmies(nbArmies);
			remainingArmies -= nbArmies;
			cout << "You now have " << player.getOwnedCountries()[i]->getNumOfArmies() << " armies on " << player.getOwnedCountries()[i]->getCountryName() << endl;
		}
		else {
			cout << "Invalid entry. Try again.";
			i--;
		}

		if (remainingArmies == 0) {
			cout << endl << "You have no more armies to place" << endl;
			break;
		}
		if (i == player.getOwnedCountries().size() - 1 && remainingArmies != 0) {
			player.getOwnedCountries()[i]->addArmies(remainingArmies);
			cout << "Your remaining armies have been placed on: " << player.getOwnedCountries()[i]->getCountryName() << endl;
			cout << "You now have " << player.getOwnedCountries()[i]->getNumOfArmies() << " armies on " << player.getOwnedCountries()[i]->getCountryName() << endl;

		}

	}


}




