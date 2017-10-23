// Poker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <functional>
#include <iostream>
#include <algorithm>
#include <string>
#include "Poker.h"

int main()
{
	int i;
	PokerHand* player1 = new PokerHand("Charlie");
	PokerHand* player2 = new PokerHand("Ed");
	PokerHand* player3 = new PokerHand("Steve");

	std::vector<PokerHand> allHands;
	player1->addCard(*(new Card('c', 13)));
	player1->addCard(*(new Card('c', 12)));
	player1->addCard(*(new Card('c', 11)));
	player1->addCard(*(new Card('c', 10)));
	player1->addCard(*(new Card('c', 9)));
	player2->addCard(*(new Card('s', 2)));
	player2->addCard(*(new Card('s', 3)));
	player2->addCard(*(new Card('s', 4)));
	player2->addCard(*(new Card('s', 5)));
	player2->addCard(*(new Card('s', 6)));
	player3->addCard(*(new Card('c', 1)));
	player3->addCard(*(new Card('s', 12)));
	player3->addCard(*(new Card('d', 11)));
	player3->addCard(*(new Card('h', 1)));
	player3->addCard(*(new Card('c', 9)));
	allHands.push_back(*player1);
	allHands.push_back(*player2);
	allHands.push_back(*player3);
	sort(allHands.begin(), allHands.end(), PokerHand::compare);
	for (PokerHand H : allHands) {
		std::cout << H.getLabel() << " has ";
		H.showHand();
		std::cout << "\n";
	}
	
	std::cin >> i;
    return 0;
}

Card::Card(char suit, int value) {
	this->suit = suit;
	this->value = value;
}
int Card::getValue() {
	return this->value;
}
char Card::getSuit() {
	return this->suit;
}
void Card::show() {
	std::cout << suit << value << " ";
}
bool Card::compare(Card a, Card b) {
	return a.getValue() < b.getValue();
}



PokerHand::PokerHand(std::string name) {
	this->label = name;
	this->hand = {};
}
std::string PokerHand::getLabel() {
	return label;
}
void PokerHand::addCard(Card c) {
	this->hand.push_back(c);
}
void PokerHand::showHand() {
	for (auto c : hand) {
		c.show();
	}
}
float PokerHand::getValue() {
	//Singles	0-1
	//Doubles	1-2
	//TwoPairs  2-3
	//Triples	3-4
	//Straight	4-5
	//Flush		5-6
	//FullHouse 6-7
	//Quad		7-8
	//SFlush	8-9
	// Only give a value for 5 cards
	if (hand.size() != 5) { return 0; }
	sort(hand.begin(), hand.end(), Card::compare);

	float val;
	int longest = longestSingle();
	if (longest == 1) {
		val = isStraightFlush();
		if (val) return val;
		val = isFlush();
		if (val) return val;
		val = isStraight();
		if (val) return val;
		return isSingle();
	} else if (longest == 2) {
		val = isTwoPair();
		if (val) return val;
		return isPair();
	} else if (longest == 3) {
		val = isFullHouse();
		if (val) return val;
		return isTriple();
	} else {
		return isQuad();
	}
	return 0;
}

bool PokerHand::compare(PokerHand a, PokerHand b) {
	return a.getValue() < b.getValue();
}

float PokerHand::isSingle() {
	float total = 0;
	for (int i = 0; i < hand.size(); i++) {
		total += (hand[i].getValue()-1) * pow(1.0 / 13, hand.size() - i);
	}
	return total;
}

float PokerHand::isPair() {
	if (hand[0].getValue() == hand[1].getValue())
		return 1 + (hand[0].getValue() - 1) * (1.0 / 13) + (hand[4].getValue() - 1) * pow(1.0 / 13, 2) +
		(hand[3].getValue() - 1) * pow(1.0 / 13, 3) + (hand[2].getValue() - 1) * pow(1.0 / 13, 4);
	if (hand[1].getValue() == hand[2].getValue())
		return 1 + (hand[1].getValue() - 1) * (1.0 / 13) + (hand[4].getValue() - 1) * pow(1.0 / 13, 2) +
		(hand[3].getValue() - 1) * pow(1.0 / 13, 3) + (hand[0].getValue() - 1) * pow(1.0 / 13, 4);
	if (hand[2].getValue() == hand[3].getValue())
		return 1 + (hand[2].getValue() - 1) * (1.0 / 13) + (hand[4].getValue() - 1) * pow(1.0 / 13, 2) +
		(hand[1].getValue() - 1) * pow(1.0 / 13, 3) + (hand[0].getValue() - 1) * pow(1.0 / 13, 4);
	if (hand[3].getValue() == hand[4].getValue())
		return 1 + (hand[3].getValue() - 1) * (1.0 / 13) + (hand[2].getValue() - 1) * pow(1.0 / 13, 2) +
		(hand[1].getValue() - 1) * pow(1.0 / 13, 3) + (hand[0].getValue() - 1) * pow(1.0 / 13, 4);
	return 0;
}

float PokerHand::isTwoPair() {
	if (hand[0].getValue() == hand[1].getValue() && hand[2].getValue() == hand[3].getValue()) {
		return 2 + hand[2].getValue() * (1.0 / 13) + hand[0].getValue() * pow(1.0 / 13, 2) + hand[4].getValue() * pow(1.0 / 13, 3);
	} else if (hand[0].getValue() == hand[1].getValue() && hand[3].getValue() == hand[4].getValue()) {
		return 2 + hand[3].getValue() * (1.0 / 13) + hand[0].getValue() * pow(1.0 / 13, 2) + hand[2].getValue() * pow(1.0 / 13, 3);
	} else if (hand[1].getValue() == hand[2].getValue() && hand[3].getValue() == hand[4].getValue()) {
		return 2 + hand[3].getValue() * (1.0 / 13) + hand[1].getValue() * pow(1.0 / 13, 2) + hand[0].getValue() * pow(1.0 / 13, 3);
	}
	return 0;
}

float PokerHand::isTriple() {
	// Incorporate the singles
	if (hand[0].getValue() == hand[1].getValue() && hand[1].getValue() == hand[2].getValue()) {
		return 3 + hand[0].getValue() * (1.0 / 13) + hand[4].getValue() * pow(1.0 / 13, 2);
	} else if (hand[1].getValue() == hand[2].getValue() && hand[1].getValue() == hand[3].getValue()) {
		return 3 + hand[1].getValue() * (1.0 / 13) + hand[4].getValue() * pow(1.0 / 13, 2);
	} else {
		return 3 + hand[2].getValue() * (1.0 / 13) + hand[1].getValue() * pow(1.0 / 13, 2);
	}
	return 0;
}

int PokerHand::longestSingle() {
	int longest = 0;
	int cur = 0;
	for (int i = 1; i < hand.size(); i++) {
		if (hand[i].getValue() == hand[i - 1].getValue())
			cur++;
		longest = cur > longest ? cur : longest;
	}
	return longest + 1;
}

float PokerHand::isFullHouse() {
	if (hand.size() == 5 && (hand[0].getValue() == hand[1].getValue() &&
		hand[2].getValue() == hand[3].getValue() && hand[3].getValue() == hand[4].getValue()) ||
		(hand[0].getValue() == hand[1].getValue() && hand[1].getValue() == hand[2].getValue() &&
			hand[3].getValue() == hand[4].getValue())) {
		int triple;
		int pair;
		if (hand[1].getValue() == hand[2].getValue()) {
			triple = hand[1].getValue();
			pair = hand[3].getValue();
		} else {
			triple = hand[3].getValue();
			pair = hand[1].getValue();
		}
		return 6 + (triple - 1) * (1.0 / 13) + (pair - 1) * pow(1.0 / 13, 2);
	}
	return 0;
}

float PokerHand::isQuad() {
	if (hand.size() == 5 && (hand[0].getValue() == hand[1].getValue() &&
		hand[1].getValue() == hand[2].getValue() && hand[2].getValue() == hand[3].getValue()) ||
		(hand[1].getValue() == hand[2].getValue() && hand[2].getValue() == hand[3].getValue() &&
			hand[3].getValue() == hand[4].getValue())) {
		int quad;
		int kicker;
		if (hand[0].getValue() == hand[1].getValue()) {
			quad = hand[0].getValue();
			kicker = hand[4].getValue();
		} else {
			quad = hand[4].getValue();
			kicker = hand[0].getValue();
		}
		return 7 + (quad - 1)*(1.0 / 13) + (kicker - 1) * pow(1.0 / 13, 2);
	} 
	return 0;
}

float PokerHand::isStraightFlush() {
	if (isStraight() && isFlush()) {
		return 4 + isStraight();
	}
}

float PokerHand::isStraight() {
	if (hand.size() == 5 && (hand[0].getValue() == hand[1].getValue() - 1) &&
		(hand[1].getValue() == hand[2].getValue() - 1) && (hand[2].getValue() == hand[3].getValue() - 1) &&
		(hand[3].getValue() == hand[4].getValue() - 1)) {
		return 4 + 0.1 * hand[0].getValue();
	}
}
float PokerHand::isFlush() {
	if (hand.size() == 5 && (hand[0].getSuit() == hand[1].getSuit()) &&
		(hand[1].getSuit() == hand[2].getSuit()) && (hand[2].getSuit() == hand[3].getSuit()) &&
		(hand[3].getSuit() == hand[4].getSuit())) {
		return 5 + 0.1 * (hand[4].getValue() - 4);
	}
}