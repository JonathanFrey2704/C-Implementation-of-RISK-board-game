#pragma once
#include <string>
using namespace std;
//DONE
class Card{
public:
	//Constructor
	Card();
	Card(int type);
	

	//Accessor
	int getType();

	//Mutator
	void setType(int type);

	//Other methods
	int cardType(Card c);
	bool isCardInfantry(Card c);
	bool isCardArtillery(Card c);
	bool isCardCavarly(Card c);
	string cardTypeName(int type);

	
//private:
	//Attributes
	int type;
	
	// artillery=1;
	// cavarly=2;
	// infantry=3;

};