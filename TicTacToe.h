#pragma once
class TicTacToe
{
public:
	int board[9];
	int num_players;
	char* map;
	bool first_player_turn;
	int size;

	TicTacToe();
	void drawBoard();
	void printTurn();
	void humanMove();
	void computerMove();
	void makeMove(int, int);
	bool isValid(int);
	int hasWon();
};

