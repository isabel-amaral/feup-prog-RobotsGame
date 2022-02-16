//T05_G03
#include "Robot.h"

int Robot::robot_id_counter = 1;

Robot::Robot(int robot_line, int robot_col)
{
	this->robot_col = robot_col;
	this->robot_line = robot_line;
	robot_status = 'R';  //default

	robot_id = robot_id_counter;
	robot_id_counter++;

	next_line = this->robot_line;  //default
	next_col = this->robot_col;
}

int Robot::get_robot_line() const
{
	return robot_line;
}

int Robot::get_robot_col() const
{
	return robot_col;
}

int Robot::get_robot_next_line() const
{
	return next_line; //gets robot's next line before moving it in order to check if any collisions will occur
}

int Robot::get_robot_next_col() const
{
	return next_col; //gets robot's next column before moving it in order to check if any collisions will occur
}

char Robot::get_robot_status() const
{
	return robot_status;
}

int Robot::get_robot_id() const
{
	return robot_id;
}

void Robot::robot_next_move(int player_line, int player_col)
{
	next_line = robot_line;
	next_col = robot_col;

	if (robot_col == player_col) {

		if (robot_line < player_line) {  //the robot is above the player; needs to move down 
			next_line++;  //robot moves to next line
			return;
		}
		if (robot_line > player_line) {  //the robot is bellow the player; needs to move up
			next_line--;  //robot moves to previous line
			return;
		}
	}
	if (robot_line == player_line) {

		if (robot_col < player_col) {    //the robot is left to the player; needs to move right
			next_col++;  //robot moves to next column
			return;
		}
		if (robot_col > player_col) {    //the robot is right to the player; needs to move left
			next_col--;  //robot moves to previous column
			return;
		}
	}

	//if robot and player are neither in the same line nor the same column robot needs to move diagonally
	if (robot_col < player_col && robot_line < player_line) {
		next_line++;
		next_col++;
		return;
	}
	if (robot_col < player_col && robot_line > player_line) {
		next_line--;
		next_col++;
		return;
	}
	if (robot_col > player_col && robot_line < player_line) {
		next_line++;
		next_col--;
		return;
	}
	if (robot_col > player_col && robot_line > player_line) {
		next_line--;
		next_col--;
		return;
	}
}

void Robot::move_robot()
{
	//robot's position is updated according to the direction which gets it closer to the player
	robot_line = next_line;
	robot_col = next_col;
}

void Robot::destroy_robot()
{
	robot_status = 'r';
}