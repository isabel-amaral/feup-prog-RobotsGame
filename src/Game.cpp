//T05_G03
#include "Game.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <chrono>
using namespace std;
using namespace std::chrono;

Game::Game(const string& maze_name)
{
	ifstream inFile;
	inFile.open(maze_name);

	ostringstream first_line;
	string next_line_str;
	int line_counter = 0;
	vector<Post> posts_vector;

	//first line contains the number of lines and columns of the maze separated by an 'x' and must be ignored
	int num_lines, num_cols;
	char sep;  //number of lines and columns are separated by 'x'
	inFile >> num_lines >> sep >> num_cols;
	inFile.ignore(10000, '\n');

	while (getline(inFile, next_line_str)) {  //next_line_str is a string that contains the characters of one of the maze's lines
		for (size_t i = 0; i < next_line_str.size(); i++) {

			//as each character of the maze is loaded, a vector of posts, a vector of robots and an instance of class Player will be initialized
			if (next_line_str[i] == '*' || next_line_str[i] == '+' || next_line_str[i] == 'O') {
				Post p(line_counter, i, next_line_str[i]);
				posts_vector.push_back(p);
			}
			if (next_line_str[i] == 'H') {
				Player p(line_counter, i);
				player = p;
			}
			if (next_line_str[i] == 'R') {
				Robot r(line_counter, i);
				robots_vector.push_back(r);
			}
		}
		line_counter++;
	}
	inFile.close();

	Maze m(num_lines, num_cols, posts_vector);
	maze = m;
	game_over = false;
	win = false;
	int game_duration = 0;
}

bool Game::get_win_flag() const
{
	return win;
}

int Game::get_game_duration() const
{
	return game_duration;
}

char Game::is_player(int line, int col) const
{
	if (line == player.get_player_line() && col == player.get_player_col())
		return player.get_player_status();

	return ' ';
}

char Game::is_robot(int line, int col) const
{
	for (size_t i = 0; i < robots_vector.size(); i++) {
		if (line == robots_vector[i].get_robot_line() && col == robots_vector[i].get_robot_col()) {
			return robots_vector[i].get_robot_status();
		}
	}
	return ' ';
}

char Game::is_post(int line, int col) const
{
	for (size_t i = 0; i < (maze.get_posts_vector()).size(); i++) {
		Post current_post = maze.get_posts_vector()[i];

		if (line == current_post.get_post_line() && col == current_post.get_post_col()) {
			return current_post.get_post_type();
		}
	}
	return ' ';
}

void Game::write_maze() const
{
	for (int i = 0; i < maze.get_num_lines(); i++) {     //i is maze line
		for (int j = 0; j < maze.get_num_cols(); j++) {  //j is maze column

			if (is_post(i, j) != ' ')
				cout << is_post(i, j);
			else if (is_robot(i, j) != ' ')
				cout << is_robot(i, j);
			else if (is_player(i, j) != ' ')
				cout << is_player(i, j);
			else
				cout << ' ';
		}
		cout << endl;
	}
}

bool Game::player_robot_collision(int line, int col)
{
	for (size_t i = 0; i < robots_vector.size(); i++) {

		if (line == robots_vector[i].get_robot_line() && col == robots_vector[i].get_robot_col()) {
			if (robots_vector[i].get_robot_status() == 'R') {
				robots_vector.erase(robots_vector.begin() + i);
				player.move_player();
				player.kill_player();
				game_over = true;
				return true;
			}
			return false;
		}
	}
	return false;
}

bool Game::player_electrified_post_collision(int line, int col)
{
	for (size_t i = 0; i < (maze.get_posts_vector()).size(); i++) {
		Post current_post = maze.get_posts_vector()[i];

		if (line == current_post.get_post_line() && col == current_post.get_post_col() && current_post.get_post_type() == '*') {
			player.kill_player();
			game_over = true;
			return true;
		}
	}
	return false;
}

bool Game::reached_exit_door(int line, int col)
{
	for (size_t i = 0; i < (maze.get_posts_vector()).size(); i++) {
		Post current_post = maze.get_posts_vector()[i];

		if (line == current_post.get_post_line() && col == current_post.get_post_col() && current_post.get_post_type() == 'O') {
			maze.erase_post(i);
			player.move_player();
			game_over = true;
			win = true;
			return true;
		}
	}
	return false;
}

bool Game::check_player_collisions()
{
	if (!player_robot_collision(player.get_player_next_line(), player.get_player_next_col()) &&
		!reached_exit_door(player.get_player_next_line(), player.get_player_next_col()) &&
		!player_electrified_post_collision(player.get_player_next_line(), player.get_player_next_col()))
		return false;

	return true;
}

bool Game::robot_player_collision(int line, int col, int id)
{
	if (line == player.get_player_line() && col == player.get_player_col()) {
		player.kill_player();
		game_over = true;
		return true;
	}
	return false;
}

bool Game::robot_robot_collision(int line, int col, int id)
{
	for (size_t i = 0; i < robots_vector.size(); i++) {

		if (i != id) {
			if (line == robots_vector[i].get_robot_line() && col == robots_vector[i].get_robot_col()) {
				robots_vector[id].destroy_robot();
				robots_vector[id].move_robot();    //both robots will be destroyed and occupy the same position

				if (robots_vector[i].get_robot_status() != 'r')  //if the collision is not with a destroyed robot
					robots_vector[i].destroy_robot();
				return true;
			}
		}
	}
	return false;
}

bool Game::robot_non_electrified_post_collision(int line, int col, int id)
{

	for (size_t i = 0; i < maze.get_posts_vector().size(); i++) {
		Post current_post = maze.get_posts_vector()[i];

		if (line == current_post.get_post_line() && col == current_post.get_post_col() && current_post.get_post_type() == '+') {
			maze.erase_post(i);
			robots_vector[id].move_robot();
			robots_vector[id].destroy_robot();
			return true;
		}
	}
	return false;
}

bool Game::robot_eletrified_post_collision(int line, int col, int id)
{
	for (size_t i = 0; i < maze.get_posts_vector().size(); i++) {
		Post current_post = maze.get_posts_vector()[i];

		if (line == current_post.get_post_line() && col == current_post.get_post_col()) {
			if (current_post.get_post_type() == '*') {
				robots_vector[id].destroy_robot();
				return true;
			}
			return false;
		}
	}
	return false;
}

bool Game::check_robot_collisions(Robot& current_robot)
{
	int index = current_robot.get_robot_id() - 1;
	if (!robot_player_collision(current_robot.get_robot_next_line(), current_robot.get_robot_next_col(), index) &&
		!robot_robot_collision(current_robot.get_robot_next_line(), current_robot.get_robot_next_col(), index) &&
		!robot_non_electrified_post_collision(current_robot.get_robot_next_line(), current_robot.get_robot_next_col(), index) &&
		!robot_eletrified_post_collision(current_robot.get_robot_next_line(), current_robot.get_robot_next_col(), index))
		return false;

	return true;
}

void Game::play()
{
	steady_clock::time_point start_timer, stop_timer;
	start_timer = steady_clock::now();

	while (!game_over) {

		char player_next_move = player.ask_next_move();
		player.next_move(player_next_move);

		if (is_robot(player.get_player_next_line(), player.get_player_next_col()) == 'r' || is_post(player.get_player_next_line(), player.get_player_next_col()) == '+') {
			do {
				cerr << "Invalid input! You can't move to places occupied by destroyed robots or non-electrified posts!" << endl;
				player_next_move = player.ask_next_move();
				player.next_move(player_next_move);
			} while (is_robot(player.get_player_next_line(), player.get_player_next_col()) == 'r' || is_post(player.get_player_next_line(), player.get_player_next_col()) == '+');
		}

		if (!check_player_collisions())
			player.move_player();       //no obstacles were found

		if (!game_over) {
			for (size_t i = 0; i < robots_vector.size(); i++) {

				if (!game_over && robots_vector[i].get_robot_status() != 'r') {
					robots_vector[i].robot_next_move(player.get_player_line(), player.get_player_col());

					if (!check_robot_collisions(robots_vector[i]))
						robots_vector[i].move_robot();  //no collisions occured, robot moves normally
				}
			}
		}
		write_maze();
	}

	stop_timer = steady_clock::now();
	game_duration = (int)duration_cast<seconds>(stop_timer - start_timer).count();
}