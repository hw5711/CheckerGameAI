
#include <iostream>
#include <ctime>
#include "GameTree.h"
#include "Checker.h"
#include "AlphaBetaSearch.h"
#include "MinMaxAB.h"
#include "Object.h"


using namespace std;

int nodes_generated, nodes_expanded, steps;

struct Step{
    int heuristic_value;
    int row;
    int col;
};

void print(char, int);
bool checkMoveable(char player, Step *repeat, Object v ){

    //two are empty
    if(repeat[0].row == -1 && repeat[1].row == -1) {
        //cout<<"\n1111111";
        repeat[0].heuristic_value = v.value;
        repeat[0].row = v.row;
        repeat[0].col = v.col;
        return true;
    }
    //second one is empty and not equal to first one
    if(repeat[0].row != -1 && repeat[1].row == -1){
       if(repeat[0].heuristic_value != v.value || repeat[0].row != v.row || repeat[0].col != v.col){
           // cout<<"\n222222 - only one and match nothing ";
            repeat[1].heuristic_value = v.value;
            repeat[1].row = v.row;
            repeat[1].col = v.col;
            return true;
       }
       //equal to the first one
       if(repeat[0].heuristic_value == v.value && repeat[1].row != v.row && repeat[0].col == v.col){
           //cout<<"\n222222 - only one and match the first one ";
           return false;
       }
    }
    //both are not empty
    if(repeat[0].row != -1 && repeat[1].row != -1 ) {
        //match first one
        if (repeat[0].heuristic_value == v.value && repeat[0].row == v.row && repeat[0].col == v.col) {
            if (repeat[1].heuristic_value != v.value && repeat[1].row != v.row && repeat[1].col != v.col) {
                //cout << "\n44444444 match the first one";
                repeat[0].heuristic_value = repeat[1].heuristic_value;
                repeat[0].row = repeat[1].row;
                repeat[0].col = repeat[1].col;
                repeat[1].heuristic_value = v.value;
                repeat[1].row = v.row;
                repeat[1].col = v.col;
                return false;
            }
        }
        if (repeat[1].heuristic_value == v.value && repeat[1].row == v.row && repeat[1].col == v.col) {
            if (repeat[0].heuristic_value != v.value && repeat[0].row != v.row && repeat[0].col != v.col) {
                //cout<<"\n55555555555 match the second one";
                return false;
            }
        }
       // cout<<"\n666666 not match any of values\n";
        repeat[0].heuristic_value = repeat[1].heuristic_value;
        repeat[0].row = repeat[1].row;
        repeat[0].col = repeat[1].col;
        repeat[1].heuristic_value = v.value;
        repeat[1].row = v.row;
        repeat[1].col = v.col;
        return true;
    }
    cout << "REPEAT!!!!-- THIS SHOULD NO SHOW ALWAYS!!!!!!!" << repeat[0].row << "-"<<repeat[0].col<<"-"<<repeat[1].row<<"-"<<repeat[1].col<<endl;
    return true;
}



//MinmaxAB vs MinmaxAB
void MinMax1() {
    int start_s = clock();
    Checker ck ; // ck is the board to be displayed
    Step ArepeatStep[2]; // detect if in the loop
    Step BrepeatStep [2]; // detect if in the loop
    for(int i=0; i<2; i++){
        ArepeatStep[i].heuristic_value = -1000;
        ArepeatStep[i].row = -1;
        ArepeatStep[i].col = -1;
        BrepeatStep[i].heuristic_value = -1000;
        BrepeatStep[i].row = -1;
        BrepeatStep[i].col = -1;
    }
    cout << "Initial board " << endl;
    ck.displayBoard();
    char win = ck.checkWin();
    char player = 'A';
    int shift = 1;
    Checker ck1;
    Checker ck2;
    Object useVal(1000,ck1,0,-1,-1);
    Object passVal(-1000,ck2,0,-1,-1);

    int evaluation1 = 1;
    int evaluation2 = 2;

    while (win == 'N') {
        steps++;
        GameTree *head = new GameTree(player);
        head->copyBoardStatus(ck);
        cout << "*****Turn*****" << player;
        Object v;
        if(shift %2 == 1) { //start with A
            v = MinMaxAB(head, 1, player, useVal, passVal, evaluation1);
        }else{
            v = MinMaxAB(head, 1, player, useVal, passVal, evaluation2);
        }
//        int temp_r = -1;
//        int temp_c = -1;
//        while(player == 'A' && checkMoveable(player, ArepeatStep, v) == false) {
//            ck.setNotMoveable(player, v.row, v.col);
//            temp_r = v.row;
//            temp_c = v.col;
//            head->copyBoardStatus(ck);
//            v = MinMaxAB(head, 1, player, useVal, passVal, evaluation1);
//            ck.setMoveable(player, temp_r, temp_c);
//        }
//
//        while(player == 'B' && checkMoveable(player, BrepeatStep, v) == false) {
//            ck.setNotMoveable(player, v.row, v.col);
//            temp_r = v.row;
//            temp_c = v.col;
//            head->copyBoardStatus(ck);
//            v = MinMaxAB(head, 1, player, useVal, passVal, evaluation2);
//            ck.setMoveable(player, temp_r, temp_c);
//        }

        cout<<"\n*** New Place -- MOVE PLAYER *** step"<<steps<<": "<< player << v.getId()<< "(" << v.getValue();
        cout << ") MOVE TO : " << v.getRow()<<  " - "<< v.getCol() << endl;
        player = ck.move(player, v.getId(), v.getRow(), v.getCol());
        ck.displayBoard();
        win = ck.checkWin();
        shift++;
    }
    int stop_s = clock();
    int execution_time = stop_s - start_s;
    ck.displayBoard();
    print(win, execution_time);
}

//AlphaBeta vs AlphaBeta
void AlphaBeta2() {
    int start_s = clock();
    Checker ck;
    cout << "Initial board " << endl;
    ck.displayBoard();
    char win = ck.checkWin();
    char player = 'A';
    int evaluation1 = 1;
    int evaluation2 = 2;
    int shift = 1;
    Step ArepeatStep[2]; // detect if in the loop
    Step BrepeatStep [2]; // detect if in the loop
    for(int i=0; i<2; i++){
        ArepeatStep[i].heuristic_value = -1000;
        ArepeatStep[i].row = -1;
        ArepeatStep[i].col = -1;
        BrepeatStep[i].heuristic_value = -1000;
        BrepeatStep[i].row = -1;
        BrepeatStep[i].col = -1;
    }

    Checker ck1;
    Checker ck2;
    Object alpha(1000,ck1,0,-1,-1);
    Object beta(-1000,ck2,0,-1,-1);

    while (win == 'N') {
        steps++;
        GameTree *head = new GameTree(player);
        head->copyBoardStatus(ck);
        cout << "\n*****Turn*****" << player << endl;
        Object v;
        if(shift %2 == 1) { //start with A
            v = alphabeta(head, 1, player, alpha, beta, evaluation1);
        }else{
            v = alphabeta(head, 1, player, alpha, beta, evaluation2);
        }
        int temp_r = -1;
        int temp_c = -1;
        int temp_r1 = -1;
        int temp_c1 = -1;
        while(player == 'A' && checkMoveable(player, ArepeatStep, v) == false) {
            ck.setNotMoveable(player, ArepeatStep[0].row, ArepeatStep[0].col);
            ck.setNotMoveable(player, ArepeatStep[1].row, ArepeatStep[1].col);
            if(v.row == ArepeatStep[0].row && v.col == ArepeatStep[0].col ) {
                temp_r1 = v.row;
                temp_c1 = v.col;
            }
            temp_r = ArepeatStep[1].row;
            temp_c = ArepeatStep[1].col;
            head->copyBoardStatus(ck);
            v = alphabeta(head, 1, player, alpha, beta, evaluation1);
            ck.setMoveable(player, temp_r, temp_c);
            ck.setMoveable(player, temp_r1, temp_c1);
        }

        while(player == 'B' && checkMoveable(player, BrepeatStep, v) == false) {
            ck.setNotMoveable(player, BrepeatStep[0].row, BrepeatStep[0].col);
            ck.setNotMoveable(player, BrepeatStep[1].row, BrepeatStep[1].col);
            if(v.row == BrepeatStep[0].row && v.col == BrepeatStep[0].col ) {
                temp_r1 = v.row;
                temp_c1 = v.col;
            }
            temp_r = BrepeatStep[1].row;
            temp_c = BrepeatStep[1].col;
            head->copyBoardStatus(ck);
            v = alphabeta(head, 1, player, alpha, beta, evaluation2);
            ck.setMoveable(player, temp_r, temp_c);
            ck.setMoveable(player, temp_r1, temp_c1);
        }

        cout<<"\n*** New Place -- MOVE PLAYER *** step"<<steps<<": "<< player << v.id<< "(" << v.value;
        cout << ") MOVE TO : " << v.row<<  " - "<< v.col << endl;
        player = ck.move(player, v.id, v.row, v.col);
        ck.displayBoard();
        win = ck.checkWin();
        shift++;
    }
    int stop_s = clock();
    int execution_time = stop_s - start_s;
    ck.displayBoard();
    print(win, execution_time);
}

void MinMaxAlphaBeta1() { //Both use evaluation 1
    int start_s = clock();
    Checker ck;
    cout << "Initial board " << endl;
    ck.displayBoard();
    char win = ck.checkWin();
    char player = 'A';
    int evaluation1 = 1;
    int evaluation2 = 2;
    int shift = 1;
    Checker ck1;
    Checker ck2;

    Object useVal(1000,ck1,0,-1,-1);
    Object passVal(-1000,ck2,0,-1,-1);
    Object alpha(1000,ck1,0,-1,-1);
    Object beta(-1000,ck2,0,-1,-1);

    Step ArepeatStep[2]; // detect if in the loop
    Step BrepeatStep [2]; // detect if in the loop
    for(int i=0; i<2; i++){
        ArepeatStep[i].heuristic_value = -1000;
        ArepeatStep[i].row = -1;
        ArepeatStep[i].col = -1;
        BrepeatStep[i].heuristic_value = -1000;
        BrepeatStep[i].row = -1;
        BrepeatStep[i].col = -1;
    }

    while (win == 'N') {
        steps++;
        GameTree *head = new GameTree(player);
        head->copyBoardStatus(ck);
        cout << "\n*****Turn*****" << player << endl;
        Object v;
        if(shift %2 == 1) { //start with A
            v = MinMaxAB(head, 1, player, useVal, passVal, evaluation1);
        }else{
            v = alphabeta(head, 1, player, alpha, beta, evaluation1);
        }

        int temp_r = -1;
        int temp_c = -1;
        int temp_r1 = -1;
        int temp_c1 = -1;
        while(player == 'A' && checkMoveable(player, ArepeatStep, v) == false) {
            ck.setNotMoveable(player, ArepeatStep[0].row, ArepeatStep[0].col);
            ck.setNotMoveable(player, ArepeatStep[1].row, ArepeatStep[1].col);
            if(v.row == ArepeatStep[0].row && v.col == ArepeatStep[0].col ) {
                temp_r1 = v.row;
                temp_c1 = v.col;
            }
            temp_r = ArepeatStep[1].row;
            temp_c = ArepeatStep[1].col;
            head->copyBoardStatus(ck);
            v = alphabeta(head, 1, player, alpha, beta, evaluation1);
            ck.setMoveable(player, temp_r, temp_c);
            ck.setMoveable(player, temp_r1, temp_c1);
        }

        while(player == 'B' && checkMoveable(player, BrepeatStep, v) == false) {
            ck.setNotMoveable(player, BrepeatStep[0].row, BrepeatStep[0].col);
            ck.setNotMoveable(player, BrepeatStep[1].row, BrepeatStep[1].col);
            if(v.row == BrepeatStep[0].row && v.col == BrepeatStep[0].col ) {
                temp_r1 = v.row;
                temp_c1 = v.col;
            }
            temp_r = BrepeatStep[1].row;
            temp_c = BrepeatStep[1].col;
            head->copyBoardStatus(ck);
            v = alphabeta(head, 1, player, alpha, beta, evaluation2);
            ck.setMoveable(player, temp_r, temp_c);
            ck.setMoveable(player, temp_r1, temp_c1);
        }

        cout<<"\n*** New Place -- MOVE PLAYER *** step"<<steps<<": "<< player << v.id<< "(" << v.value;
        cout << ") MOVE TO : " << v.row<<  " - "<< v.col << endl;
        player = ck.move(player, v.id, v.row, v.col);
        ck.displayBoard();
        win = ck.checkWin();
        shift++;
    }
    int stop_s = clock();
    int execution_time = stop_s - start_s;
    ck.displayBoard();
    print(win, execution_time);
}

void MinMaxAlphaBeta2() { //Both use evaluation 2
    int start_s = clock();
    Checker ck;
    cout << "Initial board " << endl;
    ck.displayBoard();
    char win = ck.checkWin();
    char player = 'A';
//    int evaluation1 = 1;
    int evaluation2 = 2;
    int shift = 1;
    Checker ck1;
    Checker ck2;

    Object useVal(1000,ck1,0,-1,-1);
    Object passVal(-1000,ck2,0,-1,-1);
    Object alpha(1000,ck1,0,-1,-1);
    Object beta(-1000,ck2,0,-1,-1);

    while (win == 'N') {
        steps++;
        GameTree *head = new GameTree(player);
        head->copyBoardStatus(ck);
        cout << "\n*****Turn*****" << player << endl;
        Object v;
        if(shift %2 == 1) { //start with A
            v = MinMaxAB(head, 1, player, useVal, passVal, evaluation2);
        }else{
            v = alphabeta(head, 1, player, alpha, beta, evaluation2);
        }

        cout<<"\n*** New Place -- MOVE PLAYER *** step"<<steps<<": "<< player << v.id<< "(" << v.value;
        cout << ") MOVE TO : " << v.row<<  " - "<< v.col << endl;
        player = ck.move(player, v.id, v.row, v.col);
        ck.displayBoard();
        win = ck.checkWin();
        shift++;
    }
    int stop_s = clock();
    int execution_time = stop_s - start_s;
    ck.displayBoard();
    print(win, execution_time);
}

void Statistics_print() {
    //cout << "Number of nodes generated : " << nodes_generated << endl;
    cout << "Number of nodes expanded : " << nodes_expanded << endl;
    cout << "Number of nodes generated : " << nodes_generated << endl;
    cout << "Number of steps : " << steps << endl;
    cout << "Memory need for 1 node is: 81 bytes." << endl;
    int x = 81 * nodes_generated;
    cout << "Total memory needed for the algorithm is : " << x << "bytes = " << x / (1024) << "ck" <<endl;
}

void MinMaxUser() { //Both use evaluation 2
    int start_s = clock();
    Checker ck;
    cout << "Initial board " << endl;
    ck.displayBoard();
    char win = ck.checkWin();
    char player = 'A';
//    int evaluation1 = 1;
    int evaluation2 = 2;
    int shift = 1;
    Checker ck1;
    Checker ck2;

    Object useVal(1000,ck1,0,-1,-1);
    Object passVal(-1000,ck2,0,-1,-1);
    Object alpha(1000,ck1,0,-1,-1);
    Object beta(-1000,ck2,0,-1,-1);

    while (win == 'N') {
        steps++;
        GameTree *head = new GameTree(player);
        head->copyBoardStatus(ck);
        cout << "\n*****Turn*****" << player << endl;
        Object v;
        if(shift %2 == 1) { //start with A
            v = MinMaxAB(head, 1, player, useVal, passVal, evaluation2);
        }else{
            int id = 0;
            int row = -1;
            int col = -1;
            cout<<"\n Please input id: ";
            cin>>id;
            cout<<"\n Please input row : ";
            cin>>row;
            cout<<"\n Please input col: ";
            cin>>col;
            v.id = id;
            v.row = row;
            v.col = col;
        }

        cout<<"\n*** New Place -- MOVE PLAYER *** step"<<steps<<": "<< player << v.id<< "(" << v.value;
        cout << ") MOVE TO : " << v.row<<  " - "<< v.col << endl;
        player = ck.move(player, v.id, v.row, v.col);
        ck.displayBoard();
        win = ck.checkWin();
        shift++;
    }
    int stop_s = clock();
    int execution_time = stop_s - start_s;
    ck.displayBoard();
    print(win, execution_time);
}


void print(char win, int execution_time) {
    cout << "The result of the game is : " << win << endl;
    cout << endl;
    if (win == 'A')
        cout << "Player A won! Congrats " << endl;
    else if (win == 'B')
        cout << "Player B won! Congrats " << endl;
    else if (win == 'T')
        cout << "Game tied!! " << endl;
   // cout << "\n\t\t\tGame Ends-*\n" << endl;
    cout << "Execution time taken is : " << (execution_time) / double(CLOCKS_PER_SEC) << " seconds" << endl;
    Statistics_print();
}



int main() {
    int choice_game;
    cout << "\t\t\tChecker Game(8X8)\n\t\t      *-*-*-*-*-*-*-*-*-*-*-*\n\t\t\t*-Game Begins" << endl;
    cout << "Enter 1 for MinMaxAB(EF1) VS MinMaxAB(EF2) " << endl;
    cout << "Enter 2 for AlphaBetaSearch(EF1) VS AlphaBetaSearch(EF2) " << endl;
    cout << "Enter 3 for MinMaxAB(EF1) VS AlphaBetaSearch(EF1) " << endl;
    cout << "Enter 4 for MinMaxAB(EF2) VS AlphaBetaSearch(EF2)  " << endl;
    cout << "Enter 5 for MinMaxAB VS USER  " << endl;

    cin >> choice_game;

    switch (choice_game) {
        case 1:
            MinMax1();
            break;
        case 2:
            AlphaBeta2();
            break;
        case 3:
            MinMaxAlphaBeta1();
            break;
        case 4:
            MinMaxAlphaBeta2();
            break;
        case 5:
            MinMaxUser();

    }
    // Statistics_print();

    return 0;
}
