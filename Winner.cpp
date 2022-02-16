//T05_G03
#include "Winner.h"
#include <fstream>
#include <iomanip>

Winners::Winners(const string& maze_name)
{
	maze_winners_name = maze_name.substr(0, 12) + "_WINNERS.txt";
	current_game_duration = 0;
	//other fields are initialized as empty vectors
	winners;
	winners_names;
	game_durations;
}

Winners::Winners(const string& maze_name, const int current_game_duration)
{
	maze_winners_name = maze_name.substr(0, 12) + "_WINNERS.txt";
	this->current_game_duration = current_game_duration;
	//other fields are initialized as empty vectors
	winners;
	winners_names;
	game_durations;
}

string Winners::get_player_name() const
{
	/* if the user wins the game, his/her name is read from the keyboard;
	more than one name is accepted, however it is limited to 15 characters */
	const unsigned int MAX_NAME_LEN = 16;  //15 name characters + 1 null character '\0'
	char player_name[MAX_NAME_LEN];

	cout << "Insert your name: ";
	cin.ignore(100000, '\n');
	cin.getline(player_name, MAX_NAME_LEN, '\n');
	if (sizeof(player_name) > MAX_NAME_LEN) {  //if the user inserts more than 15 characters, the extra ones will be ignored
		cin.clear();
		cin.ignore(100000, '\n');
	}

	return player_name;
}

void Winners::get_previous_winners_data()
{
	ifstream inFile;
	string next_line_str;
	vector<string> winners;  //each element is a line from the file of type "Player          - Time"

	inFile.open(maze_winners_name);
	inFile.ignore(100000, '\n');   //ignore header of the file - first two lines
	inFile.ignore(100000, '\n');
	while (getline(inFile, next_line_str))
		winners.push_back(next_line_str);
	inFile.close();

	string winner_name;
	string game_duration_str;
	int game_duration;

	/* each element from vector winners is distributed between two vectors: winner_names and game_durations;
	  each winner's name and respective game duration correspond to the same position in both vectors */
	for (size_t i = 0; i < winners.size(); i++) {
		winner_name = winners[i].substr(0, 17);
		winners_names.push_back(winner_name);
		game_duration_str = winners[i].substr(17, string::npos);
		game_duration = stoi(game_duration_str);
		game_durations.push_back(game_duration);
	}
}

void Winners::rewrite_sorted_winners_to_file()
{
	const unsigned int COL1_LENGHT = 16, COL2_LENGHT = 5;
	bool in_file = false;  //flag that indicates whether the current_game_duration was already written to file 

	ofstream outFile;
	outFile.open(maze_winners_name);

	outFile << "Player          - Time" << endl;
	outFile << "----------------------";

	for (size_t i = 0; i < game_durations.size(); i++) {
		if (current_game_duration < game_durations[i]) {
			if (!in_file) {
				outFile << endl << setw(COL1_LENGHT) << left << get_player_name() << '-' << setw(COL2_LENGHT) << right << current_game_duration;
				in_file = true;
			}
		}
		outFile << endl << winners_names[i] << setw(COL2_LENGHT) << right << game_durations[i];  //winners_names[i] and game_durations[i] are data from the same player
	}
	if (!in_file)
		outFile << endl << setw(COL1_LENGHT) << left << get_player_name() << '-' << setw(COL2_LENGHT) << right << current_game_duration;

	outFile.close();
}

void Winners::register_winners_and_time()
{
	const unsigned int COL1_LENGHT = 16, COL2_LENGHT = 5;
	bool open = true;

	ifstream file;
	file.open(maze_winners_name);  //checks if file already exists
	if (!file.is_open())           //file does not exist yet
		open = false;
	file.close();

	//maze's winners file is automatically created if it doesn't already exist
	if (!open) {
		ofstream outFile;
		outFile.open(maze_winners_name, ios::app);
		if (!open) {
			outFile << "Player          - Time" << endl;
			outFile << "----------------------";
			outFile << endl << setw(COL1_LENGHT) << left << get_player_name() << '-' << setw(COL2_LENGHT) << right << current_game_duration;
		}
		outFile.close();
	}

	/* file only needs to be sorted if there is more than one player in it (if it already existed); two other functions are called if that's the case
	for sorting the winners two vectors are created: one with their names and other with their respective games durations */
	else {
		get_previous_winners_data();
		rewrite_sorted_winners_to_file();
	}
}

void Winners::read_winners()
{
	ifstream inFile;
	string next_line;

	inFile.open(maze_winners_name);

	if (!inFile.is_open()) {
		cout << "Empty list" << endl;
		return;
	}

	while (getline(inFile, next_line)) {
		winners.push_back(next_line);
	}
	inFile.close();
}

void Winners::show_winners() const
{
	for (size_t i = 0; i < winners.size(); i++) {
		for (size_t j = 0; j < winners[i].size(); j++)
			cout << winners[i][j];
		cout << endl;
	}
	cout << endl;
}