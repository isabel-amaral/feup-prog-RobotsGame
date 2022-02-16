//T05_G03
#include "Post.h"

Post::Post(int post_line, int post_col, char post_type)
{
	this->post_line = post_line;
	this->post_col = post_col;
	this->post_type = post_type;
}

int Post::get_post_line() const
{
	return post_line;
}

int Post::get_post_col() const
{
	return post_col;
}

char Post::get_post_type() const
{
	return post_type;
}