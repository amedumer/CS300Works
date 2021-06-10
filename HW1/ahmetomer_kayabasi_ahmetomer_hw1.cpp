//
//  main.cpp
//  cs300_hw1
//
//  Created by Ahmet Ömer Kayabaşı on 11.03.2021.
//
// Hi and welcome to my homework! Hope you like it.
//
// If you want to see Debug Data, comment out the line below

//#define DBG

#include <iostream>
#include <string>
#include "Stack.cpp"
#include <vector>
#include <iomanip>
#include <chrono>
#include "randgen.h"
#include <fstream>

#include <sstream>
#define endl "\n"

using namespace std;

bool kingFinderHelper(Stack<cell> & board, int lastX, int lastY, vector<pair<int,int> >  moves,int moveCount);
void pathHelper(Stack<cell> & board, int count);

int rowCount[20];
int colCount[20];
int diagCount[39];
int reverseDiagCount[39];
int SIZE;
int kingX,kingY;
int initialMoveCount;
Stack<cell> board;
bool thereIsAWay;
Stack<pair<int,int> > movess;
RandGen rnd;
vector<pair<int, int> > finMoves;

pair<int, int> directions[8] = {
    make_pair(0,-1),
    make_pair(0, 1),
    make_pair(1, 0),
    make_pair(-1, 0),
    make_pair(1, 1),
    make_pair(1, -1),
    make_pair(-1, -1),
    make_pair(-1,1)
};

pair<int, int> knightMoves[8] = {
    make_pair(2,-1),
    make_pair(2, 1),
    make_pair(-2, 1),
    make_pair(-2, -1),
    make_pair(1, 2),
    make_pair(1, -2),
    make_pair(-1, -2),
    make_pair(-1,2)
};


Stack<cell> initBoard(const int & size){
    Stack<cell> board;
    
    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= size; j++) {
            board.push(cell(i, j));
        }
    }
    
    board.initReverse();
    
    return board;
}

/// Returns the stack index given x and y coordinates.
/// @param y
/// @param x
int findIndex(int y, int x){
    return ((x - 1) * SIZE + y - 1);
}

void printBoard(Stack<cell> &board){
    int size = board.size;
    int row = SIZE;
    cout << "The matrix:" << endl ;
    
    for (int i = 0; i < size; i++) {
        if (board[i].has_pawn) {
            cout << setw(3) << left << "O" ;
        }
        
        else if(board[i].has_knight){
            cout << setw(3) << left << "X" ;
        }
        else{
            cout << setw(3) << left << "_" ;
        }
        
        if (board[i].y_coordinate == sqrt(size)) {
            cout << setw(4) << row-- <<endl << endl;
        }
    }
    for (int i = 0; i < SIZE; i++) {
        cout << setw(3) << i + 1;
    }
    cout << endl;
}

void debugData(Stack<cell> board){
    int size = board.size;
    
    cout << endl <<"BOARD DEBUG DATA" << endl <<"-------------------------" <<
    endl << "X" << setw(5) << "Y" << setw(5) << "Pawn" << setw(6) << "Visited" << endl;
    
    for (int i = 0; i < size; i++) {
        cout << board[i].x_coordinate << setw(5) << board[i].y_coordinate << setw(5) << board[i].has_pawn << setw(6) << board[i].visited << endl;
        
        if (board[i].y_coordinate == sqrt(size)) {
            cout << endl;
        }
    }
    
    printBoard(board);
    
    cout << endl << "ROW AND COLUMN DATA" << endl << "----------" << endl;
    for (int i = 1; i <= sqrt(size); i++) {
        cout << "Row #" << i << ": " << rowCount[i] << endl << "Col #" << i << ": " << colCount[i] << endl << endl;
     }
    
    cout << endl << "DIAGONAL DATA" << endl << "----------" << endl;
    for (int i = 1; i <= sqrt(size) * 2 - 1; i++) {
        cout << "Diagonal #" << i << ": " << diagCount[i] << endl;
        
     }
    
    cout << endl << "REVERSE DIAGONAL DATA" << endl << "----------" << endl;
    for (int i = 1; i <= sqrt(size) * 2 - 1; i++) {
        cout << "Reverse Diagonal #" << i << ": " << reverseDiagCount[i] << endl;
        
     }
    int x = 1;
    cout << endl << "SOLUTION MOVES" << endl << "----------" << endl;
    for (int i = finMoves.size() - 1 ; i >= 0; i--) {
        cout << "Move #" << x++ << ": " << finMoves[i].first << " " << SIZE - finMoves[i].second + 1 << endl;
    }
    
}

/// Main pathfinder function
/// @param board Board Stack
/// @param pawnCount Required Pawn Count
void pathFinder(Stack<cell> & board, int pawnCount){
    
    board[findIndex(1, SIZE)].pawn_status(true);
    board[findIndex(1, SIZE)].visited = true;
    
    
    if (pawnCount != 1)
        pathHelper(board, pawnCount -1);
    
    printBoard(board);
    
}

/// Boolean function to check if the new move is valid.
/// @param board Board Stack
/// @param x New Possible move's x coord.
/// @param y New Possible move's y coord.
bool constraintCheck(const Stack<cell> & board, int x, int y){
    if (rowCount[y] == 3 || colCount[x] == 3 || diagCount[x + y - 1] == 3 || reverseDiagCount[SIZE + x - y] == 3) {
        return false;
    }
    return true;
}

/// A function to find the previous (faulty) move so the code can mark that move unavailable.
/// @param falseMove False Move pair (x and y)
/// @param prevMove Previous Move pair (x and y)
int directionIdx(pair<int, int> falseMove, pair<int, int> prevMove ){
    
    int move1 = falseMove.first - prevMove.first;
    int move2 = prevMove.second - falseMove.second;
    
    for (int i = 0;  i < 8; i++ ) {
        if (directions[i].first == move1 && directions[i].second == move2) {
            return i;
        }
    }
    
    return -1;
}

/// Pawn place function. Done by using stacks.
/// @param board
/// @param count
void pathHelper(Stack<cell> & board, int count){
    movess.push(pair<int, int>(1,SIZE));
    pair<int,int> lastMove,falseMove,prevMove,test,move;
    int idx, unavailableCount = 0, boardIdx, newX, newY, lastIdx, t1, t2;

    while(movess.size != count + 1) {
    
        lastMove = movess.peek();
        lastIdx = findIndex(lastMove.first, lastMove.second);
        
        unavailableCount = 0;
        // Determining unavailable moves
        for (int j = 0; j < 8; j++) {
            test = directions[j];
            t1 = lastMove.first + test.first;
            t2 = lastMove.second + test.second;
            
            boardIdx = findIndex(t1, t2);
            
            if (((t1 > SIZE || t1 < 1) || (t2 > SIZE || t2 < 1))|| board[boardIdx].has_pawn || !constraintCheck(board, t1, t2) || board[lastIdx].directions[j] == 1 ) {
                unavailableCount++;
                board[lastIdx].directions[j] = 1;
            }
        }
        
        // If there is a move to make, randomly pick that move and process.
        if (unavailableCount != 8) {
            
            idx = rnd.RandInt(0,7);
            move = directions[idx];
            
            newX = lastMove.first + move.first;
            newY = lastMove.second + move.second;
                
            while ( board[lastIdx].directions[idx] == 1 ) {
                
                idx = rnd.RandInt(0,7);
                move = directions[idx];
                
                newX = lastMove.first + move.first;
                newY = lastMove.second + move.second;
            }
            
            boardIdx = findIndex(newX, newY);
                
            board[boardIdx].visited = true;
            board[boardIdx].pawn_status(true);
            
            movess.push(pair<int,int>(newX,newY));

            board[lastIdx].directions[idx] = 1;
        }
          
        // If there is no move to make, pop that move from the stack.
        else {
            movess.pop(falseMove);
            prevMove = movess.peek();
            
            board[lastIdx].pawn_status(false);
            
            for (int i = 0; i < 8; i++) {
                board[lastIdx].directions[i] = 0;
            }
            
            board[findIndex(prevMove.first, prevMove.second)].directions[directionIdx(falseMove,prevMove)] = 1;
            
        }
    }
    
    
}

int findKing(Stack<cell> &board,int kingX, int kingY, int knightX, int knightY){
    vector<pair<int,int> > moves;
    
    if (kingX == knightX && kingY == knightY) {
        board[findIndex(knightX, knightY)].has_knight = true;
        moves.push_back(pair<int,int>(knightX,knightY));
        return 1;
    }
    else{
        for (int i = 0; i < SIZE * 2; i++) {
            initialMoveCount = i + 1;

            board[findIndex(knightX, knightY)].has_knight = true;
            moves.push_back(pair<int,int>(knightX,knightY));
            
            if(kingFinderHelper(board, knightX, knightY, moves,i + 1)){
                thereIsAWay = true;
                return 1;
            }
        }
    }
    thereIsAWay = false;
    return 1;
}

/// Event though pawn placement is done by Stacks, and we are told to do so, Homework document doesnt state that we cant use recursion when rescuing the king.
/// This recursive function works great! It tries to find the king move by move (first it tries to find with 1 moves then 2 moves 3 moves...)
/// @param board Board Stack
/// @param lastX x
/// @param lastY y
/// @param moves move vector
/// @param moveCount recursive function's break condition
bool kingFinderHelper(Stack<cell> & board, int lastX, int lastY, vector<pair<int,int> >  moves, int moveCount){
    
    int used[8] = {0};
    int idx;
    int unavailableCount = 0;
    
    if (moveCount == 0) {
        return false;
    }
    
    for (int j = 0; j < 8; j++) {
        pair<int,int> test = knightMoves[j];
        int t1 = lastX + test.first;
        int t2 = lastY + test.second;
        int idx = findIndex(t1, t2);
        
        if ((t1 > SIZE || t1 < 1) || (t2 > SIZE || t2 < 1)) {
            used[j] = 1;
            unavailableCount++;
        }
        
        else if (board[idx].has_pawn || board[idx].has_knight) {
            used[j] = 1;
            unavailableCount++;
        }
    }
    
    for (int i = 0; i < 8 ; i++) {
        
        if (used[i] == 1) {
            continue;
        }
        else{
            idx = i;
            pair<int,int> move = knightMoves[idx];
            
            int newX = lastX + move.first;
            int newY = lastY + move.second;
            
            used[idx] = 1;
        
            moves.push_back(pair<int, int>(newX,newY));
            
            if (newX == kingX && newY == kingY) {
                board[findIndex(newX, newY)].has_knight= true;
                finMoves.push_back(pair<int,int>(newX, newY));
                return true;
            }
            
            if(kingFinderHelper(board, newX, newY, moves,moveCount - 1)){
                board[findIndex(newX, newY)].has_knight= true;
                finMoves.push_back(pair<int,int>(newX, newY));
                return true;
            }
            else {
                moves.pop_back();
                board[findIndex(newX, newY)].has_knight= false;
            }
        }
    }

    board[findIndex(lastX, lastY)].has_knight= false;
    moves.pop_back();

    return false;
}

void processOutput(const int & pawn, const int & knightX, const int & knghtY, const int & kngY){
    ofstream of;
    
    of.open("output.txt");
    
    of << "N = " << SIZE << endl
    << "P = " << pawn << endl << endl;
    
    
    of << "Pawn Locations" << endl;
    pair<int,int> move;
    while (!movess.isEmpty()) {
        movess.pop(move);
        of << move.first  << " " <<SIZE - move.second + 1 << " " << endl;
    }
    
    of << endl << "Knight = " << knightX << " " << knghtY << endl
    << "King = " << kingX << " " << kngY << endl << endl;
    
    if(thereIsAWay){
        cout << "Path found, see the output file!" << endl;
        of << knightX << " " << knghtY << endl;
        
        for (int i = finMoves.size() - 1 ; i >= 0; i--) {
            of << finMoves[i].first << " " << SIZE - finMoves[i].second + 1 << endl;
        }

    }
    else{
        of << "No way!" << endl;
        cout << "No way!" << endl;
    }
    of << endl <<"Matrix" << endl;
    
    for (int i = 0; i < SIZE * SIZE; i++) {
        if (board[i].has_pawn) {
            of << setw(2) << left << "1" ;
        }
        else{
            of << setw(2) << left << "0" ;
        }
        
        if (board[i].y_coordinate == (SIZE)) {
            of << endl;
        }
    }
}

int main() {
    
    int pawn;
    int knghtY, kngY;
    
    cout << "Please enter the size of the board (n): ";
    cin >> SIZE;
    
    
    if (!(SIZE > 4 && SIZE < 11)) {
        cout << "Invalid input!" << endl;
        return 0;
    }
    
    cout << "Please enter the number of the pawns (p): ";
    cin >> pawn;
    
    if (!(pawn > 0 && pawn <= SIZE * 3)) {
        cout << "Invalid input!" << endl;
        return 0;
    }
    
    board = initBoard(SIZE);
    pathFinder(board, pawn);
    
    int knightX, knightY;
    cout << "Enter the position of knight(x,y): ";
    cin >> knightX >> knightY;
    
    knghtY = knightY;
    
    knightY = SIZE - knightY + 1;
    
    if (board[findIndex(knightX, knightY)].has_pawn) {
        cout << "Couldn't place Knight! Cell already full!" << endl;
        return 0;
    }
    
    cout << "Enter the position of king(x,y): ";
    cin >> kingX >> kingY;
    
    kngY = kingY;
    
    kingY = SIZE - kingY + 1;
    
    if (board[findIndex(kingX, kingY)].has_pawn) {
        cout << "Couldn't place King! Cell already full!" << endl;
        return 0;
    }
    
    findKing(board, kingX, kingY, knightX, knightY);
    
    processOutput(pawn,knightX,knghtY,kngY);
    
    #ifdef DBG
    debugData(board);
    #endif
    return 0;
}

