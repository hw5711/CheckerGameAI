
#include "Checker.h"
#include <iostream>
#include <iomanip>
#include<ctime>
#include<cstdlib>


using namespace std;

//initializing the board
Checker::Checker() {
    for(int i = 0; i < 8; i++){
        for( int j = 0; j < 8; j++){
            //set player A side board
            if(i == 0 && j%2 == 0){ //A side 1st row
                setBoard('A',i,j,'m',-1000);
            }else{
                setBoard(' ',i,j,'n',-1000);
            }
            if(i == 1 && j%2 != 0){ //A side 2nd row
                setBoard('A',i,j,'m',-1000);
            }else{
                setBoard(' ',i,j,'n',-1000);
            }
            if(i == 2 && j%2 == 0){ //A side 3rd row
                setBoard('A',i,j,'m',-1000);
            }else{
                setBoard(' ',i,j,'n',-1000);
            }
            //set middle 2 lines board
            if(i == 3 || i == 4 ){
                setBoard(' ',i,j,'n',-1000);
            }
            //set player B side board
            if(i == 5 && j%2 != 0){ //A side 1st row
                setBoard('B',i,j,'m',-1000);
            }else{
                setBoard(' ',i,j,'n',-1000); // N means not possessed by both playler
            }
            if(i == 6 && j%2 == 0){ //A side 2nd row
                setBoard('B',i,j,'m',-1000);
            }else{
                setBoard(' ',i,j,'n',-1000);
            }
            if(i == 7 && j%2 != 0){ //A side 3rd row
                setBoard('B',i,j,'m',-1000);
            }else{
                setBoard(' ',i,j,'n',-1000);
            }
        }
    }
    this->heuristic_value = -1000;
}

//copy constructor to copy the value of the board from one var to another
Checker::Checker(Checker *b) {
    for (int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            this->board[i][j].player = b->board[i][j].player;
            this->board[i][j].row = b->board[i][j].row;
            this->board[i][j].col = b->board[i][j].col;
            this->board[i][j].role = b->board[i][j].role;
            this->board[i][j].heuristic_value = b->board[i][j].heuristic_value;
        }
    }
}

//constructor to set the board values, mainly used for testing
void Checker::setBoard(char p, int r, int c, char ro, int he) {
    this->board[r][c].player = p;
    this->board[r][c].row = r;
    this->board[r][c].col = c;
    this->board[r][c].role = ro;
    this->board[r][c].heuristic_value = he;
}

//Function to move for the A player
char Checker::move_A(int r, int c) {
    int current_row =
    return 'B';
}

//Function to move for the B player
char Checker::move_B(int hole_number_r, int hole_number_c) {
    int tempPos = hole_number;
    ptr = B;
    int numberOfStones = ptr[tempPos];
    ptr[hole_number] = 0;
    int opponentPos, opponentStones;

    tempPos++;
    while (numberOfStones > 0) {
        if (tempPos >= 0 && tempPos <= 5) {
            if (numberOfStones == 1) {
                numberOfStones--;
                opponentPos = numberOfSlots - tempPos;
                if (ptr[tempPos] == 0) {
                    ptr = A;
                    opponentStones = ptr[opponentPos];
                    if (numberOfStones == 0)
                        return 'A';
                } else {
                    ptr[tempPos] += 1;
                    if (numberOfStones == 0)
                        return 'A';
                }
            } else if (numberOfStones > 1) {
                numberOfStones--;
                ptr[tempPos] += 1;
            }
        } else if (tempPos == 6 && numberOfStones >= 1) {
            numberOfStones--;
            if (numberOfStones == 0)
                return 'B';
        } else if (tempPos > 6 && tempPos <= 12) {
            ptr = A;
            numberOfStones--;
            ptr[tempPos - 7] += 1;
            if (numberOfStones == 0)
                return 'A';
        } else if (tempPos >= 12) {
            tempPos = -1;
            ptr = B;
        }
        tempPos++;
    }
    return 'A';
}

//Function which decides as to who should move
/*** will perform move and change role, board ***/
char Checker::move(int hole_number_r, int hole_number_c, char player) {
    char v;
    if (player == 'A')
        v = move_A(hole_number_r, hole_number_c);
    else
        v = move_B((hole_number_r, hole_number_c);
    return v;
}

//Function to decide as to which player wins
char Checker::checkWin() {
    int acc_a = 0;
    int acc_b = 0;
    for (int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(board[i][j].player == 'A')   acc_a ++;
            if(board[i][j].player == 'B')   acc_b ++;
        }
    }
    if(acc_a == 0)  return 'B';
    if(acc_b == 0)  return 'A';
}

void Checker::operator=(Checker kb) {
}

char Checker::getPlayer(int r, int c) {
    return this->board[r][c].player;
}

//Function to display the board
void Checker::displayBoard() {
    cout << "***** DISPLAY BOARD *****";
    for(int i = 0; i < 8; i++){
        for( int j = 0; j < 8; j++) {
            cout << "|" << getPlayer(i,j) << "| ";
        }
        cout << endl;
    }
}

//bool Checker::checkLegealMove(char player, int hole) {
//    if (hole > 5 || hole < 0)
//        return false;
//    if (player == 'A' && A[hole] == 0) {
//        return false;
//    } else if (player == 'B' && B[hole] == 0) {
//        return false;
//    }
//    return true;
//}

int Checker::get_heuristic_value_board(){
    return this->heuristic_value;
}

void Checker::set_heuristic_value_board(int v){
    this->heuristic_value = v;
}
