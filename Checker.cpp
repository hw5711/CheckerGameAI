
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
            }else if(i == 0 && j%2 != 0){
                setBoard(' ', i, j, 'n', -1000);
            }else{}

            if(i == 1 && j%2 != 0){ //A side 2nd row
                setBoard('A',i,j,'m',-1000);
            }else if(i == 1 && j%2 == 0){
                setBoard(' ',i,j,'n',-1000);
            }else{}

            if(i == 2 && j%2 == 0){ //A side 3rd row
                setBoard('A',i,j,'m',-1000);
            }else if (i == 2 && j%2 != 0){
                setBoard(' ',i,j,'n',-1000);
            }else{}

            //set middle 2 lines board
            if(i == 3 || i == 4 ){
                setBoard(' ',i,j,'n',-1000);
            }
            //set player B side board
            if(i == 5 && j%2 != 0){ //A side 1st row
                setBoard('B',i,j,'m',-1000);
            }else if (i == 5 && j%2 == 0) {
                setBoard(' ',i,j,'n',-1000); // N means not possessed by both playler
            }else{}

            if(i == 6 && j%2 == 0){ //A side 2nd row
                setBoard('B',i,j,'m',-1000);
            }else if(i == 6 && j%2 != 0){
                setBoard(' ',i,j,'n',-1000);
            }else{}

            if(i == 7 && j%2 != 0){ //A side 3rd row
                setBoard('B',i,j,'m',-1000);
            }else if(i == 7 && j%2 == 0){
                setBoard(' ',i,j,'n',-1000);
            }else{}
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
char Checker::move_A(int r, int c, char player) {
    int row_diff = abs(r-this->row);
    int col_diff = abs(c-this->col);
    if(row_diff == 1 && col_diff ==1){
        char role = this->board[r][c].role;
        //char player = this->board[r][c].player;
        setBoard(player,r,c,role,-1000); // set the moving place
        setBoard(' ',this->row,this->col,'n',-1000); //set current place as empty
        this->row = r; //change the current head row
        this->col = c; //change the current head col
    }else{ // eat enemy
        char role = this->board[r][c].role;
        //char player = this->board[r][c].player;
        setBoard(' ',r,c,'n',-1000);
        if(r > this->row && c > this->col) {
            setBoard(player, r, c, role, -1000);
            setBoard(' ', this->row+1, this->col+1, 'n', -1000);
            setBoard(' ', this->row, this->col, 'n', -1000);
        }
        else if(r > this->row && c < this->col){
            setBoard(player, r, c, role, -1000);
            setBoard(' ', this->row+1, this->col-1, 'n', -1000);
            setBoard(' ', this->row, this->col, 'n', -1000);
        }
        else if(r < this->row && c > this->col){
            setBoard(player, r, c, role, -1000);
            setBoard(' ', this->row-1, this->col+1, 'n', -1000);
            setBoard(' ', this->row, this->col, 'n', -1000);
        }
        else if(r < this->row && c < this->col){
            setBoard(player, r, c, role, -1000);
            setBoard(' ', this->row-1, this->col-1, 'n', -1000);
            setBoard(' ', this->row, this->col, 'n', -1000);
        }else{}
        this->row = r; //change the current head row
        this->col = c; //change the current head col
    }
    //update king role
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++) {
        }
    }
    return 'B';
}

//Function to move for the B player
char Checker::move_B(int r, int c, char player) {
    int row_diff = abs(r-this->row);
    int col_diff = abs(c-this->col);
    if(row_diff == 1 && col_diff ==1){
        char role = this->board[r][c].role;
        //char player = this->board[r][c].player;
        setBoard(player,r,c,role,-1000); // set the moving place
        setBoard(' ',this->row,this->col,'n',-1000); //set current place as empty
        this->row = r; //change the current head row
        this->col = c; //change the current head col
    }else{ // eat enemy
        char role = this->board[r][c].role;
        //char player = this->board[r][c].player;
        setBoard(' ',r,c,'n',-1000);
        if(r > this->row && c > this->col) {
            setBoard(player, r, c, role, -1000);
            setBoard(' ', this->row+1, this->col+1, 'n', -1000);
            setBoard(' ', this->row, this->col, 'n', -1000);
        }
        else if(r > this->row && c < this->col){
            setBoard(player, r, c, role, -1000);
            setBoard(' ', this->row+1, this->col-1, 'n', -1000);
            setBoard(' ', this->row, this->col, 'n', -1000);
        }
        else if(r < this->row && c > this->col){
            setBoard(player, r, c, role, -1000);
            setBoard(' ', this->row-1, this->col+1, 'n', -1000);
            setBoard(' ', this->row, this->col, 'n', -1000);
        }
        else if(r < this->row && c < this->col){
            setBoard(player, r, c, role, -1000);
            setBoard(' ', this->row-1, this->col-1, 'n', -1000);
            setBoard(' ', this->row, this->col, 'n', -1000);
        }else{}
        this->row = r; //change the current head row
        this->col = c; //change the current head col
    }
    return 'A';
}

//Function which decides as to who should move
/*** will perform move and change role, board ***/
char Checker::move(int r, int c, char player) {
    char v;
    if (player == 'A') {
        v = move_A(r, c, player);
    }
    else{
        v = move_B(r, c, player);
    }
    return v;
}

//Function to decide as to which player wins
char Checker::checkWin() {
    int acc_a = 0;
    int acc_b = 0;
    for (int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(board[i][j].player == 'A') {
                acc_a ++;
            }
            if(board[i][j].player == 'B'){
                acc_b ++;
            }
        }
    }
    if(acc_a == 0){
        return 'B';
    }
    if(acc_b == 0){
        return 'A';
    }

    if(acc_b == acc_a && acc_a == 1){
        return 'T';
    }
    return 'N';
}

char Checker::getPlayer(int r, int c) {
    return this->board[r][c].player;
}

//Function to display the board
void Checker::displayBoard() {
    cout << "***** DISPLAY BOARD *****\n";
//    cout << "xxxx|" << getPlayer(0,0) << "| ";
    for(int i = 0; i < 8; i++){
        for( int j = 0; j < 8; j++) {
            cout << "|" << getPlayer(i,j) << "| ";
        }
        cout << endl;
    }
}



int Checker::get_heuristic_value_board(){
    return this->heuristic_value;
}

void Checker::set_heuristic_value_board(int v){
    this->heuristic_value = v;
}
