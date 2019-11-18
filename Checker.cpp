
#include "Checker.h"
#include <iostream>
#include <iomanip>
#include<ctime>
#include<cstdlib>


using namespace std;

//initializing the board
Checker::Checker() {
    int id_num = 1;
    int id_num_otherplayer = 1;
    for(int i = 0; i < 8; i++){
        for( int j = 0; j < 8; j++){
            //set player A side board
            if(i == 0 && j%2 == 0){ //A side 1st row
                setBoard('A',i,j,'m',id_num,-1000,true);
                id_num++;
                continue;
            }

            if(i == 0 && j%2 != 0){
                setBoard(' ', i, j, 'n',0, -1000,true);
                continue;
            }

            if(i == 1 && j%2 != 0){ //A side 2nd row
                setBoard('A',i,j,'m',id_num,-1000,true);
                id_num++;
                continue;
            }

            if(i == 1 && j%2 == 0){
                setBoard(' ',i,j,'n',0,-1000,true);
                continue;
            }

            if(i == 2 && j%2 == 0){ //A side 3rd row
                setBoard('A',i,j,'m',id_num,-1000,true);
                id_num++;
                continue;
            }
            if (i == 2 && j%2 != 0){
                setBoard(' ',i,j,'n',0,-1000,true);
                continue;
            }

            //set middle 2 lines board
            if(i == 3 || i == 4 ){
                setBoard(' ',i,j,'n',0,-1000,true);
                continue;
            }
            //set player B side board
            if(i == 5 && j%2 != 0){ //A side 1st row
                setBoard('B',i,j,'m',id_num_otherplayer,-1000,true);
                id_num_otherplayer++;
                continue;
            }

            if (i == 5 && j%2 == 0) {
                setBoard(' ',i,j,'n',0,-1000,true); // N means not possessed by both playler
                continue;
            }

            if(i == 6 && j%2 == 0){ //A side 2nd row
                setBoard('B',i,j,'m',id_num_otherplayer,-1000,true);
                id_num_otherplayer++;
                continue;
            }

            if(i == 6 && j%2 != 0){
                setBoard(' ',i,j,'n',0,-1000,true);
                continue;
            }

            if(i == 7 && j%2 != 0){ //A side 3rd row
                setBoard('B',i,j,'m',id_num_otherplayer,-1000,true);
                id_num_otherplayer++;
                continue;
            }

            if(i == 7 && j%2 == 0){
                setBoard(' ',i,j,'n',0,-1000,true);
                continue;
            }
        }
    }
    set_heuristic_value_board( -1000);
}

//constructor to set the board values, mainly used for testing
void Checker::setBoard(char p, int r, int c, char ro, int i, int he, bool t) {
    board[r][c].player = p;
    board[r][c].row = r;
    board[r][c].col = c;
    board[r][c].role = ro;
    board[r][c].id = i;
    board[r][c].heuristic_value = he;
    board[r][c].moveable = t;

}

//Function to move for the A player
char Checker::move_A(char player, int id, int r, int c) {

    int before_r = -1;
    int before_c = -1;

    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if(board[i][j].player == player && board[i][j].id == id){
                before_r = i;
                before_c = j;
            }
        }
    }

    int row_diff = abs(r-before_r);
    int col_diff = abs(c-before_c);
    if(row_diff == 1 && col_diff ==1){
        char role = board[before_r][before_c].role;
        //char player = board[r][c].player;
        setBoard(player,r,c,role,id,-1000,true); // set the moving place
        setBoard(' ',before_r,before_c,'n',0,-1000,true); //set current place as empty
        before_r = r; //change the current head row
        before_c = c; //change the current head col
    }else{ // eat enemy
        char role = board[before_r][before_c].role;
        //char player =board[r][c].player;
        setBoard(' ',r,c,'n',0,-1000,true);
        if(r >before_r && c > before_c) {
            int en_id = board[before_r+1][before_c+1].id;
            setBoard(player, r, c, role,id, -1000,true);
            setBoard(' ', before_r+1, before_c+1, 'n',en_id, -1000,true);
            setBoard(' ', before_r, before_c, 'n',0, -1000,true);
        }
        else if(r > before_r && c < before_c){
            int en_id = board[before_r+1][before_c-1].id;
            setBoard(player, r, c, role,id, -1000,true);
            setBoard(' ', before_r+1, before_c-1,en_id, 'n', -1000,true);
            setBoard(' ', before_r, before_c, 'n',0, -1000,true);
        }
        else if(r < before_r && c >before_c){
            int en_id = board[before_r-1][before_c+1].id;
            setBoard(player, r, c, role,id, -1000,true);
            setBoard(' ', before_r-1, before_c+1, 'n',en_id, -1000,true);
            setBoard(' ', before_r, before_c, 'n',0, -1000,true);
        }
        else if(r <before_r && c < before_c){
            int en_id = board[before_r-1][before_c-1].id;
            setBoard(player, r, c, role,id, -1000,true);
            setBoard(' ', before_r-1, before_c-1, 'n', en_id,-1000,true);
            setBoard(' ', before_r, before_c, 'n',0, -1000,true);
        }else{}
//        before_r = r; //change the current head row
//        before_c = c; //change the current head col
    }
    //update king role
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++) {
            if(i==0 && getPlayer(i,j) == 'B'){
                int id = board[i][j].id;
                setBoard('B',i,j,'k',id,-1000,true);
            }
            if(i==7 && getPlayer(i,j) == 'A'){
                int id = board[i][j].id;
                setBoard('A',i,j,'k',id,-1000,true);
            }
        }
    }
//    cout<<"\n*** MOVE PLAYER *** "<< player << id;
//    cout << "   MOVE TO :hole row # " << r
//         <<  " --- hole col # "<< c<< endl;
    return 'B';
}

//Function to move for the B player
char Checker::move_B(char player, int id, int r, int c) {

    int before_r = -1;
    int before_c = -1;

    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if(board[i][j].player == player && board[i][j].id == id){
                before_r = i;
                before_c = j;
            }
        }
    }

    int row_diff = abs(r-before_r);
    int col_diff = abs(c-before_c);
    if(row_diff == 1 && col_diff ==1){
        char role = board[before_r][before_c].role;
        //char player = board[r][c].player;
        setBoard(player,r,c,role,id,-1000,true); // set the moving place
        setBoard(' ',before_r,before_c,'n',0,-1000,true); //set current place as empty
        before_r = r; //change the current head row
        before_c = c; //change the current head col
    }else{ // eat enemy
        char role = board[before_r][before_c].role;
        //char player = board[r][c].player;
        setBoard(' ',r,c,'n',0,-1000,true);
        if(r >before_r && c > before_c) {
            int en_id = board[before_r+1][before_c+1].id;
            setBoard(player, r, c, role,id, -1000,true);
            setBoard(' ', before_r+1, before_c+1, 'n',en_id, -1000,true);
            setBoard(' ', before_r, before_c, 'n',0, -1000,true);
        }
        else if(r > before_r && c < before_c){
            int en_id = board[before_r+1][before_c-1].id;
            setBoard(player, r, c, role,id, -1000,true);
            setBoard(' ', before_r+1, before_c-1,en_id, 'n', -1000,true);
            setBoard(' ', before_r, before_c, 'n',0, -1000,true);
        }
        else if(r < before_r && c >before_c){
            int en_id = board[before_r-1][before_c+1].id;
            setBoard(player, r, c, role,id, -1000,true);
            setBoard(' ', before_r-1, before_c+1, 'n',en_id, -1000,true);
            setBoard(' ', before_r, before_c, 'n',0, -1000,true);
        }
        else if(r <before_r && c < before_c){
            int en_id = board[before_r-1][before_c-1].id;
            setBoard(player, r, c, role,id, -1000,true);
            setBoard(' ', before_r-1, before_c-1, 'n', en_id,-1000,true);
            setBoard(' ', before_r, before_c, 'n',0, -1000,true);
        }else{}
//        before_r = r; //change the current head row
//        before_c = c; //change the current head col
    }
    //update king role
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++) {
            if(i==0 && getPlayer(i,j) == 'B'){
                int id = board[i][j].id;
                setBoard('B',i,j,'k',id,-1000,true);
            }
            if(i==7 && getPlayer(i,j) == 'A'){
                int id = board[i][j].id;
                setBoard('A',i,j,'k',id,-1000,true);
            }
        }
    }

//    cout<<"\n*** MOVE PLAYER *** "<< player << id;
//    cout << "   MOVE TO :hole row # " << r
//         <<  " --- hole col # "<< c<< endl;
    return 'A';
}

//Function which decides as to who should move
/*** will perform move and change role, board ***/
char Checker::move(char player, int id, int row, int col) {
    char v;
    if (player == 'A') {
        v = move_A( player,  id,  row,  col);
    }
    else{
        v = move_B( player,  id,  row,  col);
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
    return board[r][c].player;
}


char Checker::getRole(int r, int c) {
    return board[r][c].role;
}

int Checker::getId(int r, int c) {
    return board[r][c].id;
}


int Checker::getPlayerNum(char player){
    int i=0;
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if(board[i][j].player == player){
                i++;
            }
        }
    }
    return i;
}

//Function to display the board
void Checker::displayBoard() {
    cout << "***** DISPLAY BOARD *****\n";
//    cout << "A( "<< getPlayerNum('A') << " ) -vs- "
//    << "B( " << getPlayerNum('B') << " )\n";
    for(int i = 0; i < 8; i++){
        for( int j = 0; j < 8; j++) {
            if(getPlayer(i,j) != ' '){
//                cout << "|" << getPlayer(i,j)<< "| ";
                cout << "|" << getPlayer(i,j) << getId(i,j) << getRole(i,j) << "| ";
            }
            else{
                cout << " - ";
            }
        }
        cout << endl;
    }
}



int Checker::get_heuristic_value_board(){
    return heuristic_value;
}

void Checker::set_heuristic_value_board(int v){
    heuristic_value = v;
}

const Address &Checker::getAddress() const {
    return address;
}

void Checker::setAddress(const Address &address) {
    Checker::address = address;
}

void Checker::setNotMoveable(char player, int row, int col){
    board[row][col].moveable = false;
}

void Checker::setMoveable(char player, int row, int col){
    board[row][col].moveable = true;
}

bool Checker::isMoveable(int i, int j) {
    return board[i][j].moveable;
}

