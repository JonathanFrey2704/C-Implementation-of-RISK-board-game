#include "Player.h"
#include "Fortify.h"
#include <iostream>
using namespace std;

//Constructor
Fortify::Fortify(Player player) {
	cout << "**********************************" << endl;
	cout << "FORTIFICATION PHASE..............." << endl;
	cout << "**********************************" << endl;
	cout << "Player owner number: " << player.getOwnerNum() << endl;
	int numOfCountriesOwned = player.getOwnedCountries().size();
	
	int numOfArmiesToMove;
	int x=0;
	int sourceChoice,targetChoice;
	int sourceArmies;
	for (int i = 0; i < numOfCountriesOwned; i++) {
		
		cout << "Is [ " << player.getOwnedCountries()[i]->getCountryName() << " ] the source country (yes=1 & no=0)? " << endl;
		cin >> sourceChoice;
		cout << "sourceChoice: " << sourceChoice << endl;
		
		for (unsigned j = 0; j < player.getOwnedCountries()[i]->getNeighboringCountries().size(); j++) {
			
			if (sourceChoice == 1 && player.getOwnedCountries()[i]->getNeighboringCountries()[j]->getOwnerNumber()==player.getOwnerNum()) {
				x = (player.getOwnedCountries()[i]->getNumOfArmies() - 1);
				numOfArmiesToMove = player.getOwnedCountries()[i]->getNumOfArmies();
				if (numOfArmiesToMove == 1) {
					cout << "|-----------------------------------------------------------------|" << endl;
					cout << "numOfArmiesToMove is: " << numOfArmiesToMove <<" cannot moved! " <<endl;
					cout << "|-----------------------------------------------------------------|" << endl;
					break;
				}
				cout << "x= " << x << endl;
				cout << "numOfArmiesToMove= " << numOfArmiesToMove << endl;
				cout << "\n" << endl;

				cout << "Is [ " << player.getOwnedCountries()[i]->getNeighboringCountries()[j]->getCountryName() << " ] the target country (yes=1 & no=0)? " << endl;
				cin >> targetChoice;
				cout << "targetChoice: " << targetChoice<<endl;
				if (targetChoice == 1) {

					if (numOfArmiesToMove >= 1 || numOfArmiesToMove < x) {
						cout << "Total number of armies that can be moved: " << x << endl;
						cin >> sourceArmies;
						cout << "sourceArmies: " << sourceArmies<< endl;
						
						while (sourceArmies < 1 || sourceArmies >= numOfArmiesToMove) {
							cout << "Please enter a valid number of armies to be moved: " << endl;
							cin >> sourceArmies;
							cout << "sourceArmies: " << sourceArmies << endl;
						}
						
						cout << "------------------------------------------------------------------------------------------------" << endl;
						cout << "Source country [ " << player.getOwnedCountries()[i]->getCountryName() << " ] has numOfArmies= " << player.getOwnedCountries()[i]->getNumOfArmies() << endl;
						cout << "Target country [ " << player.getOwnedCountries()[i]->getNeighboringCountries()[j]->getCountryName() << " ] has numOfArmies= " << player.getOwnedCountries()[i]->getNeighboringCountries()[j]->getNumOfArmies() << endl;
						cout << "------------------------------------------------------------------------------------------------" << endl;
						cout << "\n" << endl;

						cout << "Now moving " << sourceArmies << " armies from source to target country......." << endl;
						cout << "------------------------------------------------------------------------------------------------" << endl;
						player.getOwnedCountries()[i]->setNumOfArmies(player.getOwnedCountries()[i]->getNumOfArmies()- sourceArmies);
						player.getOwnedCountries()[i]->getNeighboringCountries()[j]->setNumOfArmies(player.getOwnedCountries()[i]->getNeighboringCountries()[j]->getNumOfArmies() + sourceArmies);

						cout << "Source country [ " << player.getOwnedCountries()[i]->getCountryName() << " ] has numOfArmies= " << player.getOwnedCountries()[i]->getNumOfArmies() << endl;
						cout << "Target country [ " << player.getOwnedCountries()[i]->getNeighboringCountries()[j]->getCountryName() << " ] has numOfArmies= " << player.getOwnedCountries()[i]->getNeighboringCountries()[j]->getNumOfArmies() << endl;
						cout << "------------------------------------------------------------------------------------------------" << endl;
						cout << "FORTIFICATION PHASE COMPLETE..............." << endl;
						cout << "\n" << endl;
						return;
					}
					else {
						cout << "Total number of armies: " << numOfArmiesToMove << endl;
						cout << "No armies to be moved!: "<< endl;
						break;
					}
				}
				else {
					cout << "Next possible neighboring country " << endl;
					continue;
				}
				
			}
			else {
				cout << "Next possible source country " << endl;
				break;
			}

		}
	}
}