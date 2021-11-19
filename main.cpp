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
    void displayBoard();
    void generateBoard(const vector <string> &data, int piecesLeft);
    void printWords();

private:
    int boardSize;
    string pieces;
    vector <string> wordList;

};// end class Board
//----------------------------------------------------------------------------

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

void Board ::displayBoard() {
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
                cout << " | " << pieces.at(counter);
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
   cout << "Current board words: ";
   for(int i = 0; i < wordList.size(); i++){
       cout << wordList.at(i) << " ";
   }
   cout << endl;
   cout << endl;

}// end displayBoard()
//----------------------------------------------------------------------------

// adds random words onto the board until the board is full
void Board ::generateBoard(const vector <string> &data, int piecesLeft){

    string temp, word;

    while(piecesLeft >= 3){
        // not appending " " to random words
        // when 4 spaces remain
        if(piecesLeft == 4){
            word = data.at(rand()%data.size());
            if (word.size() > piecesLeft){
                continue;
            }
            else {
                wordList.push_back(word);
                temp.append(word);
                piecesLeft = piecesLeft - word.size();
//                cout << piecesLeft << endl;
            }
        }
        word = data.at(rand()%data.size());
        wordList.push_back(word);
        word.append(" ");
        if(word.size() > piecesLeft){
            continue;
        }
        else{
            temp.append(word);
            piecesLeft = piecesLeft - word.size();
            //cout << piecesLeft << endl;

            }
        }// end while

    if(piecesLeft <=2){
        while(piecesLeft != 0){
            temp.append(" ");
            piecesLeft--;
        }

    }// end while

    pieces = temp; // will be using pieces to when displaying board


    // making sure it was generating the correct random words
//    for(int x = 0; x < temp.size(); x++){
//        cout << temp.at(x);
//    }
//    cout << endl;
}

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

    srand(1);
    char userInput;
    int sizeInput;
    int totalPiecesLeft;
    vector <string> dictionary;

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
        // TODO Scramble and print here


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
                case 'c':
                    cout << "The completed board should look like:" << endl;
                    myBoard.displayBoard();


                default:
                    break;

            }// end switch
        }

    }// end initial prompts






    cout << "Thank you for playing!" << endl;
    cout << "Exiting program..." << endl;

    return 0;
}// end main()