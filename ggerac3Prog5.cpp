/* ------------------------------------------------
   ggerac3Prog5.cpp
 
   Program #5: Ricochet Robots: Allow solving the sliding robots puzzle
   Class: CS 141
   Author: Gina Gerace
   Lab: Tues 11am
   System:  C++ Windows Dev-C++

   Grading Rubric:

   55 Execution points
        2 Displays header info and instructions on screen when run
        3 Displays the board (Since I'm giving you all the code for this...)
        5 Allows selecting default values (robot 2 to square M), random values, or user-selected values.
       15 Allows making moves, displaying move numbers.  Input can be upper or lower case, and can have spaces or not.
       20 Robots stop at walls and don't run over each other
        5 Game stops and message is given when goal robot makes it to the goal square.
        5 If some robot besides robot 2 goes to the destination square (square M in this case), the destination square should change to show the robot there. When this robot moves away, the square should go back to displaying the letter that was there previously (M in our case.)

   45 Programming Style (Given only if program runs substantially correctly)
         5 Program naming convention is followed
         5 Meaningful identifier names
         5 Comments: Has header and this rubric.  Has comments on each block of code
        20 Appropriate data and control structures. Is implemented using classes.
        10 Code Layout: Appropriate indentation and blank lines
   ------------------------------------------------
*/

#include <iostream>
#include <cstring>      // for getline
#include <cstdlib>      // for the system command
#include <cctype>       // For the letter checking functions, e.g. toupper( )
#include <fstream>      // For file input and output
#include <cstdlib>      // For random number generator
#include <time.h>		// For using time to get a random number
using namespace std;

// Global data structure for board
const int BOARD_EDGE = 16;
const int BOARD_SIZE = BOARD_EDGE * BOARD_EDGE;
const int NUMBER_OF_ROBOTS = 4;
// declare constants to later use instead of numbers to select values from theBoard
const int NUMBER_OF_ELEMENTS = 5;   // Number of elements for each piece, enumerated below
const int PIECE = 0;    // to reference the character, such as in: theBoard[ i][ PIECE]
const int LEFT = 1;     // to reference the left wall character, such as in: theBoard[ i][ LEFT]
const int ABOVE = 2;    // to reference the above wall character, such as in: theBoard[ i][ ABOVE]
const int RIGHT = 3;    // to reference the right wall character, such as in: theBoard[ i][ RIGHT]
const int BELOW = 4;    // to reference the below wall character, such as in: theBoard[ i][ BELOW]


void displayIdentifyingInformationAndInstructions()
{
    // Display identifying information
    cout << "Author: Gina Gerace                    " << endl
         << "Program 5: RicoRobots in C++         " << endl
         << "TA: Ashour Dankha, Tues. 11:00 AM  " << endl
         << "April 11, 2018                       " << endl;

    // Display Instructions
    cout << "Welcome to Ricochet Robots                                     " << endl
         << "(\'Ricochet Robot\' is a registered trademark of Hans im Glück " << endl
         << "Munich, Germany, 1999. The game was created by Alex Randolph.) " << endl
         << endl
         << "The object of the game is to get the designated numbered robot " << endl
         << "to the indicated letter position.                              " << endl
         << "The numbered squares are all robots.  They unfortunately have  " << endl
         << "no brakes, and so will continue in whatever direction they are " << endl
         << "moving until they encountar an obstacle.                       " << endl
         << "For each move enter the robot number and the desired direction." << endl
         << "For instance entering                                          " << endl
         << "   1 U " << endl
         << "would move the #1 robot up as far as it can go.                " << endl
         << "The first letter of input is the robot number (1 - 4),         " << endl
         << "and the second letter is the direction:                        " << endl
         << "  (L=left, U=up, R=right, D=down)                              " << endl
         << "Enter x to exit.  Have fun!                                    " << endl
         <<  endl;
}//end displayIdentifyingInformationAndInstructions()


// class to store the information of each position on the board
class Position 
{
	public:
		// Constructor
		Position(char thePiece, char theLeft, char theAbove, char theRight, char theBelow) 
		{
			this->piece = thePiece;
			this->left = theLeft;
			this->above = theAbove;
			this->right = theRight;
			this->below = theBelow;
		}
		
		// Default Constuctor
		Position()
		{
			this->piece = ' ';
			this->left = ' ';
			this->above = ' ';
			this->right = ' ';
			this->below = ' ';
		}
		
		// Get member functions
		char getPiece() {return piece;}
		char getLeft()  {return left;}
		char getAbove() {return above;}
		char getRight() {return right;}
		char getBelow() {return below;}
		
		// Set member functions
		void setPiece(char thePiece) {piece = thePiece;}
		void setLeft(char theLeft)   {left = theLeft;}
		void setAbove(char theAbove) {above = theAbove;}
		void setRight(char theRight) {right = theRight;}
		void setBelow(char theBelow) {below = theBelow;}
	
	// declare private variables
	private:
		char piece, left, above, right, below;
		
};//end Position class


// Function to create the board by initializing all the display characters
void createBoard( Position theBoard[ BOARD_SIZE])
{
    for( int i=0; i<BOARD_SIZE; i++) {
        theBoard[i].setPiece('.');    // Set each playing piece default
        // set the default wall values to be blank
        theBoard[i].setLeft(' ');
        theBoard[i].setAbove(' ');
        theBoard[i].setRight(' ');
        theBoard[i].setBelow(' ');
        
        // reset the edge pieces
        // reset the left wall if piece is on left edge
        if( (i % BOARD_EDGE) == 0) {
            theBoard[i].setLeft('|');
        }
        // reset the above wall if piece is on top edge
        if( i < BOARD_EDGE) {
            theBoard[i].setAbove('-');
        }
        // reset the right wall if piece is on right edge
        if( ((i+1) % BOARD_EDGE) == 0) {
            theBoard[i].setRight('|');
        }
        // reset the below wall if piece is on bottom edge
        if( i >= (BOARD_SIZE - BOARD_EDGE) ) {
            theBoard[i].setBelow('-');
        }
    }
    
}//end createBoard()


// Function to read from data file and update board accordingly
void readFromFileAndModifyBoard(
        Position theBoard[BOARD_SIZE],
        int theRobots[ ],
        int &numberOfDestinationPieces)
{
    int numberOfSpecialSquares;  // Read from file, denotes number of pieces with some kind of wall
    string inputLine;            // Input line from file
    int pieceNumber;             // pieceNumber for each square defined in data file
    char c;
    
    ifstream inStream;           // declare an input file stream
    inStream.open("board.txt");  // Open input file, associating the actual file name with "inStream"
    if ( inStream.fail() ) {
        cout << "Input file opening failed.  Exiting...\n\n";
        exit(-1);
    }
    
    // Read from file one line at a time.  First read the top three data file lines which are documentation.
    getline( inStream, inputLine);
    getline( inStream, inputLine);
    getline( inStream, inputLine);
    
    inStream >> numberOfDestinationPieces;      // read how many destination pieces there are
    inStream >> numberOfSpecialSquares;         // number of square with walls around them somewhere
    inStream.get( c);                           // Get rid of return character at end of current line
                                                // to get ready for reading a line at a time below
    
    // process the special squares, updating the board
    for( int i=0; i<numberOfSpecialSquares; i++) {
        getline( inStream, inputLine);
        char *pInputLine = &inputLine[0];
        // Extract the piece number from the input line array
        sscanf( pInputLine, "%d", &pieceNumber);
        // Advance the inputLine pointer to the space after the number
        pInputLine = strchr( pInputLine, ' ');

        // Read the information on whether or not there is each of the potential 4 walls.
        // The four values read correspond in order to the pieces on all four sides,
        // which are defined as global constants for the values LEFT=1, ABOVE=2, RIGHT=3, BELOW=4
        for( int position=1; position<=4; position++) {
            pInputLine++;   // advance to next character to be read
            sscanf( pInputLine, " %c", &c);         // Read the next potential wall character
            // Convert it to a blank if it was '0'.  '0' was left in input file to make it easier to read.
            if( c=='0') {
                c = ' ';
            }
            else if(position == 1)
            	{theBoard[pieceNumber].setLeft(c);}
			else if(position == 2)
            	{theBoard[pieceNumber].setAbove(c);}      
			else if(position == 3)
            	{theBoard[pieceNumber].setRight(c);}   
			else if(position == 4)
            	{theBoard[pieceNumber].setBelow(c);}   
        }
        pInputLine++;

        // See if there is a piece letter still to be read on this input line.
        // Do this by finding the end of the line, and seeing the length of the string
        // after that.
        char letter;
       	if(strlen( pInputLine) > 0) {
		   for(int i=0; i<inputLine.length(); i++) {
			   letter = inputLine.at(i);
			   if(isalpha(letter)){
	       			theBoard[pieceNumber].setPiece(letter);
				}
			}
	 	}
    }//end for( int i...
    
    // At the end of the data file read the information on the location of the robots, updating the board.
    char junk[80];           // used to read and discard input file information
    // Loop starts counting from 1 (rather than 0), since we ignore the 0th position
    // of the robots array, so that robot numbers correspond to what is shown
    // on the board.
    for( int i=1; i<=NUMBER_OF_ROBOTS; i++) {
        inStream >> theRobots[ i];
        inStream.getline( junk, '\n');    // discard rest of line, which is color information, if using graphics
        // set robot on board, converting the integer value to a character
        theBoard[theRobots[ i]].setPiece((char)('0'+i));     // record the robot number in place on board
    }
    
    inStream.close();         // close the input file stream
}//end readFromFileAndModifyBoard()


// Function to display the board
void displayTheBoard( Position theBoard[BOARD_SIZE])
{
    // display the top edge
    cout << "  ---------------------------------------------------------------- " << endl;
    
    // display the "body" of the board
    for( int i=0; i<BOARD_SIZE; i++) {
        // Figure out what character should be displayed to the left.  It will
        // be a wall if the current spot has a left wall, or if the spot to the
        // left has a right wall.
        
        char leftCharacter = theBoard[i].getLeft();   // set left display char
        // See if the piece to the left has a right wall.  Don't do this for the
        // first piece on the board, since it has no left neighbor.
        if ( (i>0) && (theBoard[i-1].getRight() != ' ')) {
            leftCharacter = theBoard[i-1].getRight();
        }
        cout << " " << leftCharacter << " " << theBoard[i].getPiece();
        // see if we're at the end of a row
        if( ((i+1) % BOARD_EDGE) == 0) {
            // we are at the end of a row, so display right wall and go to next line
            cout << "  " << theBoard[i].getRight() << endl;
            // Now display any walls immediately below the line of pieces just displayed
            // Backup our index counter j to the beginning of this line again, to find any
            // walls displayed below this line.  Don't do it for the bottom row though.
            if( i < BOARD_SIZE - BOARD_EDGE) {
            
                cout << " |";       // display the left boundary
                for( int j=i-BOARD_EDGE+1; j<(i+1); j++) {
                    // Set the character to be displayed.  This is a wall if the
                    // current spot has a wall below, or if the spot below has a wall
                    // above.
                    char belowCharacter = theBoard[j].getBelow();
                    // Only check the square below if we're NOT on the bottom row
                    if ( (j<(BOARD_SIZE - BOARD_EDGE)) &&      // verify not on bottom row
                        (theBoard[j+16].getAbove() != ' ')) {    // piece below has wall above
                        belowCharacter = theBoard[j+16].getAbove();
                    }
                    for( int i=0; i<3; i++) {
                       cout << belowCharacter;        // display the character
                    }
                    // display extra spaces, if we're not at the end of a row
                    if( ((j+1) % BOARD_EDGE) != 0) {
                        cout << " ";
                    }
                }//end for( int j...
                cout << " |" << endl;       // display the right boundary
            }//end if( i< BOARD_SIZE...

        }//end if( ((i+1...
        
    }//end for( int i=0;...
    
    // display the bottom edge
    cout << "  ---------------------------------------------------------------- " << endl;
    cout << endl;
}//end displayTheBoard()


// Function to set the piece back to the destination letter after the non-goal robot has moved
void resetLetter(char destinationLetter, int destinationLetterIndex, Position theBoard[BOARD_SIZE]) 
{
	if(theBoard[destinationLetterIndex].getPiece() == '.')
	{
		theBoard[destinationLetterIndex].setPiece(destinationLetter);
	}
}//end resetLetter()


// Function to see if the user has gotten the goal robot to the destination letter
bool reachedLetter(int currentRobot, int goalRobot, int destinationLetterIndex, int theRobots[5]) 
{
	int robotIndex = theRobots[currentRobot];	
	
	// returns false if it is not the correct robot
	if(currentRobot != goalRobot) 
		{return false; }
		
	else{
		if(robotIndex == destinationLetterIndex) {
			return true;
		}
	}
	
	return false;
}//end reachedLetter()


// Function to move the robot up
void movingUp(int goalRobot, char destinationLetter, int currentRobot, Position theBoard[BOARD_SIZE], int theRobots[5]) 
{	
	int robotIndex = theRobots[currentRobot];
	
	//continue until the robot hits an obstacle
	while((theBoard[robotIndex].getAbove() == ' ') && (theBoard[robotIndex-16].getBelow() == ' '))
	{	
		//checking to see if the space above already has a robot in position
		if((theBoard[robotIndex-16].getPiece() != '.') 
		  && (theBoard[robotIndex-16].getPiece() != destinationLetter))
			{break;}
		
		// To make moves you selectively change values on the board.
    	theBoard[robotIndex].setPiece('.');            // blank out where we're coming FROM
    	theRobots[currentRobot] = robotIndex - 16;     // Reset robot position index to the square above
    	robotIndex = theRobots[currentRobot];          // Get the new stored value reflecting the new position
    	// Place robot number where we're going TO.  We have to add '0' to the goal robot because the robot
    	// number is an integer, but the board stores characters
    	theBoard[robotIndex].setPiece('0'+ currentRobot);
	}	
	
}//end movingUp()


// Function to move the robot down
void movingDown(int goalRobot, char destinationLetter, int currentRobot, Position theBoard[BOARD_SIZE], int theRobots[5]) 
{	
	int robotIndex = theRobots[currentRobot];
	
	//continue until the robot hits an obstacle
	while((theBoard[robotIndex].getBelow() == ' ') && (theBoard[robotIndex+16].getAbove() == ' '))
	{	
		//checking to see if the space above already has a robot in position
		if((theBoard[robotIndex+16].getPiece() != '.') 
		  && (theBoard[robotIndex+16].getPiece() != destinationLetter))
			{break;}
		
		// To make moves you selectively change values on the board.
    	theBoard[robotIndex].setPiece('.');            // blank out where we're coming FROM
    	theRobots[currentRobot] = robotIndex + 16;     // Reset robot position index to the square above
    	robotIndex = theRobots[currentRobot];          // Get the new stored value reflecting the new position
    	// Place robot number where we're going TO.  We have to add '0' to the goal robot because the robot
    	// number is an integer, but the board stores characters
    	theBoard[robotIndex].setPiece('0'+ currentRobot);
	}	
	
}//end movingDown()


// Function to move the robot right
void movingRight(int goalRobot, char destinationLetter, int currentRobot, Position theBoard[BOARD_SIZE], int theRobots[5]) 
{	
	int robotIndex = theRobots[currentRobot];
	
	//continue until the robot hits an obstacle
	while((theBoard[robotIndex].getRight() == ' ') && (theBoard[robotIndex+1].getLeft() == ' '))
	{	
		//checking to see if the space above already has a robot in position
		if((theBoard[robotIndex+1].getPiece() != '.') 
		  && (theBoard[robotIndex+1].getPiece() != destinationLetter))
			{break;}
		
		// To make moves you selectively change values on the board.
    	theBoard[robotIndex].setPiece('.');            // blank out where we're coming FROM
    	theRobots[currentRobot] = robotIndex + 1;     // Reset robot position index to the square above
    	robotIndex = theRobots[currentRobot];          // Get the new stored value reflecting the new position
    	// Place robot number where we're going TO.  We have to add '0' to the goal robot because the robot
    	// number is an integer, but the board stores characters
    	theBoard[robotIndex].setPiece('0'+ currentRobot);
	}	
	
}//end movingRight()


// Function to move the robot left
void movingLeft(int goalRobot, char destinationLetter, int currentRobot, Position theBoard[BOARD_SIZE], int theRobots[5]) 
{	
	int robotIndex = theRobots[currentRobot];
	
	//continue until the robot hits an obstacle
	while((theBoard[robotIndex].getLeft() == ' ') && (theBoard[robotIndex-1].getRight() == ' '))
	{	
		//checking to see if the space above already has a robot in position
		if((theBoard[robotIndex-1].getPiece() != '.') 
		  && (theBoard[robotIndex-1].getPiece() != destinationLetter))
			{break;}
		
		// To make moves you selectively change values on the board.
    	theBoard[robotIndex].setPiece('.');            // blank out where we're coming FROM
    	theRobots[currentRobot] = robotIndex - 1;     // Reset robot position index to the square above
    	robotIndex = theRobots[currentRobot];          // Get the new stored value reflecting the new position
    	// Place robot number where we're going TO.  We have to add '0' to the goal robot because the robot
    	// number is an integer, but the board stores characters
    	theBoard[robotIndex].setPiece('0'+ currentRobot);
	}	
	
}//end movingLeft()


int main() 
{
	// theBoard itself is represented by a one-dimensional array.
    // The other entries are used to keep track of walls.  Each row
    // in theBoard array will contain the character to be displayed,
    // followed by any "walls" to be displayed around the displayed character.
	Position theBoard[ BOARD_SIZE];
	
	// Declare the 4 robots, which will store the board position of where they are found
    // Robots are displayed using values 1-4.  We declare 5 robots, though we will never use
    // the 0th robot in the array, so that we can use the robot digit itself as the index.
    int theRobots[ NUMBER_OF_ROBOTS + 1] = {0,0,0,0,0};

	srand(time(NULL));				// get a different random number each run
	char userIn1;					// stores the number typed in by user
	char userChar;					// stores the letter typed in by user
	int userNum;					// stores the number of the robot the user chooses
	bool isValid = false;			// used to make sure the user input is valid
    bool stillPlaying = true;		// used to end the while loop when the user has won the game
	int turnCount = 0;				// keep track of the amount of turns
    int letterIndex;				// used to store the index of the destination letter
	int goalRobot;                  // the robot that needs to reach the goal
    char destinationLetter;         // the goal letter
    int numberOfDestinationPieces;  // Number of destination pieces. 
                                    // Value comes from the data file.
                                    
    displayIdentifyingInformationAndInstructions();
    // create the board, initializing all pieces to their default settings
    createBoard( theBoard);   
	// read from the datafile, updating board
	readFromFileAndModifyBoard( theBoard, theRobots, numberOfDestinationPieces); 
	
	while(isValid == false) 
	{	
		// prompt the user to input a letter to choose mode
		cout << endl << "Enter 'r' for random robot and goal, 'd' for default or 's' to select: ";
		cin >> userChar;
		userChar = toupper (userChar);
		
		// set a goal robot and destination letter based on user input
		if(userChar == 'D') {
			// set to default game values
			goalRobot = 2;
		    destinationLetter = 'M';
		    isValid = true;
		}
		else if(userChar == 'R') {
			// randomely set the game values
			goalRobot = (rand() % NUMBER_OF_ROBOTS) + 1; 
			int num = rand() % 15;		//15 because there are 15 letters on the board to choose from
			destinationLetter = 'A' + num;
			isValid = true;
		}
		else if(userChar == 'S') {
			// user selects game values
			displayTheBoard( theBoard);
			cout << "Enter the goal robot number and the destination letter: ";
			cin >> goalRobot >> destinationLetter;
			destinationLetter = toupper (destinationLetter);
			isValid = true;
		}
		else if (userChar == 'X') {
			cout << endl << "Exiting...";
			exit(0);
		}
		else 
			{cout << "That is not a valid input, please try again" << endl; }
	}
	
	// Erase all the letters from the board besides the destination letter;
	for (int i=0; i< BOARD_SIZE; i++) {
		// clear each position if it is not a '.' or the destination letter
		if((isalpha(theBoard[i].getPiece())) && (theBoard[i].getPiece() != destinationLetter)) {
			theBoard[i].setPiece('.');  
		}
		//store the index of the destination letter
		else if(isalpha(theBoard[i].getPiece())) {
			letterIndex = i;
		}
	}

    while(stillPlaying == true) 
	{
		isValid = false;
		
    	// Print the goal and the board for user to see
		cout << endl << "Move robot " << goalRobot << " to square " << destinationLetter << endl;
		displayTheBoard( theBoard);
	
		while(isValid == false) 
		{
		    turnCount++;
		    
			// Prompt user to chose a robot and a direction to move it
			cout << turnCount << ". Please enter the robot to move and the direction (e.g. 2 r): ";
	    	cin >> userIn1;
			 
	    	// exit if user enters 'X'
	    	if ((userIn1 == 'X') || (userIn1 == 'x')) {
				cout << endl << "Exiting...";
				exit(0);
			}
			
			// convert user input to uppercase
			cin >> userChar;
	    	userChar = toupper (userChar);
			
			// get an int for the robot number
			userNum = userIn1 - '0';
			
			// make sure the user enters valid numbers
			if(((userChar=='U') || (userChar=='D') || (userChar=='L') || (userChar=='R')) &&
			   ((userNum==1) || (userNum==2) || (userNum==3) || (userNum==4)))
			   {isValid = true;}
			else 
				{cout << "That is not a valid input, please try again" << endl << endl;}
		}
		
		// call the correct function depending on which direction the user chose
		if(userChar=='U'){
			movingUp(goalRobot, destinationLetter, userNum, theBoard, theRobots);
		}
		else if(userChar=='D'){
			movingDown(goalRobot, destinationLetter, userNum, theBoard, theRobots);
		}
		else if(userChar=='R'){
			movingRight(goalRobot, destinationLetter, userNum, theBoard, theRobots);
		}
		else if(userChar=='L'){
			movingLeft(goalRobot, destinationLetter, userNum, theBoard, theRobots);
		}
		
		//make sure the destination letter reappears if robot has moved
		resetLetter(destinationLetter, letterIndex, theBoard);
		
		// check to see if the user has won
	    if(reachedLetter(userNum, goalRobot, letterIndex, theRobots)) {
	    	stillPlaying = false;
		}
	}
	
	//end game: show finished board and print winning statement
	displayTheBoard( theBoard);
	cout << endl << "Good Job! You did it in only " << turnCount << " moves." << endl;
	
	return 0;
	
} //end main()



