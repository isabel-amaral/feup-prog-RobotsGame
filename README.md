## PROG_T05_G03 - ROBOTS GAME

> **2020/2021** - 1st Year, 2nd Semester
> 
> **Course** - PROG (Programação)

### Game Description

The player is placed in a maze made up of posts which can be electrified or non-electrified. There are also
some interceptor robots that will try to destroy the player. If the player touches an electrified post or any of these
robots, that is the end of the game. The robots are also destroyed when they touch an electrified post or when they 
collide with each other, and they become stuck when they collide with a non-electrified post.

Every time the player moves in any direction (horizontally, vertically, or diagonally) to a contiguous cell, 
each robot moves one cell closer to the new player's location, in whichever direction is the shortest path. The robots
have no vision sensors but they have an accurate odour sensor that allows them to follow the player!

The maze has one or more exit gates. The objective is for the player to reach one of the exit gates, in the shortest time
possible, before being electrocuted or caught by a robot.

Before playing you can read the rules [here](./docs/RULES.txt).

For a more detailed version of this description click [here](./docs/PraticalAssignment-RobotsGame.pdf).

### Implemented features

- **Player control** - The player is moved with keyboard inputs that are recieved through the respective events.

- **Maze creation** -  Several mazes were created in .txt files that are read later on.
Therefore, different games can be played.

<p align="center">
  <img src="https://github.com/isabel-amaral/feup-prog-RobotsGame/blob/master/docs/screenshots/PlayMaze2.png" />
</p>
<p align="center">
  <img src="https://github.com/isabel-amaral/feup-prog-RobotsGame/blob/master/docs/screenshots/PlayMaze4.png" />
</p>

- **Menu** - Functional and interactive menu. The player has the possibility to play the game, choosing one of the different
  available mazes, to read the game rules or to view the list of previous winners for a specific maze alongside the repective game durations.

<p align="center">
  <img src="https://github.com/isabel-amaral/feup-prog-RobotsGame/blob/master/docs/screenshots/Menu.png" />
</p>

- **Rules** - Before each game the user has the possibility to read the game rules through the menu.

<p align="center">
  <img src="https://github.com/isabel-amaral/feup-prog-RobotsGame/blob/master/docs/screenshots/Rules.png" />
</p>

- **Winners list** - Every time a user wins, their name is registered in a list of Winners ordered by the time they took
to win the game.

<p align="center">
  <img src="https://github.com/isabel-amaral/feup-prog-RobotsGame/blob/master/docs/screenshots/WinMaze4.png" />
</p>

<p align="center">
  <img src="https://github.com/isabel-amaral/feup-prog-RobotsGame/blob/master/docs/screenshots/WinnersMaze4.png" />
</p>

- **Quit** - Ctrl^Z / Ctrl^D can be used at any time to quit the game.

### Program Development State

Since this was our first time using OOP concepts, the code isn't as organized as it could have been and there's definitely
room for improvement. However, all the goals were accomplished and all the specifications were completed. Overall it was a
really fun project and we were able to learn a lot.
