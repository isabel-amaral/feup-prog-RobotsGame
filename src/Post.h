//T05_G03
#ifndef POST_H
#define POST_H

/* This class implements a maze's post, which can be electrified, non-electrified or an exit gate */
class Post
{
public:
	/*Post's constructor
	* post_line - post's line
	* post_col - post's column
	* post_type - post's type identifier */
	Post(int post_line, int post_col, char post_type);
	//Post's position getter methods
	int get_post_line() const;
	int get_post_col() const;
	//Post's type getter method
	char get_post_type() const;

	/* post_line - each post has a definite line in the maze
	* post_col - each post has a definite column in the maze
	* post_type - '*' is an electrified post, '+' is a non-electrified post, 'O' is an exit door */
private:
	int post_line;
	int post_col;
	char post_type;
};

#endif
