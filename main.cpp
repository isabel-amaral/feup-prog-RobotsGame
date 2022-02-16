//T05_G03
#include "Game.h"
#include "Winner.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

//gets the number of the maze to be played
int ask_maze_num()
{
	int maze_num;
	bool valid_maze = true;
	cout << "Please chose a maze: "; cin >> maze_num;

	if (cin.eof())  //Ctrl-Z / Ctrl-D stops program execution
		exit(0);

	if (cin.fail() || cin.peek() != '\n' || maze_num < 0 || maze_num >= 100)
		valid_maze = false;

	//handles invalid inputs
	if (!valid_maze) {
		do {
			valid_maze = true;
			cin.clear();
			cin.ignore(100000, '\n');
			cerr << "Invalid maze! Please chose again." << endl;
			cout << "Chose a maze: "; cin >> maze_num;
			if (cin.fail() || cin.peek() != '\n' || maze_num < 0 || maze_num >= 100)
				valid_maze = false;
		} while (!valid_maze);
	}

	return maze_num;
}

/* returns the name of the file that contains the maze generated from maze_num
maze_num - number inserted by the user  */
string generate_maze_name(int maze_num)
{
	ostringstream maze_name;

	maze_name << "MAZE_";
	maze_name << setw(2) << setfill('0') << maze_num;
	maze_name << ".txt";

	return maze_name.str();
}

//checks if the maze chosen by the user is an existing file
bool available_maze(string maze_name)
{
	ifstream inFile;

	inFile.open(maze_name);
	//checks if file exists
	if (!inFile.is_open())
		return false;

	inFile.close();
	return true;
}

/* returns the name of the file that contains the winners ranking generated from maze_name
maze_name - name of the file that contains the maze being played */
string generate_maze_winners_name(string maze_name)
{
	string maze_winners_name = maze_name.substr(0, 7) + "_WINNERS.txt";
	return maze_winners_name;
}

//displays the game's rules to the screen
void show_rules()
{
	int back_to_menu;  //if player inserts '0' the game's menu should be shown to the screen
	string next_line;

	ifstream inFile;
	inFile.open("RULES.txt");
	if (!inFile.is_open()) {
		cout << "An error occured! Returning to menu...";
		return;
	}
	while (getline(inFile, next_line))
		cout << next_line << endl;
	inFile.close();

	cout << endl;

	cout << "Press 0 to go back to the menu" << endl;

	cin >> back_to_menu;
	cout << endl;

	while (back_to_menu != 0 || cin.peek() != '\n') {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Please insert 0 if you want to go back to the menu" << endl;
		cin >> back_to_menu;
	}
}

//displays the game's menu to the screen
void show_menu()
{
	int playing_option;

	do {
		cout << "Please choose an option:" << endl;
		cout << setw(9) << "1) Rules" << setw(10) << "2) Play" << setw(13) << "3) Winners" << setw(10) << "0) Exit" << endl;
		cin >> playing_option;

		if (cin.eof())  //Ctrl-Z / Ctrl-D stops program execution
			exit(0);

		while ((playing_option != 1 && playing_option != 2 && playing_option != 3 && playing_option != 0) || cin.peek() != '\n') {
			cin.clear();
			cin.ignore(100000, '\n');
			cout << "Invalid option! Try again" << endl;
			cout << "Please choose an option:" << endl;
			cout << setw(9) << "1) Rules" << setw(10) << "2) Play" << setw(13) << "3) Winners" << setw(10) << "0) Exit" << endl;
			cin >> playing_option;
		}

		switch (playing_option) {
		case 0: exit(0);
			break;
		case 1: show_rules();
			break;
		case 2:  //continues game execution
			break;
		case 3:
			int maze_num = ask_maze_num();
			string maze_name = generate_maze_name(maze_num);
			Winners winner(maze_name);
			winner.read_winners();
			winner.show_winners();
			break;
		}
	} while (playing_option != 2);
}

int main()
{
	cout << "***ROBOTS GAME***" << endl;
	show_menu();

	string maze_name;
	string maze_winners_name;

	do {
		int maze_num = ask_maze_num();
		if (maze_num == 0) {
			show_menu();
			maze_num = ask_maze_num();
		}
		maze_name = generate_maze_name(maze_num);
	} while (!available_maze(maze_name));
	maze_winners_name = generate_maze_winners_name(maze_name);

	Game game(maze_name);
	game.write_maze();
	game.play();

	if (game.get_win_flag()) {
		cout << "Exit gate was reached! YOU WIN" << endl;

		Winners winner(maze_name, game.get_game_duration());
		winner.register_winners_and_time();
		winner.read_winners();
		winner.show_winners();
	}
	else
		cout << "GAME OVER!" << endl;

	return 0;
}