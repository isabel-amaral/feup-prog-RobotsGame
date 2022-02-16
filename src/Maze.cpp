//T05_G03
#include "Maze.h"

Maze::Maze()
{
	num_lines = 0;
	num_cols = 0;
	posts_vector;
}

Maze::Maze(int num_lines, int num_cols, vector<Post> posts_vector)
{
	this->num_lines = num_lines;
	this->num_cols = num_cols;
	this->posts_vector = posts_vector;
}

int Maze::get_num_lines() const
{
	return num_lines;
}

int Maze::get_num_cols() const
{
	return num_cols;
}

vector<Post> Maze::get_posts_vector() const
{
	return posts_vector;
}

void Maze::erase_post(int post_position)
{
	posts_vector.erase(posts_vector.begin() + post_position);
}