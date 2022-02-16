//T05_G03
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <cstring>

using namespace std;

/* This class implements a player that can be moved by the user */
class Player
{
public:
	Player();  //Player's default constructor
	/*Player's constructor
	* line - player's beggining line
	* column - player's beggining column */
	Player(int line, int column);
	//Player's position getter methods
	int get_player_line() const;
	int get_player_col() const;
	//Player's next position getter methods
	int get_player_next_line() const;
	int get_player_next_col() const;
	//Player's current status getter method
	char get_player_status() const;
	//updates the player's status to 'h' after he/she was killed
	void kill_player();
	//reads from the keyboard in which direction the user wants to move the player
	char ask_next_move() const;
	/*updates the fields next_line and next_col (position the player will move to if no collisions occur)
	* next_move - letter corresponding to the move chosen by the user */
	void next_move(char next_move);
	//moves the player if the inserted move is valid and no collisions occur
	void move_player();

	/*player_line - line of the player's current position
	* player_col - column of the player's current position
	* player_status - 'H' means player is alive, 'h' means player is dead
	* next_line - player's next line
	* next_col - player's next column */
private:
	int player_line;
	int player_col;
	char player_status;
	//these two fields identify the player's next move
	int next_line;
	int next_col;
};

#endif