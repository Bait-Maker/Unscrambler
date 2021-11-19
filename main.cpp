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
using namespace std;

class Board{

public:
    Board(int size){ boardSize = size;}
    void displayBoard();

private:
    int boardSize;
    vector <string> Boards;

};// end class Board

void Board ::displayBoard() {
    cout << "Current board:" << endl;
    cout << "       ";
    for(int i = 0; i < boardSize; i++){
       cout << i << "   ";
        for(int j = 0; j < boardSize ; j++){
            cout << "   " << j << " |   |";
            if(j == boardSize-1){
                cout << endl;
            }
        }
    }
    cout << endl;





}// end displayBoard()
//----------------------------------------------------------------------------

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

    char userInput;
    vector <string> dictionary;
    Board myBoard(4);

    readInDictionary(dictionary);

    myBoard.displayBoard();


    cout << "Program 5: Unscrambler\n"
         << "CS 141, Fall 2021, UIC\n" << endl;

    cout << "You will be presented with a board that is filled with scrambled words. Rotate the rows and columns\n"
         << "to get the words displayed in the right order.\n" << endl;

    cout << "13893 words have been read in from the dictionary.\n" << endl;

    cout << "Enter Q to quit or B to begin:";
    cin >> userInput;
    userInput = tolower(userInput);

    if(userInput == 'q'){
        cout << "Thanks for playing!" << endl;
    }



    cout << "Exiting program..." << endl;

    return 0;
}// end main()