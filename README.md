# Grid-Class
Task
You will write a class called Grid, and test it with a couple of programs. A Grid object will be made up of a grid of positions, numbered with rows and columns. Row and column numbering start at 0, at the top left corner of the grid. A grid object also has a "mover", which can move around to different locations on the grid. Obstacles (which block the mover) and other objects (that can be placed or picked up) are also available. Here is a sample picture of a Grid object in its display format:
0 . . .    This is a Grid object with 4 rows and 4 columns (numbered 0 - 3). 
. . > .    The mover '>' is at row 1, column 2, facing east. 
. . . .    The obstacle '#' is at row 3, column 1 
. # . .    The other item '0' is at row 0, column 0
The @ character indicates that the mover and an item (0) currently occupy the same position on the grid.
Program Details and Requirements
1) Grid class
Download this starter file: grid_starter.h and rename it as grid.h. Your member function prototypes are already given in this file. You will need to add appropriate member data. You will also need to define each of the member functions in the file grid.cpp. You may add whatever member data you need, but you must store the grid itself as a two-dimensional array. Maximum grid size will be 40 rows and 40 columns. (Note that this means dynamic allocation will NOT be needed for this assignment).
Meaning of Grid symbols
.	empty spot on the grid
0	an item that can be placed, or picked up
#	a block (an obstacle).  Mover cannot move through it
<	mover facing WEST
>	mover facing EAST
^	mover facing NORTH
v	mover facing SOUTH
@	mover occupying same place as item (0)
A printed space ' ' in a grid position represents a spot that the mover has already moved through when the path display is toggled on
Member function descriptions
Grid() 
The default constructor should create a 1 x 1 grid, with the mover in the only position, facing EAST 
 
Grid(int r, int c) 
The two-parameter constructor will accept two integers, representing rows and columns. Create a grid with r rows and c columns. If either of these is less than 3, default to 3. If either is greater than the max number of rows or columns, default to the max. This grid should be built such that blocks are placed all around the edge, with one random exit (i.e. with no block). The mover should be in a random position and facing a random direction within the grid. When setting up the randomness, make sure each possibility has an equal chance of happening. For example, the random direction has 4 possibilities, so each one should happen about 25% of the time. For the random exit, it will be sufficient to pick a random wall first, then pick a random location on that wall (note that the exit cannot be in a corner spot).
You'll need the library cstdlib for the srand and rand functions. While it's not normally the best place to do it, you can go ahead and seed the random number generator here in the constructor in some appropriate way so that it's different for seperate program runs.

Grid(int r, int c, int mr, int mc, int d) 
This constructor (5 parameters) takes in the following information, in this order:
number of starting rows for the grid (if out of range, adjust like in the 2-parameter constructor, although minimum in this case is 1)
number of starting columns for the grid (if out of range, adjust like in the 2-parameter constructor, although minimum in this case is 1)
The starting row position of the mover (if out of range, adjust to the first or last row, whichever is closer)
The starting column position of the mover (if out of range, adjust to the first or last column, whichever is closer)
The starting direction of the mover
Build the starting grid based on the incoming parameters and their descriptions above. Other than the mover, this grid starts out empty. 
 
Display() 
This function should print out "The Grid:" on one line, then output the full grid below it -- place spaces between columns so that outputs line up more evenly. End with a newline (so that any next output will be on a separate line). If the path setting is toggled to ON, then any position the mover has already moved through should show up blank. If the path setting is toggled to OFF, then all empty grid spaces show up as dots '.' 
Examples of the full Display format can be seen in the sample run for test1.cpp linked below under "Test Programs". 
For description of the path setting, see the funtion TogglePath() below 
 
TogglePath() 
This function, when called, should reverse whatever the current "path" setting is. The path setting can be either ON or OFF. If it's ON, it means that displays of the grid should indicate where the mover has been by showing those positions as spaces. If the path is OFF, then all blank spots on the grid show as the dot character '.' no matter what. The initial default setting for any grid should be ON. 
 
Simple Accessors 
These are accessor functions that should return the requested information:
GetRow() should return the current row of the mover
GetCol() should return the current column of the mover
GetNumRows() should return the number of rows in the grid
GetNumCols() should return the number of columns in the grid

Predicate functions 
These two functions return boolean values (true or false) to answer simple questions:
FrontIsClear() should return an indication of whether the space in front of the mover is clear (i.e. not blocked)
RightIsClear() should return an indication of whether the space to the right of the mover is clear (i.e. not blocked)

Placing blocks and/or items 
These functions involve placing things on the grid:
PutDown(): This function should place an "item" at the current location of the mover. If the location already contains an item, then nothing changes (i.e. the item is still there)
PutDown(int r, int c): This function should place an "item" at position (r,c) where r is the row and c is the column. This function should return true for a successful placement, and false for failure. For successful placement, the position has to exist within the grid boundaries and not already contain a block or another item. (It can, however, be placed in a spot where only the mover is located).
PlaceBlock(int r, int c): This function should place a "block" at position (r,c) where r is the row and c is the column. This function should return true for a successful placement, and false for failure. For successful placement, the position has to exist within the grid boundaries and be an empty space (i.e. not containing a block, an item, or the mover)

PickUp() 
This function should pick up the "item" at the mover's position. This means removing it from the grid. This function should return true for a successful pick-up (i.e. the item is at the mover's current position), and false for failure (there is no item there). 
 
Move(int s) 
This function should move the mover forward, in the current direction, for s spaces. Return true for success, false for failure. A successful move must be a positive number of spaces, must remain on the grid, and must not attempt to move through a "block". On a failed move, the mover should remain in the original position. (i.e. the move must be all or nothing, based on the number of spaces given by the parameter). 
 
TurnLeft() 
This function will cause the mover to turn 90 degrees to the left, from whichever way it is currently facing. (example: if the mover is facing NORTH, then TurnLeft() will make it face WEST). 
 
void Grow(int gr, int gc) 
This function should increase the size of the grid by gr rows and gc columns. If the increase causes either the number of rows or columns to exceed the maximum, simply set that (rows or columns) to the maximum. The grow should not change the current position of any item, mover, or block on the grid. 
 
Note that the list of member functions given in the provided starter file (and described above) constitute the entire public interface of the class. These should be the ONLY public member functions in your class. If you create any extra member functions as helpers, put them in the private section of the class

2) Test Programs
Two test program descriptions follow. One is provided to you, the other is a program for you to write to submit.
Maze!
You are being provided one starter test program, along with the sample output:

test1.cpp
output1.txt
You can use this to help test your class, but keep in mind that this is NOT a comprehensive set of tests. It is a small program that builds a simple maze in a grid, then has the mover navigate through the maze to pick up an item. It also drops a couple of other items on the way.
You can certainly add to this and/or write your own test programs to help test your class features. 
 
Trapped!
Write a main program in a file called trap.cpp that solves the following scenario, using your Grid class:

Giant Mole People have risen from their underground lairs and are taking over the world. You have been taken prisoner and placed in an underground jail cell. Since the Mole People are blind and don't know how to build doors, your cell has one open exit (no door). Since you are deep underground, it is completely dark and you cannot see. Your task is to escape your prison to join the human resistance!

Your program should ask the user to input the number of rows, then columns, for the grid. (Note that this is the ONLY keyboard input for this program). Create a grid with the specified number of rows and columns, using the constructor with two parameters -- (this is the one that should automatically create a fenced-in grid containing one exit and a randomly placed mover). Display the initial grid. Since the placement of the exit and the mover is random, execution of this program will look a little different every time. Your task is to escape the trap! You will need to create an algorithm that will instruct the mover to find its way to the exit. (Hint: Think about how to use the Predicate functions before you move). Upon reaching the exit, you should print a message of success, like "We escaped!", and then output the final position of the mover. Keep the path toggled ON. You only need to display the initial setup grid and the final grid for this program.

General Requirements:

All class member data (other than the provided static constants) must be private
As your only output in the Grid class is the Display function, your output should match mine exactly. (i.e. if I check your output against mine with the "diff" command, there should be no differences in the output of a grid).
Adhere to the good programming practices discussed in class. (No global variables, use const in all appropriate places, don't #include .cpp files, document your code. etc).
You may use the iostream library, as well as any of the basic C function libraries. You'll probably want to take a look at ctime and cstdlib for setting up random number generation
Do not use any C++11 - only features

