/* UIC CS-141 Program 5 Fall 2021
 * Author: Jakub Dejworek
 * IDE: Clion, Windows 10
 *
 *
 * Example of a scrambled board:
 *      0   1   2   3
      ---------------
   0 |   | d | n | d |
      ---------------
   1 | e | e | a | s |
      ---------------
   2 |   | t | o | u |
      ---------------
   3 | n | m |   |   |
      ---------------
 *
 */


#include <iostream>
#include <string>
#include <istream>
#include <cctype>
#include <vector>
#include <fstream>
#include <cassert>
#include <ctime>
using namespace std;

class Board{

public:
    Board(int size){ boardSize = size;}
    int getSize(){return boardSize;}
    void displayBoard(bool printScrambled);
    void generateBoard(const vector <string> &data, int piecesLeft);
    void printWords();
    void scrambler(int numOfScrambles);
    void specificScrambler(char rowOrColumn, int index, int rotationAmount);
    void moveRow(int randomRow, int scrambleAmount, int theBoardSize, string &piecesToScramble);
    void moveColumn(int randomColumn, int scrambleAmount, int theBoardSize, string &piecesToScramble );


private:
    int boardSize;
    string pieces;
    string scrambledPieces;
    vector <string> wordList;

};// end class Board
//----------------------------------------------------------------------------

// display words from the board in order
void Board ::printWords(){
    for(int i = 0; i < wordList.size(); i++){
        if(i == wordList.size()-1){
            cout << wordList.at(i) << ".";
        }
        else{
            cout << wordList.at( i) << ", ";
        }
    }
    cout << endl;
}// end printWords()
//----------------------------------------------------------------------------

void Board ::displayBoard(bool printScrambled=true) {

    string piecesToPrint;  // will either be unscrambled or scrambled pieces

    // if true prints a scrambledBoard
    if(printScrambled){
        piecesToPrint = scrambledPieces;
    }
    else{
        piecesToPrint = pieces;
    }

    int counter = 0;

    cout << "Current board:" << endl;
    cout << "       ";
    // printing column numbers
    for(int i = 0; i < boardSize; i++){
        cout << i << "   ";
    }

    // printing dashes
    cout << endl;
    cout << "      ";
    for(int x = 0; x < boardSize; x++){
        cout << "---";
    }
    for (int d = 0; d < boardSize-1; d++) {
        cout << "-";
    }
    cout << endl;

    // printing board rows
    for(int i = 0; i < boardSize; i++){
        cout << "   " << i;
        for(int j = 0; j < boardSize; j++){
                cout << " | " << piecesToPrint.at(counter);
                counter++;
        }

        cout << " |" << endl;
        cout << "      ";

        // printing dashes
        for(int x = 0; x < boardSize; x++){
            cout << "---";
        }
        for (int d = 0; d < boardSize-1; d++) {
            cout << "-";
        }
        cout << endl;

    }

   //  displaying current board words

   cout << "Current board words: " << piecesToPrint << endl;
   cout << endl;

}// end displayBoard()
//----------------------------------------------------------------------------

// adds random words onto the board until the board is full
void Board ::generateBoard(const vector <string> &data, int piecesLeft){

    string temp, word;
    int randIndex;
    string randWord;        // will hold random words from the dictionary
    string wordWithSpace;   // will hold random word with a space
    bool isBoardFull = false;

    while(!isBoardFull){
        randIndex = rand() % data.size();
        if(piecesLeft > 5){
            // adding random words into
            randWord = data.at(randIndex);
            wordList.push_back(randWord);
            randWord.append(" ");
            wordWithSpace.append(randWord);
            piecesLeft = piecesLeft - randWord.size();
            continue;
        }
        else if(piecesLeft <= 5 && piecesLeft > 2){
            randWord = data.at(randIndex);
            if(randWord.size() > piecesLeft){
                continue;
            }
            else{
                wordList.push_back(randWord);
                wordWithSpace.append(randWord);
                piecesLeft = piecesLeft - word.size();
            }
        }
        else{
            while(piecesLeft != 0){
                wordWithSpace.append(" ");
                piecesLeft--;
            }
        }

        isBoardFull = true;
    }// end while



    pieces = wordWithSpace; // will be using pieces to when displaying board


    // making sure it was generating the correct random words
//    for(int x = 0; x < temp.size(); x++){
//        cout << temp.at(x);
//    }
//    cout << endl;
}// end generateBoard()
//----------------------------------------------------------------------------

// rotates row to the right by a specific amount
void Board ::moveRow(int randomRow, int scrambleAmount, int theBoardSize, string &piecesToScramble) {

    // Getting the right most index of the row
    int lastIndex = ((randomRow + 1) * theBoardSize) - 1;

    // Store the right most character for safe keeping
    char lastChar = piecesToScramble.at(lastIndex);

   for(int j = 0; j < scrambleAmount; j++){

    int i;
    for(i = lastIndex; i > lastIndex - theBoardSize + 1; i--){
        piecesToScramble.at(i) = piecesToScramble.at(i-1);
    }

       // putting the last index character first
       piecesToScramble.at(i) = lastChar;

   }

}// end moveRow()
//----------------------------------------------------------------------------

// rotates a column downwards by a specific amount
void Board ::moveColumn(int randomColumn, int scrambleAmount, int theBoardSize, string &piecesToScramble) {

    // getting the last index of the random column
    int lastIndex = (theBoardSize * (theBoardSize -1)) + randomColumn;

    // Storing the last character of the column for safe keeping
    char lastChar = piecesToScramble.at(lastIndex);

   for(int j = 0; j < scrambleAmount; j++){

       int i;
       int z = lastIndex;
       for(i = lastIndex; i > lastIndex - theBoardSize + 1; i--){
           piecesToScramble.at(z) = piecesToScramble.at(z-boardSize);
           z = z - boardSize;
       }

       // putting the last index character at the beginning of the column
       piecesToScramble.at(z) = lastChar;
   }



}// end moveColumn()
//----------------------------------------------------------------------------

//to help visualize the board
/*
 *       0 1 2 3
 *   0   c a t _   0  1  2  3
 *   1   d o g _   4  5  6  7
 *   2   p e a r   8  9 10 11
 *   3   s _ _ _  12 13 14 15
 */

// scrambles the board by row/column
void Board ::scrambler(int numOfScrambles) {
    scrambledPieces = pieces;   //
    int size = boardSize;       // Size of the board
    int randomRow = 0;
    int randomColumn = 1;  // TODO change this to 0 when done

    // when starting the program, scrambles the board
    for(int i = 0; i < abs(numOfScrambles); i++){
        //randomRow = rand() % size; // TODO uncomment this when done
        moveRow(randomRow, numOfScrambles, size, scrambledPieces);
        //randomColumn = rand() % size; // TODO uncomment this when done
        moveColumn(randomColumn, numOfScrambles, size, scrambledPieces);
    }
}// end scrambler()
//----------------------------------------------------------------------------

void Board ::specificScrambler(char rowOrColumn, int index, int rotationAmount) {
    
}



//reads in words from the dictionary and stores them into the dictionary vector
void readInDictionary(vector <string> & dictionary){

    ifstream inStream;

    inStream.open("dictionary-3to5-letters.txt");
    assert(inStream.fail() == false);

    dictionary.clear();

    string newWord;
    while(inStream >> newWord){
        dictionary.push_back(newWord);
    }
    inStream.close();

}// end readInDictionary()
//----------------------------------------------------------------------------


int main(){

    srand(1);                  // makes rand() predictable
    char userInput;                  // when user inputs a character
    int sizeInput;                   // when user inputs a number
    int totalPiecesLeft;             // total number of pieces on a board
    vector <string> dictionary;      // will store all the words in the dictionary

    readInDictionary(dictionary); // reads in words from dictionary and stores them into vector


    // displaying start up text
    cout << "Program 5: Unscrambler\n"
         << "CS 141, Fall 2021, UIC\n" << endl;

    cout << "You will be presented with a board that is filled\n"
         << "with scrambled words. Rotate the rows and columns\n"
         << "to get the words displayed in the right order.\n" << endl;

    cout << dictionary.size() << " words have been read in from the dictionary." << endl;
    cout << endl;

    cout << "Enter Q to quit or B to begin:";
    cin >> userInput;
    userInput = tolower(userInput);


    if(userInput != 'q') {
        cout << "Choose your board size (must be a number greater than or equal to 4):";
        cin >> sizeInput;
        cout << endl;


        while(sizeInput < 4){
            cout << "The board size must be at least 4. Retry.";
            cout << "Choose your board size (must be a number greater than or equal to 4):";
            cin >> sizeInput;
        }
        Board myBoard(sizeInput);                  // setting board size
        totalPiecesLeft = sizeInput * sizeInput;   // initializing totalPieces
        //TODO generate board
        myBoard.generateBoard(dictionary, totalPiecesLeft);
        //myBoard.displayBoard();

        cout << "Choose the number of times you would like the board to be scrambled (must be a single number >= 1):";
        cin >> sizeInput;

        // making sure the number of scrambles is at least 1
        while(sizeInput < 1){
            cout << "The number of times you select must be at least 1. Retry.\n"
                 << "Choose the number of times you would like the board to be scrambled (must be a single number >= 1):";
            cin >> sizeInput;
        }

        // scrambling the board for the first time
        myBoard.scrambler(sizeInput);


        cout << "These are the words that you should try to spell out using the board, in order:\n"
             << "   ";
        myBoard.printWords();
        cout << endl;

        // !!appending space works so far!!
//        string test = "Test";
//        test.append(" ");
//        cout << test << "space" << endl;
//        cout << endl;


        //TODO scrambled words here

        char charInput;
        int rowOrColumnIndex;
        int rotationAmount;
        bool isInputCorrect = false;
        bool check = false;

        while(userInput != 'q'){
            myBoard.displayBoard(); // TODO supposed to be scrambled

            cout << "Enter one of the following:\n"
                 << "   R to rotate a row or column,\n"
                 << "   C to view what the completed board should look like,\n"
                 << "   B to reset the board back to the beginning,\n"
                 << "   G to generate a new board with new random words,\n"
                 << "   S to have the computer automatically solve a board that you enter (5 points extra credit),\n"
                 << "   Q to quit." << endl;
            cout << "Your choice:";
            cin >> userInput;
            tolower(userInput);

            switch(userInput){
                case 'r':
                    while((rowOrColumnIndex < 0 || rowOrColumnIndex > myBoard.getSize() -1) && check == false){
                        cout << "Enter the row/column you would like to rotate, and the number of positions to rotate by.\n"
                             << "This should be in the format of <R or C> <row/column number> <number of positions to rotate>,\n"
                             << "where valid row and column numbers are between 0 and " << myBoard.getSize() -1 << ",\n"
                             << "E.g. R 0 1 would rotate the top row (row 0) of the board to the right once,\n"
                             << "    c 1 -2 would rotate the second column (col 1) of the board upwards twice." << endl;
                        cout << "Your choice:";
                        cin >> charInput >> rowOrColumnIndex >> rotationAmount;
                        if(charInput == 'r' || charInput == 'c'){
                            check = true;
                        }
                        // if user doesn't enter 'r' or 'c'
                        if(!check){
                            cout << "First input must be 'R' or 'C'. Try again." << endl;
                            check = false;
                        }
                        // if row or column Index is not between 0 and bord size -1
                        else if(rowOrColumnIndex < 0 || rowOrColumnIndex > myBoard.getSize() -1){
                            cout << "Number must be between 0 and 3. Try again." << endl;
                            check = false;
                        }
                        cout << endl;
                    }// end while

                    // rotating a row or column
                    myBoard.scrambler(rotationAmount);
                    break;

                case 'c':
                    cout << "The completed board should look like:" << endl;

                    myBoard.displayBoard(false);
                    break;



                default:
                    break;

            }// end switch
        }

    }// end initial prompts


    cout << "Thank you for playing!" << endl;
    cout << "Exiting program..." << endl;

    return 0;
}// end main()