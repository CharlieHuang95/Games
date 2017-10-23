// tictactoe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include "TicTacToe.h"
void playTicTacToe();

int main() {
	while (true) {
		playTicTacToe();
		std::cout << "Would you like to play again? (y/n)\n";
		char c;
		std::cin >> c;
		while (c != 'y' && c != 'n') {
			std::cout << "Please enter a valid value.\n";
			std::cin >> c;
		}
		if (c == 'n')
			break;
	}
	return 0;
}

void playTicTacToe()
{
	TicTacToe* Game = new TicTacToe();
	Game->drawBoard();
	do {
		Game->printTurn();
		if (Game->num_players == 1) {
			if (Game->first_player_turn) Game->humanMove();
			else Game->computerMove();
		} else
			Game->humanMove();
		Game->drawBoard();
		if (Game->hasWon()) {
			std::cout << "Winner is " << Game->hasWon() << "\n";
			break;
		}
	} while (true);
}


TicTacToe::TicTacToe()
{
	size = 0;
	first_player_turn = true;
	map = " XO";
	for (int i = 0; i < 9; i++)
		board[i] = 0;

	// Decide the number of human players
	std::cout << "How many players? (1 or 2)\n";
	std::cin >> num_players;
	while (num_players > 2 || num_players < 1) {
		std::cout << "Please enter a valid value.\n";
		std::cin >> num_players;
	}

	// Decide if human wants to do first
	if (num_players == 1) {
		char c;
		std::cout << "Would you like to go first? (y/n)\n";
		std::cin >> c;
		while (c != 'y' && c != 'n') {
			std::cout << "Please enter a valid value.\n";
			std::cin >> c;
		}
		if (c == 'n')
			first_player_turn = false;
	}
}

void TicTacToe::humanMove()
{
	std::cout << "Please enter a position (0-8)\n";
	int move;
	std::cin >> move;
	while (!isValid(move)) {
		std::cout << "Please enter a valid position;\n";
		std::cin >> move;
	}
	this->makeMove(move, size % 2 + 1);
}

void TicTacToe::computerMove() {
	for (int i = 0; i < 9; i++) {
		if (isValid(i)) {
			this->makeMove(i, size % 2 + 1);
			break;
		}
	}
}

void TicTacToe::makeMove(int move, int mark) {
	std::cout << "Player " << mark << " has placed at " << move << "\n";
	this->board[move] = mark;
	if (first_player_turn)
		first_player_turn = false;
	else
		first_player_turn = true;
	this->size++;
}

bool TicTacToe::isValid(int move) {
	return board[move] == 0;
}

int TicTacToe::hasWon() {
	std::vector<std::vector<int>> v = { {0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6} };
	for (std::vector<int> v : v) {
		if (board[v[0]] != 0 && (board[v[0]] == board[v[1]] && board[v[1]] == board[v[2]])) {
			return board[v[0]];
		}
	}
	return 0;
}

void TicTacToe::drawBoard()
{
	std::cout << map[board[0]] << "|" << map[board[1]] << "|" << map[board[2]] << std::endl;
	std::cout << "------" << std::endl;
	std::cout << map[board[3]] << "|" << map[board[4]] << "|" << map[board[5]] << std::endl;
	std::cout << "------" << std::endl;
	std::cout << map[board[6]] << "|" << map[board[7]] << "|" << map[board[8]] << std::endl;
}

void TicTacToe::printTurn()
{
	if (first_player_turn)
		std::cout << "It is player 1's turn.\n";
	else
		std::cout << "It is player 2's turn.\n";
}
