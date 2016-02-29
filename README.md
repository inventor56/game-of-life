# game-of-life
The Game of Life - Including Classic, Doughnut, and Mirror Modes!

Name: Joshua Smith


Comments:
	- I used an array that was 2 rows and 2 columns bigger than the original grid so that I could
	  check for empty spaces (classic mode), wrapped around references (doughnut mode), and
	  references reflected back (mirror mode).
	
Issues:
	- Since I made the program through the Linux VM, system("pause") doesn't work. It just
	  waits for the user to hit a key on the keyboard.
	- I used cin.get() to wait for user input to continue. But, there seems to be a bug where
	  it automatically prints out the original generation as well as the next generation. 
