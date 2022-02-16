//T05_G03
#ifndef MAZE_H
#define MAZE_H

#include "Post.h"
#include <vector>
using namespace std;

/* This class implements the maze chosen by the user;
each maze is made os severall Post objects */
class Maze
{
public:
	//Maze's default constructor
	Maze();
	/* Maze's constructor
	* num_lines - number of lines in the maze
	* num_cols - number of columns in the maze
	* posts_vector - vector where each element corresponds to a Post object */
	Maze(int num_lines, int num_cols, vector<Post> posts_vector);
	//Maze's dimension getter methods
	int get_num_lines() const;
	int get_num_cols() const;
	//Maze's posts getter method
	vector<Post> get_posts_vector() const;
	/* when a robot collides with a non-electrified post or the player reaches an exit door, the posts are respectively replaced by a
	robot and a player in the maze so it gets deleted from the vector of posts
	* post_position - index of the post that will be removed from the vector */
	void erase_post(int post_position);

	/*num_lines - number of lines in the maze
	* num_cols - number of columns in the maze
	* posts_vector - vector where each element corresponds to a Post object from type '*', '+', or 'O' */
private:
	int num_lines;
	int num_cols;
	vector<Post> posts_vector;
};

#endif