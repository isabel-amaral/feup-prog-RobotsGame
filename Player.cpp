//T05_G03
#include "Player.h"
#include <iostream>
using namespace std;

Player::Player()
{
	player_line = 0;
	player_col = 0;
	player_status = 'H';
	next_line = player_line;
	next_col = player_col;
}

Player::Player(int player_line, int player_col)
{
	this->player_line = player_line;
	this->player_col = player_col;

	//default
	player_status = 'H';
	next_line = player_line;
	next_col = player_col;
}

int Player::get_player_line() const
{
	return player_line;
}

int Player::get_player_col() const
{
	return player_col;
}

int Player::get_player_next_line() const
{
	return next_line; //gets the player's next line before moving it in order to check if any collisions will occur
}

int Player::get_player_next_col() const
{
	return next_col; //gets the player's next column before moving it in order to check if any collisions will occur
}

char Player::get_player_status() const
{
	return player_status;
}

char Player::ask_next_move() const
{
	char move;  //character inserted by the player to indicate next move

	cout << "Next move? "; cin >> move;
	while ((move != 'Q' && move != 'q' && move != 'W' && move != 'w' && move != 'E' && move != 'e' && move != 'A' && move != 'a' && move != 'S' && move != 's'
		&& move != 'D' && move != 'd' && move != 'Z' && move != 'z' && move != 'X' && move != 'x' && move != 'C' && move != 'c') || cin.peek() != '\n') {
		if (cin.eof()) { //if player inserted CTRL+Z/D the game's execution is stopped
			cout << "GAME OVER!";
			exit(0);
		}
		cin.clear();
		cin.ignore(100000, '\n');
		cerr << "Invalid input! Please insert another move." << endl;
		cout << "Next move: "; cin >> move;
	}
	return move;
}

void Player::next_move(char next_move)
{
	next_line = player_line;
	next_col = player_col;

	switch (next_move) {
	case 'S': case 's':  //player stays in same position
		break;
	case 'Q': case 'q':  //player moves to left-upper diagonal
		next_line--;
		next_col--;
		break;
	case 'W': case 'w':  //player mover up
		next_line--;
		break;
	case 'E': case 'e':  //player moves to right-upper diagonal
		next_line--;
		next_col++;
		break;
	case 'A': case 'a':  //player moves left
		next_col--;
		break;
	case 'D': case 'd':  //player moves right
		next_col++;
		break;
	case 'Z': case 'z':  //player moves to left-inferior diagonal
		next_line++;
		next_col--;
		break;
	case 'X': case 'x':  //player moves down
		next_line++;
		break;
	case 'C': case 'c':  //player moves to right-inferior diagonal
		next_line++;
		next_col++;
		break;
	}
}

void Player::move_player()
{
	//player's position is updated according to the direction chosen by the user
	player_line = next_line;
	player_col = next_col;
}

void Player::kill_player()
{
	player_status = 'h';
}