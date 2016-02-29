# game-of-life
The Game of Life - Including Classic, Doughnut, and Mirror Modes!

Code by Joshua Smith

The Game of Life:
This program will run the Game of Life simulation. It works by using multi-dimensional arrays
which are all of the same size. However, these arrays are each 1 row bigger and 1 column bigger
than the original grids, so that we can run more modes in the game (Doughnut/Mirror).

One of the big challenges in this program was trying to iterate and index through all these
arrays, and so I decided to try and break up the program into smaller methods. That way, I was
able to clearly focus on which methods did what.

The program begins by setting up the game:
	The player chooses whether to use a file with the dimensions listed and a grid
		or:
	The player opts to use a randomly generated grid based off of their input

	The player then is asked whether they want to play classic, doughnut, or mirror mode.

	Next, the player can choose to either have the simulation pause for them, wait for
	their input (like the enter key), or have the results printed out to a file name of
	their choice! ***********PAUSE MODE IS NOT WORKING ON THE LINUX VM******************

The program then runs the game:
	The game checks the grid and applies the game rules to it. The new grid is stored in a
	separate 2D array, so that we don't mess up the simulation rules. After it's all done,
	the array is copied back to the original one so we can start again for the next generation.

	The game ends when the grid either empties out or stablizes.

Enjoy!!!


Comments:
	- I used an array that was 2 rows and 2 columns bigger than the original grid so that I could
	  check for empty spaces (classic mode), wrapped around references (doughnut mode), and
	  references reflected back (mirror mode).
	
Issues:
	- Since I made the program through the Linux VM, system("pause") doesn't work. It just
	  waits for the user to hit a key on the keyboard.
	- I used cin.get() to wait for user input to continue. But, there seems to be a bug where
	  it automatically prints out the original generation as well as the next generation. 
