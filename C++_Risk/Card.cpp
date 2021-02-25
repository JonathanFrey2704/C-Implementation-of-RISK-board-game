#include "Card.h"
#include <string>
using namespace std;

//DONE

//Constructor
Card::Card() {

}

Card::Card(int type) {
	this->type = type;

}



//Accessor

int Card::getType() {
	return this->type;
}

//Mutator

void Card::setType(int type) {
	this->type = type;
}

//Other methods
int Card::cardType(Card c) {
	return c.getType();
}

bool Card::isCardInfantry(Card c) {
	if (c.getType() == 3) {
		return true;
	}
	else {
		return false;
	}
}

bool Card::isCardArtillery(Card c) {
	if (c.getType() == 1) {
		return true;
	}
	else {
		return false;
	}
}

bool Card::isCardCavarly(Card c) {
	if (c.getType() == 2) {
		return true;
	}
	else {
		return false;
	}
}

string Card::cardTypeName(int type) {
	

	if (type == 1) {
		return "Artillery";
	}
	else if (type == 2) {
		return "Cavarly";
	}
	else if(type==3) {
		return "Infantry";
	}
	else {
		return "Empty";
	}
}