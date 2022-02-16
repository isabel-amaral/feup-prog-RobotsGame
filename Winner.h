//T05_G03
#ifndef WINNER_H
#define WINNER_H

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

/* This class implements a ranking of winners for each maze */
class Winners
{
public:
	/*Winners constructor - called only for reading the list of winners
	* maze_name - name of the maze whose winners the user wants to check */
	Winners(const string& maze_name);
	/*Winners constructor - called for adding a new winner, sorting the list a reading ir afterwards
	* maze_name - name of the maze being played
	* current_game_duration - time that the game that just ended lasted */
	Winners(const string& maze_name, const int current_game_duration);
	//gets the Winner's name
	string get_player_name() const;
	//reads from file players' names and their respective times to 2 seperate vectors
	void get_previous_winners_data();
	//sorts and rewrites winners' names and respective times into the file
	void rewrite_sorted_winners_to_file();
	//writes winner and his/her game duration to the file
	void register_winners_and_time();
	//reads the list of winners from the file
	void read_winners();
	//updates the list of winners with the player's name and time
	void show_winners() const;

	/*maze_winners_name - name of the file where the winners will be read/written to
	* winners - each element corresponds to a winners file line
	* winners_names - each element corresponds to a winner's name
	* game_durations - each element corresponds to a winner's time
	* current_game_duration - how long took the game that just ended */
private:
	string maze_winners_name;
	vector<string> winners;
	vector<string> winners_names;
	vector<int> game_durations;
	int current_game_duration;
};

#endif
