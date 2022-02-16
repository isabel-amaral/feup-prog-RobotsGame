//T05_G03
#ifndef ROBOT_H
#define RBOT_H

/* This class implements a robot that is automatically moved along the game */
class Robot
{
public:
	/*Robot's constructor
	* robot_line - robot's beggining line
	* robot_col - robot's beggining column */
	Robot(int robot_line, int robot_col);
	//Robot's position getter methods
	int get_robot_line() const;
	int get_robot_col() const;
	//Robot's next position getter methods
	int get_robot_next_line() const;
	int get_robot_next_col() const;
	//Robot's current status getter method
	char get_robot_status() const;
	//Robot's ID getter method
	int get_robot_id() const;
	/*checks the relative position between the robot and player, decides in which direction
	the move should be done in order to get them as close as possible
	* player_line - line of the player's current position
	* player_col - column of the player's current position */
	void robot_next_move(int palyer_line, int player_column);
	//moves the robot normally if no collisions occur
	void move_robot();
	//updates the robot's status to 'r' after a collision
	void destroy_robot();
	//id counter - saves last robot id after every call
	static int robot_id_counter;

	/*robot_id - each robot is assigned an id number starting with 1
	* robot_line - line of the robot's cuurent position
	* robot_col - column of the robot's current position
	* robot_status - 'R' means robot is alive, 'r' means robot is dead
	* next_line - robot's next line
	* next_col - robot's next column */
private:
	int robot_id;
	int robot_line;
	int robot_col;
	char robot_status;
	//these two fields identify the robot's next move
	int next_line;
	int next_col;
};

#endif