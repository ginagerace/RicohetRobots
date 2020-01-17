/*-------------------------------------------------------------------------------------
   ggerac3prog6.cpp
   
   *used Reed's code*
        Play the game of Ricochet Robots, similar
        to that seen online at: http://www.braunston.com/kevin/rrobot/rrobot.html
        This version uses a class to store the board.
 
   Author: Gina Gerace
   Class: CS 141, Spring 2018
   Lab: Ashour Dankha, Tues. 11:00 AM
   System: Dev-C++ on a Windows
 
   There are a few tricky aspects to keep track of:
   1. A robot cannot move ontop of another robot.
   2. A robot (numbered 1..4) that is not the goal robot can move on top of the destination
      letter.  If it does, then the letter disappears.  Once non-goal-robot moves off,
      then the goal letter must reappear.
 
  Sample run of the program:
        Author: Dale Reed
        Program 4: RicoRobots in C++
        TA: Billie Joe Armstrong, T 6:00 AM
        March 22, 2018
        Welcome to Ricochet Robots
        ('Ricochet Robot' is a registered trademark of Hans im Glück
        Munich, Germany, 1999. The game was created by Alex Randolph.)

        The object of the game is to get the designated numbered robot
        to the indicated letter position.
        The numbered squares are all robots.  They unfortunately have
        no brakes, and so will continue in whatever direction they are
        moving until they encountar an obstacle.
        For each move enter the robot number and the desired direction.
        For instance entering
           1 U
        would move the #1 robot up as far as it can go.
        The first letter of input is the robot number (1 - 4),
        and the second letter is the direction:
          (L=left, U=up, R=right, D=down)
        Enter x to exit.  Have fun!

        Enter 'r' for random robot and goal, 'd' for default or 's' to select: d
        Move robot 2 to square M
          ----------------------------------------------------------------
         | .   .   .   .   . | .   .   .   .   .   . | .   .   .   .   .  |
         |                                                                |
         | .   .   . | .   .   .   .   .   . | .   .   .   .   .   .   .  |
         |        ---                         ---                 ---     |
         | .   .   .   .   .   .   .   .   .   .   .   .   .   .   . | .  |
         |                                                                |
         | . | .   .   .   .   .   .   .   .   .   .   .   .   .   .   .  |
         |    ---                 ---                                     |
         | .   .   .   .   .   . | .   .   .   .   . | .   .   .   .   .  |
         |---                                     ---                 --- |
         | .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   4  |
         |                    ---                         ---             |
         | .   .   .   .   .   . | .   .   .   .   .   . | .   .   .   .  |
         |                            --- ---                             |
         | .   .   .   . | .   .   . | .   . | .   .   .   .   .   .   .  |
         |            ---                                                 |
         | .   .   .   .   .   .   . | .   . | .   .   .   .   .   .   .  |
         |    ---             ---     --- ---                             |
         | .   . | .   .   . | .   .   .   .   .   .   .   .   .   .   .  |
         |                                                            --- |
         | .   .   .   .   .   .   .   .   . | .   .   .   .   .   .   .  |
         |---                             ---                 ---         |
         | .   .   .   .   .   .   .   .   .   .   .   .   . | 3   .   .  |
         |                                                                |
         | .   .   .   .   .   .   M | .   .   .   .   .   .   .   .   .  |
         |                        ---                                     |
         | .   .   .   .   .   .   .   .   . | .   .   .   .   .   .   .  |
         |                                    ---                 ---     |
         | .   . | .   .   .   .   .   .   .   .   .   .   .   .   1 | .  |
         |        ---                                                     |
         | .   .   .   .   .   . | .   .   .   .   .   . | .   .   .   2  |
          ----------------------------------------------------------------

        1. Please enter the robot to move and the direction (e.g. 2 r): 2u

        Move robot 2 to square M
          ----------------------------------------------------------------
         | .   .   .   .   . | .   .   .   .   .   . | .   .   .   .   .  |
         |                                                                |
         | .   .   . | .   .   .   .   .   . | .   .   .   .   .   .   .  |
         |        ---                         ---                 ---     |
         | .   .   .   .   .   .   .   .   .   .   .   .   .   .   . | .  |
         |                                                                |
         | . | .   .   .   .   .   .   .   .   .   .   .   .   .   .   .  |
         |    ---                 ---                                     |
         | .   .   .   .   .   . | .   .   .   .   . | .   .   .   .   .  |
         |---                                     ---                 --- |
         | .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   4  |
         |                    ---                         ---             |
         | .   .   .   .   .   . | .   .   .   .   .   . | .   .   .   .  |
         |                            --- ---                             |
         | .   .   .   . | .   .   . | .   . | .   .   .   .   .   .   .  |
         |            ---                                                 |
         | .   .   .   .   .   .   . | .   . | .   .   .   .   .   .   .  |
         |    ---             ---     --- ---                             |
         | .   . | .   .   . | .   .   .   .   .   .   .   .   .   .   .  |
         |                                                            --- |
         | .   .   .   .   .   .   .   .   . | .   .   .   .   .   .   2  |
         |---                             ---                 ---         |
         | .   .   .   .   .   .   .   .   .   .   .   .   . | 3   .   .  |
         |                                                                |
         | .   .   .   .   .   .   M | .   .   .   .   .   .   .   .   .  |
         |                        ---                                     |
         | .   .   .   .   .   .   .   .   . | .   .   .   .   .   .   .  |
         |                                    ---                 ---     |
         | .   . | .   .   .   .   .   .   .   .   .   .   .   .   1 | .  |
         |        ---                                                     |
         | .   .   .   .   .   . | .   .   .   .   .   . | .   .   .   .  |
          ----------------------------------------------------------------

        2. Please enter the robot to move and the direction (e.g. 2 r):
  -------------------------------------------------------------------------------------
 */

#include <iostream>
#include <cstring>      // for getline
#include <cstdlib>      // for the system command
#include <cctype>       // For the letter checking functions, e.g. toupper( )
#include <fstream>      // For file input and output
#include <ctime>        // For time()
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

class Board
{
    public:
        // Constructors
        Board() {
            // Create the default board values, and walls around the borders.
            for( int i=0; i<BOARD_SIZE; i++) {
                theBoard[ i][ PIECE]= '.';    // Set each playing piece default
                // set the default wall values to be blank
                theBoard[ i][ LEFT]= ' ';
                theBoard[ i][ ABOVE]= ' ';
                theBoard[ i][ RIGHT]= ' ';
                theBoard[ i][ BELOW]=  ' ';
                
                // reset the edge pieces
                // reset the left wall if piece is on left edge
                if( (i % BOARD_EDGE) == 0) {
                    theBoard[ i][ LEFT]= '|';
                }
                // reset the above wall if piece is on top edge
                if( i < BOARD_EDGE) {
                    theBoard[ i][ ABOVE]= '-';
                }
                // reset the right wall if piece is on right edge
                if( ((i+1) % BOARD_EDGE) == 0) {
                    theBoard[ i][ RIGHT]= '|';
                }
                // reset the below wall if piece is on bottom edge
                if( i >= (BOARD_SIZE - BOARD_EDGE) ) {
                    theBoard[ i][ BELOW]= '-';
                }
            }//end for( int i...
        }//end Board()
    
        // Getters / Setters
        void setPieceAt( int index, char c) { theBoard[ index][ PIECE] = c; }
        void setBorderAt( int index, int direction, char c) { theBoard[ index][ direction] = c; }
        void setRobotAt( int index, int value) { theRobots[ index] = value; }
        void setGoalRobot( int robotValue) { goalRobot = robotValue; }
        void setDestinationLetter( char c) { destinationLetter = c; }
        void setGoalPosition( int thePosition) { goalPosition = thePosition; }
        void setNumberOfDestinationPieces( int theNumber) { numberOfDestinationPieces = theNumber; }
    
        char getPieceAt( int index) { return theBoard[ index][ PIECE]; }
        char getBorderAt( int index, int direction) { return theBoard[ index][ direction]; }
        int  getRobotAt( int index) { return theRobots[ index]; }
        int  getGoalRobot() { return goalRobot; }
        int  getGoalRobotIndex() { return theRobots[ goalRobot]; }
        char getDestinationLetter() { return destinationLetter; }
        int  getGoalPosition() { return goalPosition; }
        int  getNumberOfDestinationPieces() { return numberOfDestinationPieces; }
    
        // Utility functions
        void readFromFileAndModifyBoard();
        void display();
        void findGoalPosition();   // Get the index of the letter for the winning position
    
    private:
        // theBoard itself is represented by a one-dimensional array.
        // The other entries are used to keep track of walls.  Each row
        // in theBoard array will contain the character to be displayed,
        // followed by any "walls" to be displayed around the displayed
        // character.  For instance the first couple of entries are be:
        //
        //       PIECE   LEFT ABOVE RIGHT BELOW
        //      ---0---  --1-  --2-  --3-  --4-
        //    0    .       |     _
        //    1    .             _
        //   ...
        //   255   .                   |     _
        //
        char theBoard[ BOARD_SIZE][ NUMBER_OF_ELEMENTS];
        // Declare the 4 robots, which will store the board position of where they are found
        // Robots are displayed using values 1-4.  We declare 5 robots, though we will never use
        // the 0th robot in the array, so that we can use the robot digit itself as the index.
        int theRobots[ NUMBER_OF_ROBOTS + 1] = {0,0,0,0,0};
        int goalRobot;                  // the robot that needs to reach the goal
        char destinationLetter;         // the goal letter
        int goalPosition;               // Index position of the goal letter
        int numberOfDestinationPieces;  // Number of destination pieces.  Value comes from the data file.
};


//-------------------------------------------------------------------------------------
// readFromFileAndModifyBoard() - Read from data file, updating board accordingly
//
void Board::readFromFileAndModifyBoard()
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
            theBoard[ pieceNumber][ position] = c;
        }
        pInputLine++;

        // See if there is a piece letter still to be read on this input line.
        // Do this by finding the end of the line, and seeing the length of the string
        // after that.
        // An inputline sample for piece 18 would be:
        // 18 00|- A
        if( strlen( pInputLine) > 0) {
            sscanf( pInputLine, " %c", &theBoard[ pieceNumber][ PIECE]);
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
        theBoard[ theRobots[ i]][ PIECE] = (char)('0'+i);     // record the robot number in place on board
    }
    
    inStream.close();         // close the input file stream
}//end Board::readFromFileAndModifyBoard()


//-------------------------------------------------------------------------------------
// Display the Board
//
void Board::display( )
{
    // display the top edge
    cout << "  ---------------------------------------------------------------- " << endl;
    
    // display the "body" of the board
    for( int i=0; i<BOARD_SIZE; i++) {
        // Figure out what character should be displayed to the left.  It will
        // be a wall if the current spot has a left wall, or if the spot to the
        // left has a right wall.
        
        char leftCharacter = theBoard[ i][ LEFT];   // set left display char
        // See if the piece to the left has a right wall.  Don't do this for the
        // first piece on the board, since it has no left neighbor.
        if ( (i>0) && (theBoard[ i-1][ RIGHT] != ' ')) {
            leftCharacter = theBoard[ i-1][ RIGHT];
        }
        cout << " " << leftCharacter << " " << theBoard[ i][ PIECE];
        // see if we're at the end of a row
        if( ((i+1) % BOARD_EDGE) == 0) {
            // we are at the end of a row, so display right wall and go to next line
            cout << "  " << theBoard[ i][ RIGHT] << endl;
            // Now display any walls immediately below the line of pieces just displayed
            // Backup our index counter j to the beginning of this line again, to find any
            // walls displayed below this line.  Don't do it for the bottom row though.
            if( i < BOARD_SIZE - BOARD_EDGE) {
            
                cout << " |";       // display the left boundary
                for( int j=i-BOARD_EDGE+1; j<(i+1); j++) {
                    // Set the character to be displayed.  This is a wall if the
                    // current spot has a wall below, or if the spot below has a wall
                    // above.
                    char belowCharacter = theBoard[ j][ BELOW];
                    // Only check the square below if we're NOT on the bottom row
                    if ( (j<(BOARD_SIZE - BOARD_EDGE)) &&      // verify not on bottom row
                        (theBoard[ j+16][ ABOVE] != ' ')) {    // piece below has wall above
                        belowCharacter = theBoard[ j+16][ ABOVE];
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
}//end Board::display()


//-------------------------------------------------------------------------------------
// findGoalPosition()
//       Find the index of the goal letter.  This is used to mark the position where the
//       goal letter must be redisplayed in the case (probably rare) where a non-goal
//       robot passes over the goal letter, blanking it out.
//
void Board::findGoalPosition()
{
    for( int i=0; i<BOARD_SIZE; i++) {
        if( theBoard[ i][ PIECE] == destinationLetter) {
            // found the position where the destination letter is, so return it
            goalPosition = i;
            return;
        }
    }//end for( int i...
    
    // Should never have gotten here, so display error message
    cout << "*** Error, destination letter position not found.  Exiting program...";
    exit( -1);   // exit program
}//end Board::findGoalPosition()


//-------------------------------------------------------------------------------------
void displayIdentifyingInformationAndInstructions()
{
    // Display identifying information
    cout << "Author: Gina Gerace                   " << endl
         << "Program 6: RicoRobots with Undo         " << endl
         << "TA: Ashour Dankha, T 11:00 AM  " << endl
         << "April 27, 2018                       " << endl;

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


//-------------------------------------------------------------------------------------
// chooseRandomRobotAndDestination() - choose a robot at random, and a destination at random
//
void chooseRandomRobotAndDestination( Board &theBoard)
{
    srand( (int)time(0));        // Seed the random number generator with time(), to give varying results.
    
    int randomNumber = rand()%4;    // get random number from 0 to 3
    theBoard.setGoalRobot( randomNumber + 1);   // set random robot to be some value between 1 - 4
    
    // get random number from 0 to numberOfDestinationPieces
    randomNumber = rand() % theBoard.getNumberOfDestinationPieces();
    // add this number to 'A' to set the destination character
    theBoard.setDestinationLetter( 'A' + randomNumber);
}// end chooseRandomRobotAndDestination()


//-------------------------------------------------------------------------------------
// canMove( )
//      See if the robot can move in the desired direction.
//
bool canMove(
        Board theBoard,           // the board
        char robot,               // the robot to be moved
        int directionOffset,      // Offset value to use in moving robot
        char moveDirection)       // Move direction 'L','U','R' or 'D'for left, up, right, down
{
    // find neighbor location
    int theNeighborIndex = theBoard.getRobotAt( robot-'0') + directionOffset;
    
    // verify that we're not out-of-bounds before we use robot position to check board array
    if( (theNeighborIndex < 0) || (theNeighborIndex >= BOARD_SIZE)) {
        return false;     // attempting to move out of bounds, which is invalid
    }
    
    // See if we can move in the desired direction of travel.  For each direction we must check for
    //      1. a wall in the piece we are moving from
    //      2. a wall in the piece we are moving to
    // If any wall is found, return false.
    int theRobotIndex = theBoard.getRobotAt( robot-'0');
    switch( moveDirection) {
        case 'L':  if( (theBoard.getBorderAt( theRobotIndex, LEFT) != ' ') ||
                       (theBoard.getBorderAt( theNeighborIndex, RIGHT) != ' ')
                     )
                    return false;   // we can't make the move
                    break;
        case 'U':  if( (theBoard.getBorderAt( theRobotIndex, ABOVE) != ' ') ||
                       (theBoard.getBorderAt( theNeighborIndex, BELOW) != ' ')
                     )
                    return false;   // we can't make the move
                    break;
        case 'R':  if( (theBoard.getBorderAt( theRobotIndex, RIGHT) != ' ') ||
                       (theBoard.getBorderAt( theNeighborIndex, LEFT) != ' ')
                     )
                    return false;   // we can't make the move
                    break;
        case 'D':  if( (theBoard.getBorderAt( theRobotIndex, BELOW) != ' ') ||
                       (theBoard.getBorderAt( theNeighborIndex, ABOVE) != ' ')
                     )
                    return false;   // we can't make the move
                    break;
        default: cout << "*** Error, invalid check for neighbor in canMove(). Exiting...\n";
                    exit( -1);      // exit the program
    }
    
    // Verify that the neighbor in the direction of travel is not also the location of
    // one of the other robots.
    char neighborPiece = theBoard.getPieceAt( theNeighborIndex);      // Make copy of neighbor board piece
    // ensure destination doesn't contain a robot character, which is '1'..'4'
    // Convert NUMBER_OF_ROBOTS to a char by adding it to char '0'
    if( (neighborPiece >= '1') && (neighborPiece <= NUMBER_OF_ROBOTS+'0')) {
        return false;  // destination has another robot, so can't move there.
    }
    
    return true;       // passed all the tests, so move is valid
}//end method canMove()


//-------------------------------------------------------------------------------------
// blankOutSourcePosition( )
//     Put the default character in the square we're moving from.
//     One other check must be made.  If a robot (which shouldn't be the goal robot)
//     is moving OFF of the goal square, we must re-display the goal square letter.
void blankOutSourcePosition(
            Board &theBoard,    // The board
            int robotIndex)     // Board position where robot is
{
    int goalPosition = theBoard.getGoalPosition();                // Board index of winning move position
    char destinationLetter =  theBoard.getDestinationLetter();    // Letter for winning move position
    
    if( robotIndex != goalPosition) {
        theBoard.setPieceAt( robotIndex, '.');
    }
    else {
        theBoard.setPieceAt( robotIndex, destinationLetter);
    }
}


//-------------------------------------------------------------------------------------
// Blank out all letters except the destination letter
void blankOutAllLettersExceptDestinationLetter( Board &theBoard)
{
    for( int i=0; i<BOARD_SIZE; i++) {
        // Clear off the alphabetic squares, except for the destination square
        if( isalpha( theBoard.getPieceAt( i)) &&
            (theBoard.getPieceAt( i) != theBoard.getDestinationLetter() )
          ) {
            theBoard.setPieceAt( i, '.');      // set piece at position i to the default character
        }
    }
}


//-------------------------------------------------------------------------------------
// Given the user input of 'r' for random robot and goal, 'd' for default or 's' to select,
// set the robot to be used and the destination letter.
void setRobotAndGoal( Board &theBoard)
{
    // Prompt for robot and goal letter configuration to be used
    char userResponse;
    cout << "Enter 'r' for random robot and goal, 'd' for default or 's' to select: ";
    cin >> userResponse;
    userResponse = toupper( userResponse);
    
    if( userResponse == 'R') {
        // choose a random robot and random destination
        chooseRandomRobotAndDestination( theBoard);
    }
    else if( userResponse == 'D') {
        // Use default values for the goalRobot and destination. This makes the program consistent
        // for the sake of debugging.
        theBoard.setGoalRobot( 2);
        theBoard.setDestinationLetter( 'M');
    }
    else if (userResponse == 'X'){
		exit(0);
	}
    else {
        theBoard.display();
        cout << "Enter the goal robot number and the destination letter: ";
        int theGoalRobot;
        char theDestinationLetter;
        cin >> theGoalRobot >> theDestinationLetter;
        theBoard.setGoalRobot( theGoalRobot);
        theBoard.setDestinationLetter( toupper( theDestinationLetter));
    }
    
    // Find which square has the goal letter in it. Store this to use in redisplaying the goal letter
    // if a non-goal robot passes over it.
    theBoard.findGoalPosition();
    
    // Blank out all the letters except the destination letter, to make playing the game more clear
    blankOutAllLettersExceptDestinationLetter( theBoard);
}//end setRobotAndGoal()


//-------------------------------------------------------------------------------------
// Move the selected robot in the direction indicated, moving as far as it can go until
// it hits some obstacle of a wall or another robot.
//
void moveRobotInIndicatedDirection(
        Board &theBoard,        // the board
        char robot,             // the robot, as a character '1'..'4'
        int directionOffset,    // Number indicating offset to add to index to make move
        char moveDirection)     // Letter for move direction 'L','U','R', or 'D'
{
    while( canMove( theBoard, robot, directionOffset, moveDirection)) {
        // Find position of robot
        int robotIndex = theBoard.getRobotAt( robot-'0');
        // blank out where robot is moving from
        blankOutSourcePosition( theBoard, robotIndex);
        // clear screen
		//system("clear");  // "clear" for unix, "cls" for windows.
                        // This only works when running it from the command line.
        
        // store robot in new location
        theBoard.setPieceAt( robotIndex + directionOffset, robot);
        // update robot index position.  Must subtract '0' from robot since it's a char
        theBoard.setRobotAt( robot-'0', robotIndex + directionOffset);
    }//end while( canMove...
    
}//end moveRobotInIndicatedDirection()

// struct to create a linked list
struct Node {
	Board theBoard;
	int moveNumber;
	Node *pNext;
}; //end struct Node

// function to append a node to the list
void addNodeToList(Node *&pHead, Board theBoard, int moveNumber){
	//create a temporary node to store the information of the head
	//add the new node to the start of the list and have it point to the temp node
	Node *pTemp = new Node;
	pTemp->theBoard = theBoard;
	pTemp->moveNumber = moveNumber;
	pTemp->pNext = pHead;
	pHead = pTemp;   
}//end addNodeToList()

// function to traverse the list and display current move number
void displayList(Node *pHead, Board theBoard) {
	cout << pHead->moveNumber << ". List: ";
	while(pHead != NULL) {
		cout << (pHead->moveNumber);
		if(pHead->moveNumber != 1) {
			cout << "->";
		}
		pHead = pHead->pNext;		//advance to the next node
	}
	cout << endl << "   Robots: ";
	for (int robot=1; robot<=4; robot++) {
		cout << theBoard.getRobotAt(robot) << " ";
	}
	cout << endl << "   Enter robot to move and direction (e.g. 2 r), x to exit or b to backup: " ;
}//end displayList()

// function to delete the most recent move from the list
void deleteNodeFromList(Node *&pHead, Board &theBoard, int &moveNumber) {
	if (pHead->moveNumber == 1) {
		cout << "*** You cannot undo past the beginning of the game.  Please retry. ***" << endl;
	}
	else {
		cout << "* Undoing move *" << endl;
		Node *pTemp = new Node;
		pTemp = pHead;
		pHead = pHead->pNext;
		delete pTemp;
	}
	theBoard = pHead->theBoard;
	moveNumber = pHead->moveNumber;
}//end deleteNodeFromList()

//-------------------------------------------------------------------------------------
// main() - main part of program, that drives everything else
//
int main()
{
	//check if user wants the board and instructions displayed or not
	bool displayBoards = false;
	char choice;
	cout << "Enter T for true or F for false to indicate if boards and instructions will be displayed: ";
	cin >> choice;
	if((choice == 't') || (choice == 'T')) {
		displayBoards = true;
	}
	
	if(displayBoards){
    	displayIdentifyingInformationAndInstructions();
	}
    
	// Create and initialize the board
    Board theBoard;
    theBoard.readFromFileAndModifyBoard(); // read from the datafile, updating board
    
    // Set the robot and goal to be used, depending on the user's choice
    setRobotAndGoal( theBoard);
    
	if(displayBoards){
	    cout << "Move robot " << theBoard.getGoalRobot() << " to square " << theBoard.getDestinationLetter() << endl;
    	theBoard.display();
	}

    int moveNumber = 1;          // track how many moves have been made
    char robot = ' ';            // user entry for robot to move
    char moveDirection = ' ';    // direction in which to move (L, U, R, or D)
    int directionOffset = 0;     // value to add to current robot position to reflect move direction
       
    // create the first node
    Node *pHead = NULL;									
    addNodeToList(pHead, theBoard, moveNumber);
	 
    // infinite loop to play the game
    while( true) {
		displayList(pHead, theBoard);
        cin >> robot;
        if( toupper( robot) == 'X') {
            break;       // exit program
        }
        if( toupper( robot) == 'B') {
        	deleteNodeFromList(pHead, theBoard, moveNumber);	//call undo function
			continue;
    	}
        cin >> moveDirection;
        moveDirection = toupper( moveDirection);   // fold into upper-case
        // ensure robot values were in range
        if( (robot < '1') || (robot > NUMBER_OF_ROBOTS+'0')) {
            cout << "Invalid robot value, please retry." << endl;
            continue;  // continue up to the user input loop again
        }
        
        // Find the directionOffset for robot change in position
        switch( moveDirection) {
            case 'L': directionOffset = -1; break;
            case 'U': directionOffset = -BOARD_EDGE; break;
            case 'R': directionOffset = 1; break;
            case 'D': directionOffset = BOARD_EDGE; break;
            default: cout << "*** Error, invalid direction.  Retry Input. \n" << endl;
                continue;  // continue up to the user input loop again
        }
        
        // Make the move for this particular robot and direction
        moveRobotInIndicatedDirection( theBoard, robot, directionOffset, moveDirection);
        
        if(displayBoards){
        	// display board
       		 cout << "Move robot " << theBoard.getGoalRobot() << " to square " << theBoard.getDestinationLetter() << endl;
       		 theBoard.display();
        }
        
		// Update number of moves
        moveNumber++;
        
        // add move to the list
        addNodeToList(pHead, theBoard, moveNumber);
        
        // See if we've arrived at destination.  We've arrived if the robot just moved
        // was the goal robot, and it's location is the goal position
        if( ((robot-'0') == theBoard.getGoalRobot() ) &&
            (theBoard.getRobotAt( robot-'0') == theBoard.getGoalPosition() )
          ) {
            cout << "Great Job!  You did it in only " << moveNumber << " moves." << endl;
            break;         // break from endless loop making moves
        }

    }//end while( true...
    
    // pause output
    cout << "Exiting program..." << endl << endl;
    getchar();
    
}//end main()

