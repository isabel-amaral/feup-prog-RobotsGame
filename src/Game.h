//T05_G03
#ifndef GAME_H
#define GAME_H

#include "Maze.h"
#include "Player.h"
#include "Robot.h"
#include "Post.h"
#include <vector>
#include <string>

/* This class implements the game execution */
class Game
{
public:
	/* Game's constructor
	* maze_name - name of the file from where the maze will be loaded */
	Game(const string& maze_name);
	//Game's win flag getter function
	bool get_win_flag() const;
	//Game's duration getter function
	int get_game_duration() const;
	/* checks what object occupies a given position of the maze;
	if there's not a player, robot or post in that position it returns an empty space char,
	otherwise it returns a character corresponding to its status
	* line - line that needs to be checked
	* col - column that needs to be checked */
	char is_player(int line, int col) const;
	char is_robot(int line, int col) const;
	char is_post(int line, int col) const;
	//shows the maze to the screen
	void write_maze() const;
	/*Game's methods to check for collisions during the player's movement and make
	suitable changes to the objects according to the type of the collision
	* line - player's next line
	* col - player's next col */
	//checks for collision between the player and a robot that's not destroyed
	bool player_robot_collision(int line, int col);
	//checks for collision between the player and an electrified post
	bool player_electrified_post_collision(int line, int col);
	//checks for collision between the player and an exit door
	bool reached_exit_door(int line, int col);
	//checks for any kind of collisions between the player and the other maze's objects
	bool check_player_collisions();
	/*Game's methods to check for collisions during a robot's movement and make
	suitable changes to the objects according to the type of the collision
	* line - robot's next line
	* col - robots's next col
	* id - robot's index in the robots vector */
	//checks for collision between the robot and the player
	bool robot_player_collision(int line, int col, int id);
	//checks for collision between two robots
	bool robot_robot_collision(int line, int col, int id);
	//checks for collision between the robot and a non-electrified post
	bool robot_non_electrified_post_collision(int line, int col, int id);
	//checks for collision between the robot and a electrified post
	bool robot_eletrified_post_collision(int line, int col, int id);
	//checks for any kind of collisions between the robot and the other maze's objects
	bool check_robot_collisions(Robot& current_robot);
	//implements the game execution
	void play();

	/*player - instance of class Player
	* robots_vector - each element corresponds to an instance of class Robot
	* maze - instance of class Maze
	* game_over - flag that indicates whether the game is over
	* win - flag that indicates whether the game was won by the user
	* game_duration - time until the game is over */
private:
	Player player;
	vector<Robot> robots_vector;
	Maze maze;
	bool game_over;
	bool win;
	int game_duration;
};

#endif