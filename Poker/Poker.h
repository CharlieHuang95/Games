#pragma once
#include <vector>

class Card {
private:
	char suit;
	int value;
public:
	Card(char, int);
	int getValue();
	char getSuit();
	void show();
	static bool compare(const Card, const Card);
};

class PokerHand {
private:
	std::vector<Card> hand;
	std::string label;
	float isSingle();
	float isPair();
	float isTwoPair();
	float isTriple();
	float isFullHouse();
	float isQuad();
	float isStraightFlush();
	float isStraight();
	float isFlush();
public:
	PokerHand(std::string);
	std::string getLabel();
	void addCard(Card);
	void showHand();
	int longestSingle();
	float getValue();
	static bool compare(const PokerHand, const PokerHand);
};
