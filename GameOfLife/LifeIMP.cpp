// Implementation of Life .cpp
// Code by Joshua Smith

#include "Life.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

Life :: Life() // Constructor, assigns numbers to these variables
{
	density = 0;
	numOfX = 0;
}

Life :: ~Life() //Destructs all open streams and all the dynamically allocated arrays
{

	if (outputFileStream.is_open())
	{
		outputFileStream.close();
	}
	if (inputFileStream.is_open())
	{
		inputFileStream.close();
	}
	
	
	for (int i = 0; i < arrayRows; ++i)
	{
		delete [] originalArray[i];
		delete [] curr[i];
		delete [] next[i];
	
	}
	delete [] originalArray;
	delete [] curr;
	delete [] next;
	
	//delete any dynamically allocated arrays
}

void Life :: questions() // Asks the player some questions to determine how the game will play out
{
	string ynReadFile;
	cout << "Would you like to read from a file, or do a random generation? Respond with 'read' or 'random': ";
	cin >> ynReadFile;
	if (ynReadFile == "read")
	{
		readFile = true;
		cout << "Please enter the file name, followed by a .txt: ";
		cin >> inputFileString;
		inputFileStream.open(inputFileString.c_str());
		
		setSizes();
		
		
	}
	if (ynReadFile == "random")
	{
		setSizes();
	}
	cout << "Which mode would you like: Classic, Doughnut, or Mirror? type C, D, or M: ";
	cin >> cDM;
	cout << "Did you want the game to pause automatically, have you press 'enter' to continue, or output results? Type P, E, or O: ";
	cin >> pEO;
	if ((pEO == 'O') || (pEO == 'o'))
	{
		cout << "Please enter the name of the file you would like to output to: ";
		cin >> outputFileString;
		outputFileStream.open(outputFileString.c_str(), ios::out | ios::app);
	}
	
	
		
}


void Life:: setSizes() // used in read or random
{	// If file is being read in, sets the dimensions of the array correctly, as well keeping the original sizes
	if (inputFileStream.is_open())
		{
			string line;
			getline (inputFileStream, line);
			originalArrayRows = atoi(line.c_str());
			getline (inputFileStream, line);
			originalArrayColumns = atoi(line.c_str());

			arrayRows = originalArrayRows + 2;
			arrayColumns = originalArrayColumns + 2;
			
		}
	// If the player will be using a random grid. This will grab the dimensions of the grid as well as the density
	else
		{
			cout << "Please enter the height of your random grid: ";
			cin >> originalArrayRows;
			cout << "Please enter the width of your random grid: ";
			cin >> originalArrayColumns;

			arrayRows = originalArrayRows +2;
			arrayColumns = originalArrayColumns +2;

			cout << "Please enter the desired population density in the form of a decimal(between 0 and 1): ";
			cin >> density;
		}

}

void Life :: createArrays() // Initializes arrays. Will be destructed later in the destructor.
{
	oArrayExists = true; // testing, making sure array can be destructed
	
	originalArray = new int*[arrayRows];
	for (int i = 0; i < arrayRows; ++i) //DESTRUCT BOTH LATER!!!!
	{
		originalArray[i] = new int[arrayColumns];
	}
	curr = new int*[arrayRows];
	for (int a = 0; a < arrayRows; ++a) //DESTRUCT BOTH LATER!!!!
	{
		curr[a] = new int[arrayColumns];
	}

	next = new int*[arrayRows];
	for (int b = 0; b < arrayRows; ++b) //DESTRUCT BOTH LATER!!!!
	{
		next[b] = new int[arrayColumns];
	}
}


void Life :: fillArrayInitial(int **arr) // Fills the array for the first time, based off of using either a file/random grid.
{
	string line;

	// From a file
	if (readFile)
	{
		for (int s = 1; s < arrayRows -1; ++s)
		{
			getline (inputFileStream, line);
			for (int b = 1; b < arrayColumns - 1; ++b)
			{
				if ((line[b-1] == 'X') || (line[b-1] == 'x'))
				{
					arr[s][b] = X;
				}
				else if (line[b-1] == '-')
				{
					arr[s][b] = dash;
				}
			}
		}	

			
	}
	//Sets grid based on density
	else if (density > 0)
	{
		int row = 0;
		int column = 0;
		int xPopulation=(originalArrayRows*originalArrayColumns)*(density); // gets the number of x's to put in grid
		
		for (int s = 1; s < arrayRows -1; ++s) // fills grid with dashes first
		{
			for (int b = 1; b < arrayColumns - 1; ++b)
			{
				arr[s][b] = dash;	
			}
		}
		/////////////////////////////////////////////////////////////////////////
		//fills in grid with x's in random spots, based off of population density
		/////////////////////////////////////////////////////////////////////////

		while (xPopulation > 0)
		{
			row = rand() % originalArrayRows + 1;
			column = rand() % originalArrayColumns + 1;
			if (arr[row][column] != X)
			{
				arr[row][column] = X;
				--xPopulation;
			}
			
		}

	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Most important method below.
// It fills the sides of the array based off of the setting you chose at the beginning (Classic, Doughnut, Mirror)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Life :: fillArraySides(int **arr) // Fill sides of array based off of the mode selected
{
	//sets to empty the outside rows and columns.  originalArray as argument for initial, next for game loop
	if((cDM == 'C') || (cDM == 'c'))
	{	
		
		for (int a = 0; a < arrayRows; ++a)
		{
			for (int b = 0; b < arrayColumns; ++b)
			{
				if((a == 0) || (a == arrayRows-1))
				{
					arr[a][b] = dash;
				}
				if ((b == 0) || (b == arrayColumns-1))
				{
					arr[a][b] = dash;
				}
			}
		}
	}
	//sets to doughnut mode/mirror mode. originalArray as argument for initial, next for game loop
	if( ((cDM == 'D') || (cDM == 'd')) || ((cDM == 'M') || (cDM == 'm')) )
	{	
		for (int a = 1; a < arrayRows-1; ++a)
		{
			for (int b = 1; b < arrayColumns-1; ++b)
			{
				if((a == 1) && (b == 1)) //top left corner
				{
					if ((cDM == 'D') || (cDM == 'd'))
					{
						arr[a-1][b-1] = arr[arrayRows-2][arrayColumns-2];
					}
					if ((cDM == 'M') || (cDM == 'm'))
					{
						arr[a-1][b-1] = arr[a][b];
						arr[a-1][b] = arr[a][b];
						arr[a][b-1] = arr[a][b];
					}
				}
				if( (a == 1) && ((b > 1) && (b < arrayColumns -2)) )// top middle section
				{
					if ((cDM == 'D') || (cDM == 'd'))
					{
						arr[a-1][b-1] = arr[arrayRows-2][b-1];
						arr[a-1][b] =  arr[arrayRows -2][b];
						arr[a-1][b+1] = arr[arrayRows -2][b+1];
					}
					if ((cDM == 'M') || (cDM == 'm'))
					{
						arr[a-1][b] = arr[a][b];
						
					}
				}
				if ((a == 1) && (b == arrayColumns - 2)) // top right corner
				{
					if ((cDM == 'D') || (cDM == 'd'))
					{
						arr[a-1][b+1] = arr[arrayRows - 2][1];
					}
					if ((cDM == 'M') || (cDM == 'm'))
					{
						arr[a-1][b] = arr[a][b];
						arr[a-1][b+1] = arr[a][b];
						arr[a][b+1] = arr[a][b];	
					}
				}
				if ( ((a > 1) && (a < arrayRows - 2)) && (b == arrayColumns - 2) ) // right side middle
				{
					if ((cDM == 'D') || (cDM == 'd'))
					{
						arr[a-1][b+1] = arr[a-1][1];
						arr[a][b+1] = arr[a][1];
						arr[a+1][b+1] = arr[a+1][1];
					}
					if ((cDM == 'M') || (cDM == 'm'))
					{
						arr[a][b+1] = arr[a][b];	
					}
				}
				if ( (a == arrayRows -2) && (b == arrayColumns - 2) ) // bottom right corner
				{
					if ((cDM == 'D') || (cDM == 'd'))
					{
						arr[a+1][b+1] = arr[1][1];
					}
					if ((cDM == 'M') || (cDM == 'm'))
					{
						arr[a][b+1] = arr[a][b];
						arr[a+1][b+1] = arr[a][b];
						arr[a+1][b] = arr[a][b];	
					}
				}
				if ( (a == arrayRows -2) && ((b < arrayColumns - 2) && (b > 1)) ) // bottom portion
				{
					if ((cDM == 'D') || (cDM == 'd'))
					{
						arr[a+1][b+1] = arr[1][b+1];
						arr[a+1][b] = arr[1][b];
						arr[a+1][b-1] = arr[1][b-1];
					}
					if ((cDM == 'M') || (cDM == 'm'))
					{
						arr[a+1][b] = arr[a][b];	
					}
				}
				if ((a == arrayRows -2) && (b == 1)) // bottom left corner
				{
					if ((cDM == 'D') || (cDM == 'd'))
					{
						arr[a+1][b-1] = arr[1][arrayColumns -2];
					}
					if ((cDM == 'M') || (cDM == 'm'))
					{
						arr[a+1][b] = arr[a][b];
						arr[a+1][b-1] = arr[a][b];
						arr[a][b-1] = arr[a][b];
					}
				}
				if ( ((a < arrayRows - 2) && (a > 1)) && (b == 1) ) // left side middle
				{
					if ((cDM == 'D') || (cDM == 'd'))
					{
						arr[a+1][b-1] = arr[a+1][arrayColumns -2];
						arr[a][b-1] = arr[a][arrayColumns - 2];
						arr[a-1][b-1] = arr[a-1][arrayColumns - 2];
					}
					if ((cDM == 'M') || (cDM == 'm'))
					{
						arr[a][b-1] = arr[a][b];
					}
				}
	
			}
		}
	}
	
}

void Life :: checkIfEmpty(int **arr) // Check to see if array has emptied, so you can quit the game later
{
	int result = 0;
	for (int s = 0; s < arrayRows; ++s)
	{
		
		for (int b = 0; b < arrayColumns; ++b)
		{
			if (arr[s][b] == X)
			{
				result +=1;
			}
			
		}	
	}
	numOfX = result;	
}

bool Life :: checkIfStable(int **arr1, int **arr2) // checks to see if the array has stablized, so you can quit later
{
	for (int s = 0; s < arrayRows; ++s)
	{
		
		for (int b = 0; b < arrayColumns; ++b)
		{
			if (arr1[s][b] != arr2[s][b])
			{
				return false;
			}
			
		}	
	}
	
	return true;

}



void Life :: copyAll(int **from, int **to) // Copies one array's contents to another array
{
	for (int s = 0; s < arrayRows; ++s)
	{
		
		for (int b = 0; b < arrayColumns; ++b)
		{
			if (from[s][b] == X)
			{
				to[s][b] = X;
			}
			else if (from[s][b] == dash)
			{
				to[s][b] = dash;
			}
		}
	}

}


void Life :: printArray(int ** arr) // print original array
{
	cout << whichGen << endl;
	for (int s = 1; s < arrayRows - 1; ++s)
	{
		
		for (int b = 1; b < arrayColumns - 1; ++b)
		{
			if (arr[s][b] == X)
			{
				cout << "X";
			}
			else if (arr[s][b] == dash)
			{
				cout << "-";
			}
		}
		cout << endl;
	}
	++whichGen;

}
void Life :: printArrayUTIL() // UTIL PRINT
{
	cout << whichGen << endl;
	for (int s = 1; s < arrayRows - 1; ++s)
	{
		
		for (int b = 1; b < arrayColumns - 1; ++b)
		{
			if (curr[s][b] == X)
			{
				cout << "X";
			}
			else if (curr[s][b] == dash)
			{
				cout << "-";
			}
		}
		cout << endl;
	}

}

void Life :: printWholeEntireArray() //utility purposes , prints curr array
{
	cout << whichGen << endl;
	for (int s = 0; s < arrayRows; ++s)
	{
		
		for (int b = 0; b < arrayColumns; ++b)
		{
			if (curr[s][b] == X)
			{
				cout << "X";
			}
			else if (curr[s][b] == dash)
			{
				cout << "-";
			}
		}
		cout << endl;
	}
	++whichGen;

}
void Life :: printToOutput(int **arr) // print to a file (stream is closed in the destructor)
{
	outputFileStream << whichGen << endl;
	if(outputFileStream.is_open())
	{
		for (int s = 1; s < arrayRows - 1; ++s)
		{
			for (int b = 1; b < arrayColumns - 1; ++b)
			{
				if (arr[s][b] == X)
				{
					outputFileStream << "X";
				}
				else if (arr[s][b] == dash)
				{
					outputFileStream << "-";
				}
			}
			outputFileStream << endl;
		}
	}
	++whichGen;
}




void Life:: setUp() // set up the game intially
{
	//by creating the arrays, filling in the array inside based off file/density
	//filling in the outer part of the array
	//copying the original setup to the curr array
	questions();
	createArrays();
	fillArrayInitial(originalArray);
	fillArraySides(originalArray);
	copyAll(originalArray, curr);
	checkIfEmpty(curr);
	pauseEnterOrOutput();
	
}

void Life :: pauseEnterOrOutput() //Either prompts for a continue key, or prints everything to a file based on your preference
{
	if ((pEO == 'P') || (pEO == 'p'))
	{
		printArray(curr);
		cin.get();
	}
	if ((pEO == 'E') || (pEO == 'e'))
	{
		printArray(curr);
		cout << "Please press enter to continue simulation: " << endl;
		cin.get();
	}
	if ((pEO == 'O') || (pEO == 'o'))
	{
		printToOutput(curr);
	}
}

void Life ::theGame()
{
	// At this point, the arrays have been set up initially, the
	//boundary mode has been set, and the printer functionality 
	//should already be set up too.

	////////////////////////////////////////////////////////////////////
	// Checks array and fills it in according to the Game of Life rules
	////////////////////////////////////////////////////////////////////
	while (numOfX != 0)
	{
		
		for (int s = 1; s < arrayRows -1; ++s)
		{
			for (int b = 1; b < arrayColumns -1; ++b)
			{
				//case 1: One or Fewer Neighbors
				if ((curr[s-1][b]) + (curr[s-1][b+1]) + (curr[s][b+1]) + (curr[s+1][b+1]) + (curr[s+1][b]) +
					(curr[s+1][b-1]) + (curr[s][b-1]) + (curr[s-1][b-1]) <= 1)
				{
					next[s][b] = dash;
				}
				//case 2: 2 Neighbors
				if ((curr[s-1][b]) + (curr[s-1][b+1]) + (curr[s][b+1]) + (curr[s+1][b+1]) + (curr[s+1][b]) +
					(curr[s+1][b-1]) + (curr[s][b-1]) + (curr[s-1][b-1]) == 2)
				{
					next[s][b] = curr[s][b];
				}
				//case 3 : 3 Neighbors
				if ((curr[s-1][b]) + (curr[s-1][b+1]) + (curr[s][b+1]) + (curr[s+1][b+1]) + (curr[s+1][b]) +
					(curr[s+1][b-1]) + (curr[s][b-1]) + (curr[s-1][b-1]) == 3)
				{
					next[s][b] = X;
				}
				//case 4: 4 or More Neighbors
				if ((curr[s-1][b]) + (curr[s-1][b+1]) + (curr[s][b+1]) + (curr[s+1][b+1]) + (curr[s+1][b]) +
					(curr[s+1][b-1]) + (curr[s][b-1]) + (curr[s-1][b-1]) >= 4)
				{
					next[s][b] = dash;
				}
			
			}
		}

		///////////////////////////////////////////////////////////////////////////
		// Fill the sides of the array depending on the mode
		///////////////////////////////////////////////////////////////////////////
		fillArraySides(next);
		///////////////////////////////////////////////////////////////////////////
		// Exit game if it becomes stable
		///////////////////////////////////////////////////////////////////////////
		if (checkIfStable(curr, next))
		{
			if ((pEO == 'O') || (pEO == 'o'))
			{
				if(outputFileStream.is_open())
				{
					outputFileStream << "The grid is stable. Program end. " << endl;
				}
			}
			else
			{
				cout << "The grid is stable. Program end. " << endl;
			}
			break;
			
		}
		///////////////////////////////////////////////////////////////////////////
		// copy to curr, next remains the same
		///////////////////////////////////////////////////////////////////////////
		copyAll(next, curr);

		//////////////////////////////////////////////////////////////////////////
		// It's here where you want to run a method to check if the array is empty
		//////////////////////////////////////////////////////////////////////////
		checkIfEmpty(curr);
	
		//////////////////////////////////////////////////////////////////////////
		// pause simulation, require "enter", or print to output.
		//////////////////////////////////////////////////////////////////////////
		pauseEnterOrOutput();

	}
	
}



