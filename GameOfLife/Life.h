// header file .h
// Code by Joshua Smith

#ifndef MY_HEADER_FILE
#define MY_HEADER_FILE

#include <iostream>
#include <string>
#include <fstream>

const int X = 1; // 1 is X
const int dash = 0; // 0 is - 

class Life {

public:
	Life(); // constructor
	~Life(); // destructor

	void questions(); //SET UP: asks questions to the user regarding input, mode, and output settings
	void createArrays(); //SET UP: creates the initial array based off either a .txt file or population density
	void setSizes(); //SET UP: sets the sizes for array, with "original" being the original size of the grid, and "array" being +2
	void fillArrayInitial(int **arr); //SET UP: filling initially
	///////////////////////////////////////////////////////////////////////////////////////////////
	void fillArraySides(int **arr); // FILLS THE OUTSIDE ARRAYS ACCORDING TO WHICH MODE IS SELECTED
	///////////////////////////////////////////////////////////////////////////////////////////////
	void copyAll(int **arr1, int **arr2); //SET UP: copies initial array config
	void checkIfEmpty(int **arr); //SET UP: checks to see if the grid has emptied
	bool checkIfStable(int **arr1, int **arr2); //checks to see if stable
	void pauseEnterOrOutput(); //SET UP: checks to see if the program should pause, wait for enter, or just output to txt
	//////////////////////////////////////////////////////
	
	
	void setUp(); //sets up the game using the set up methods above
	void theGame(); //runs the game loop
	void printArray(int **arr); //prints the array to screen
	void printArrayUTIL(); // utility function
	void printWholeEntireArray(); //utility function
	void printToOutput(int **arr); //prints the resulting grids to an output file
	

private:
	int **originalArray; // original array from file
	int originalArrayRows; // original row size
	int originalArrayColumns; //original column size
	//////////////
	int arrayRows; //original row size + 2 for the outer grid
	int arrayColumns;//original column size + 2 for the outer grid
	//////////
	int **curr; //current array
	int **next; //next array for copying purposes
	///////////
	char cDM; // for checking if you are playing classic, doughnut, or mirror mode!
	char pEO; //for checking if you will be using either pause, play, or output!
	///////////
	float density; // for random generation of a grid based on the dimensions and density input
	std::string outputFileString; // output stream name
	std::ofstream outputFileStream; // output stream 
	//////////
	std::string inputFileString; // input string name
	std::ifstream inputFileStream; // input stream
	//////////
	bool readFile; //checks to see if reading from a file.
	bool oArrayExists; //checks to see if the original array exists.
	//////////
	int whichGen; //keeps track of the generation
	//////////
	int numOfX; //number of X's on the grid, for checking whether to stop the program.
	
	



};
#endif


