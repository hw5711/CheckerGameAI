
#include <iostream>
#include <ctime>
#include "CheckerTree.h"
#include "Checker.h"
#include "MinMaxAB.h"
#include "Object.h"
#include "AlphaBeta.h"
#include <stdio.h>

using namespace std;



struct Step {
    int heuristic_value1;
    int row1;
    int col1;
    int id1;
    int heuristic_value2;
    int row2;
    int col2;
    int id2;
};

int nodesGenerated, nodesExpanded, node_generatedA, node_generatedB,node_expendedA, node_expendedB,steps;

void gameMenu();

int getTotalPieceNum(char player, Checker *ck){
    int counter = 0;
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if(ck->board[i][j].player == player){
                counter ++;
            }
        }
    }
    return counter;
}

int getMoveableCount(char player, Checker *ck) {
    int cA = 0;
    int cB = 0;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (ck->board[i][j].player == player && player == 'A'
                && ck->board[i][j].moveable == true) {
                cA++;
            }
            if (ck->board[i][j].player == player && player == 'B'
                && ck->board[i][j].moveable == true) {
                cB++;
            }
        }
    }
    if (player == 'A') return cA;
    if (player == 'B') return cB;
}

void displayResult(char winner, int executionTime, int nodesGenerated, int nodesExpanded) {
    cout << "Final Result is : " << winner << endl;
    if (winner == 'A')
        cout << "Player A is the winner." << endl;
    else if (winner == 'B')
        cout << "Player B is the winner." << endl;
    else if (winner == 'T')
        cout << "No players won.It is a tie!" << endl;
    cout << "Execution time: " << (executionTime) / double(CLOCKS_PER_SEC) << " s\n" << endl;

    cout << "No: of nodes expanded A: " << node_expendedA << endl;
    cout << "No: of nodes expanded B: " << node_expendedB << endl;
    cout << "No: of nodes generated A: " << node_generatedA << endl;
    cout << "No: of nodes generated B: " << node_generatedB << endl;

    cout << "Total length of path A: " << steps/2 << endl;
    cout << "Total length of path B: " << steps/2 << endl;


    cout << "Memory need for 1 node is: 1236 bytes." << endl;
    int x = 1236 * node_generatedA;
    int y = 1236 * node_generatedB;

    cout << "Total memory needed for A: " << x << " bytes = " << x / (1024) << " kb" << endl;
    cout << "Total memory needed for B: " << y << " bytes = " << y / (1024) << " kb" << endl;
}

bool checkMoveable(char player, Step *repeat, Object v) {
    //two are empty
    if (repeat->row1 == -1 && repeat->row2 == -1) {
        repeat->heuristic_value1 = v.value;
        repeat->row1 = v.row;
        repeat->col1 = v.col;
        return true;
    }
    //second one is empty and not equal to first one
    if (repeat->row1 != -1 && repeat->row2 == -1) {
        if (repeat->heuristic_value1 != v.value || repeat->row1 != v.row || repeat->col1 != v.col) {
            repeat->heuristic_value2 = v.value;
            repeat->row2 = v.row;
            repeat->col2 = v.col;
            return true;
        }
        //equal to the first one
        if (repeat->heuristic_value1 == v.value && repeat->row2 != v.row && repeat->col1 == v.col) {
            return false;
        }
    }
    //both are not empty
    if (repeat->row1 != -1 && repeat->row2 != -1) {
        //match first one
        if (repeat->heuristic_value1 == v.value && repeat->row1 == v.row && repeat->col1 == v.col) {
            if (repeat->heuristic_value2 != v.value || repeat->row2 != v.row || repeat->col2 != v.col) {
                repeat->heuristic_value1 = repeat->heuristic_value2;
                repeat->row1 = repeat->row2;
                repeat->col1 = repeat->col2;
                repeat->heuristic_value2 = v.value;
                repeat->row2 = v.row;
                repeat->col2 = v.col;
                return false;
            }
        }
        if (repeat->heuristic_value2 == v.value && repeat->row2 == v.row && repeat->col2 == v.col) {
            if (repeat->heuristic_value1 != v.value && repeat->row1 != v.row && repeat->col1 != v.col) {
                return false;
            }
        }
        repeat->heuristic_value1 = repeat->heuristic_value2;
        repeat->row1 = repeat->row2;
        repeat->col1 = repeat->col2;
        repeat->heuristic_value2 = v.value;
        repeat->row2 = v.row;
        repeat->col2 = v.col;
        return true;
    }
    return true;
}

//MinmaxAB vs MinmaxAB ( using ev1,ev2 and ev3)
void MinMax1(int choice) {  //option 1
    int counter = choice;
    clock_t time_req;
    time_req = clock();
    Checker checker;

    char winner = checker.winningPlayer();
    char player = 'A';

    Step ArepeatStep; // detect if in the loop
    Step BrepeatStep; // detect if in the loop

    ArepeatStep.heuristic_value1 = -1000;
    ArepeatStep.row1 = -1;
    ArepeatStep.col1 = -1;
    ArepeatStep.id1 = -1;
    ArepeatStep.heuristic_value2 = -1000;
    ArepeatStep.row2 = -1;
    ArepeatStep.col2 = -1;
    ArepeatStep.id2 = -1;
    BrepeatStep.heuristic_value1 = -1000;
    BrepeatStep.row1 = -1;
    BrepeatStep.col1 = -1;
    BrepeatStep.id1 = -1;
    BrepeatStep.heuristic_value2 = -1000;
    BrepeatStep.row2 = -1;
    BrepeatStep.col2 = -1;
    BrepeatStep.id2 = -1;
    bool notfound = true;

    Step stepArrayA[12]; // index means each piece id of player A
    Step stepArrayB[12]; // index means each piece id of player B

    for (int i = 0; i < 12; i++) {
        stepArrayA[i] = ArepeatStep;
    }
    for (int i = 0; i < 12; i++) {
        stepArrayB[i] = BrepeatStep;
    }

    int shift = 1;
    Checker checker1;
    Checker checker2;
    Object useVal(1000, checker1, 0, -1, -1);
    Object passVal(-1000, checker2, 0, -1, -1);

    while (winner == 'N') {
        steps++;
        CheckerTree *headptr = new CheckerTree(player);
        headptr->newCurrentBoard(checker);
        Object v;
        if (counter == 1) {
            if (shift % 2 == 1) { //start with A
                v = MinMaxAB(headptr, 1, player, useVal, passVal, 1);
            } else {
                v = MinMaxAB(headptr, 1, player, useVal, passVal, 2);
            }
        }
        if (counter == 2) {
            if (shift % 2 == 1) { //start with A
                v = MinMaxAB(headptr, 1, player, useVal, passVal, 1);
            } else {
                v = MinMaxAB(headptr, 1, player, useVal, passVal, 3);
            }
        }
        if (counter == 3) {
            if (shift % 2 == 1) { //start with A
                v = MinMaxAB(headptr, 1, player, useVal, passVal, 2);
            } else {
                v = MinMaxAB(headptr, 1, player, useVal, passVal, 3);
            }
        }

        int temp_r = -1;
        int temp_c = -1;
        int temp_id = 0;
        int temp_r1 = -1;
        int temp_c1 = -1;
        int temp_id1 = 0;
        int current_id = v.id;
        int counterA = -1;
        int counterB = -1;
        bool notfound = true;
        if (player == 'A') {
            counterA = getMoveableCount(player, &headptr->currentboard);
        }
        if (player == 'B') {
            counterB = getMoveableCount(player, &headptr->currentboard);
        }

        if (player == 'A') {
            checkMoveable(player, &stepArrayA[current_id], v);
            getTotalPieceNum('A',&headptr->currentboard);
            while (checkMoveable(player, &stepArrayA[current_id], v) == 0) {
                if (counterA > 0) {
                    checker.setNotMoveable(player, ArepeatStep.row1, ArepeatStep.col1, ArepeatStep.id1);
                    checker.setNotMoveable(player, ArepeatStep.row2, ArepeatStep.col2, ArepeatStep.id2);
                    if(ArepeatStep.row1 == -1 && ArepeatStep.row2 == -1){
                        ArepeatStep.col1 = v.col;
                        ArepeatStep.row1 = v.row;
                        ArepeatStep.id1 = v.id;
                        ArepeatStep.heuristic_value1 = v.value;
                    }

                    if(ArepeatStep.row1 != -1 && ArepeatStep.row2 == -1){
                        ArepeatStep.col2 = v.col;
                        ArepeatStep.row2 = v.row;
                        ArepeatStep.id2 = v.id;
                        ArepeatStep.heuristic_value2 = v.value;
                    }

                    if (v.row == ArepeatStep.row1 && v.col == ArepeatStep.col1) {
                        temp_r1 = v.row;
                        temp_c1 = v.col;
                        temp_id1 = v.id;
                        temp_id = ArepeatStep.id2;
                        temp_r = ArepeatStep.row2;
                        temp_c = ArepeatStep.col2;
                        int tempr, tempc, tempid, temph;
                        tempc = ArepeatStep.col1;
                        tempr = ArepeatStep.row1;
                        tempid = ArepeatStep.id1;
                        temph = ArepeatStep.heuristic_value1;
                        ArepeatStep.col1 = ArepeatStep.col2;
                        ArepeatStep.row1 = ArepeatStep.row2;
                        ArepeatStep.id1 = ArepeatStep.id1;
                        ArepeatStep.heuristic_value1 = ArepeatStep.heuristic_value2;
                        ArepeatStep.col2 = tempc;
                        ArepeatStep.row2 = tempr;
                        ArepeatStep.id2 = tempid;
                        ArepeatStep.heuristic_value2 = temph;
                    } else if (v.row == ArepeatStep.row2 && v.col == ArepeatStep.col2){
                        temp_r = v.row;
                        temp_c = v.col;
                        temp_id = v.id;
                        temp_r1 = ArepeatStep.row2;
                        temp_c1 = ArepeatStep.col2;
                        temp_id1 = ArepeatStep.id2;
                    }
                    else {
                        ArepeatStep.col2 = v.col;
                        ArepeatStep.row2 = v.row;
                        ArepeatStep.id2 = v.id;
                        ArepeatStep.heuristic_value2 = v.value;
                    }

                    headptr->newCurrentBoard(checker);

                    if (counter == 1) { //start with A
                        v = MinMaxAB(headptr, 1, player, useVal, passVal, 1);
                    }
                    if (counter == 2) {
                        v = MinMaxAB(headptr, 1, player, useVal, passVal, 1);
                    }
                    if (counter == 3) {
                        v = MinMaxAB(headptr, 1, player, useVal, passVal, 2);
                    }
                    checker.setMoveable(player, temp_r, temp_c, temp_id);
                    checker.setMoveable(player, temp_r1, temp_c1, temp_id1);
                    counterA--;
                } else {
                    if(getTotalPieceNum('A',&headptr->currentboard)<=2) {
                        notfound = false;
                    }
                    break;

                }
            }
        }
        if (player == 'B') {
                checkMoveable(player, &stepArrayB[current_id], v);
                getTotalPieceNum('B',&headptr->currentboard);
            while (checkMoveable(player, &stepArrayB[current_id], v) == 0) {
                if (counterB > 0) {
                    checker.setNotMoveable(player, BrepeatStep.row1, BrepeatStep.col1, BrepeatStep.id1);
                    checker.setNotMoveable(player, BrepeatStep.row2, BrepeatStep.col2, BrepeatStep.id2);
                    if(BrepeatStep.row1 == -1 && BrepeatStep.row2 == -1){
                        BrepeatStep.col1 = v.col;
                        BrepeatStep.row1 = v.row;
                        BrepeatStep.id1 = v.id;
                        BrepeatStep.heuristic_value1 = v.value;
                    }
                    if(BrepeatStep.row1 != -1 && BrepeatStep.row2 == -1){
                        BrepeatStep.col2 = v.col;
                        BrepeatStep.row2 = v.row;
                        BrepeatStep.id2 = v.id;
                        BrepeatStep.heuristic_value2 = v.value;
                    }
                    if (v.row == BrepeatStep.row1 && v.col == BrepeatStep.col1) {
                        temp_r1 = v.row;
                        temp_c1 = v.col;
                        temp_id1 = v.id;
                        temp_id = BrepeatStep.id2;
                        temp_r = BrepeatStep.row2;
                        temp_c = BrepeatStep.col2;
                        int tempr, tempc, tempid, temph;
                        tempc = BrepeatStep.col1;
                        tempr = BrepeatStep.row1;
                        tempid = BrepeatStep.id1;
                        temph = BrepeatStep.heuristic_value1;
                        BrepeatStep.col1 = BrepeatStep.col2;
                        BrepeatStep.row1 = BrepeatStep.row2;
                        BrepeatStep.id1 = BrepeatStep.id1;
                        BrepeatStep.heuristic_value1 = BrepeatStep.heuristic_value2;
                        BrepeatStep.col2 = tempc;
                        BrepeatStep.row2 = tempr;
                        BrepeatStep.id2 = tempid;
                        BrepeatStep.heuristic_value2 = temph;
                    } else {
                        temp_r = v.row;
                        temp_c = v.col;
                        temp_id = v.id;
                        temp_r1 = BrepeatStep.row2;
                        temp_c1 = BrepeatStep.col2;
                        temp_id1 = BrepeatStep.id2;
                    }
                    BrepeatStep.col2 = v.col;
                    BrepeatStep.row2 = v.row;
                    BrepeatStep.id2 = v.id;
                    BrepeatStep.heuristic_value2 = v.value;
                    headptr->newCurrentBoard(checker);
                    if (counter == 1) { //start with A
                        v = MinMaxAB(headptr, 1, player, useVal, passVal, 2);
                    }
                    if (counter == 2) {
                        v = MinMaxAB(headptr, 1, player, useVal, passVal, 3);
                    }
                    if (counter == 3) {
                        v = MinMaxAB(headptr, 1, player, useVal, passVal, 3);
                    }
                    checker.setMoveable(player, temp_r, temp_c, temp_id);
                    checker.setMoveable(player, temp_r1, temp_c1, temp_id1);
                    counterB--;
                } else {
                    if( getTotalPieceNum('B',&headptr->currentboard)<=2) {
                        notfound = false;
                    }
                    break;
                }
            }
        }

        if(player == 'A'&& v.value == 1000){
            winner = 'B';
            continue;
        }
        if(player=='B'&& v.value == -1000){
            winner = 'A';
            continue;
        }
//        player = checker.choosePlayer(player, v.id, v.row, v.col);
        if(notfound == false && player == 'A'){
            player = checker.choosePlayer(player, ArepeatStep.id1, ArepeatStep.row1, ArepeatStep.col1);
        }

        if(notfound == false && player == 'B'){
            player = checker.choosePlayer(player,  BrepeatStep.id1, BrepeatStep.row1, BrepeatStep.col1);
        }
        if(notfound == true){
            player = checker.choosePlayer(player, v.id, v.row, v.col);
        }
//        checker.displayCheckerBoard();
        winner = checker.winningPlayer();
        shift++;
    }
    int executionTime = clock() - time_req;
    checker.displayCheckerBoard();
    displayResult(winner, executionTime, nodesGenerated, nodesExpanded);
}

void AlphaBeta2(int choice) {  //option 2
    int counter = choice;
    clock_t time_req;
    time_req = clock();
    Checker checker;
    int shift = 1;

    char winner = checker.winningPlayer();
    char player = 'A';

    Step ArepeatStep; // detect if in the loop
    Step BrepeatStep; // detect if in the loop

    ArepeatStep.heuristic_value1 = -1000;
    ArepeatStep.row1 = -1;
    ArepeatStep.col1 = -1;
    ArepeatStep.id1 = -1;
    ArepeatStep.heuristic_value2 = -1000;
    ArepeatStep.row2 = -1;
    ArepeatStep.col2 = -1;
    ArepeatStep.id2 = -1;
    BrepeatStep.heuristic_value1 = -1000;
    BrepeatStep.row1 = -1;
    BrepeatStep.col1 = -1;
    BrepeatStep.id1 = -1;
    BrepeatStep.heuristic_value2 = -1000;
    BrepeatStep.row2 = -1;
    BrepeatStep.col2 = -1;
    BrepeatStep.id2 = -1;

    Step stepArrayA[12]; // index means each piece id of player A
    Step stepArrayB[12]; // index means each piece id of player B

    for (int i = 0; i < 12; i++) {
        stepArrayA[i] = ArepeatStep;
    }
    for (int i = 0; i < 12; i++) {
        stepArrayB[i] = BrepeatStep;
    }

    Checker checker1;
    Checker checker2;
    Object alpha(-1000, checker1, 0, -1, -1);
    Object beta(1000, checker2, 0, -1, -1);

    while (winner == 'N') {
        steps++;
        CheckerTree *headptr = new CheckerTree(player);
        headptr->newCurrentBoard(checker);
        Object v;
        if (counter == 1) { //start with A
            if (shift % 2 == 1) { //start with A
                v = alphabeta(headptr, 1, player, alpha, beta, 1);
            } else {
                v = alphabeta(headptr, 1, player, alpha, beta, 2);
            }
        }
        if (counter == 2) {
            if (shift % 2 == 1) { //start with A
                v = alphabeta(headptr, 1, player, alpha, beta, 1);
            } else {
                v = alphabeta(headptr, 1, player, alpha, beta, 3);
            }
        }
        if (counter == 3) {
            if (shift % 2 == 1) { //start with A
                v = alphabeta(headptr, 1, player, alpha, beta, 2);
            } else {
                v = alphabeta(headptr, 1, player, alpha, beta, 3);
            }
        }
        int temp_r = -1;
        int temp_c = -1;
        int temp_id = 0;
        int temp_r1 = -1;
        int temp_c1 = -1;
        int temp_id1 = 0;
        int current_id = v.id;
        int counterA = -1;
        int counterB = -1;
        bool notfound = true;
        if (player == 'A') {
            counterA = getMoveableCount(player, &headptr->currentboard);
        }
        if (player == 'B') {
            counterB = getMoveableCount(player, &headptr->currentboard);
        }

        if (player == 'A') {
                getTotalPieceNum('A',&headptr->currentboard);

            while (checkMoveable(player, &stepArrayA[current_id], v) == 0) {
                if (counterA > 0) {
                    checker.setNotMoveable(player, ArepeatStep.row1, ArepeatStep.col1, ArepeatStep.id1);
                    checker.setNotMoveable(player, ArepeatStep.row2, ArepeatStep.col2, ArepeatStep.id2);
                    if(ArepeatStep.row1 == -1 && ArepeatStep.row2 == -1){
                        ArepeatStep.col1 = v.col;
                        ArepeatStep.row1 = v.row;
                        ArepeatStep.id1 = v.id;
                        ArepeatStep.heuristic_value1 = v.value;
                    }

                    if(ArepeatStep.row1 != -1 && ArepeatStep.row2 == -1){
                        ArepeatStep.col2 = v.col;
                        ArepeatStep.row2 = v.row;
                        ArepeatStep.id2 = v.id;
                        ArepeatStep.heuristic_value2 = v.value;
                    }

                    if (v.row == ArepeatStep.row1 && v.col == ArepeatStep.col1) {
                        temp_r1 = v.row;
                        temp_c1 = v.col;
                        temp_id1 = v.id;
                        temp_id = ArepeatStep.id2;
                        temp_r = ArepeatStep.row2;
                        temp_c = ArepeatStep.col2;
                        int tempr, tempc, tempid, temph;
                        tempc = ArepeatStep.col1;
                        tempr = ArepeatStep.row1;
                        tempid = ArepeatStep.id1;
                        temph = ArepeatStep.heuristic_value1;
                        ArepeatStep.col1 = ArepeatStep.col2;
                        ArepeatStep.row1 = ArepeatStep.row2;
                        ArepeatStep.id1 = ArepeatStep.id1;
                        ArepeatStep.heuristic_value1 = ArepeatStep.heuristic_value2;
                        ArepeatStep.col2 = tempc;
                        ArepeatStep.row2 = tempr;
                        ArepeatStep.id2 = tempid;
                        ArepeatStep.heuristic_value2 = temph;
                    } else if (v.row == ArepeatStep.row2 && v.col == ArepeatStep.col2){
                        temp_r = v.row;
                        temp_c = v.col;
                        temp_id = v.id;
                        temp_r1 = ArepeatStep.row2;
                        temp_c1 = ArepeatStep.col2;
                        temp_id1 = ArepeatStep.id2;
                    }
                    else {
                        ArepeatStep.col2 = v.col;
                        ArepeatStep.row2 = v.row;
                        ArepeatStep.id2 = v.id;
                        ArepeatStep.heuristic_value2 = v.value;
                    }

                    headptr->newCurrentBoard(checker);

                    if (counter == 1) { //start with A
                        v = alphabeta(headptr, 1, player, alpha, beta, 1);
                    }
                    if (counter == 2) {
                        v = alphabeta(headptr, 1, player, alpha, beta, 1);
                    }
                    if (counter == 3) {
                        v = alphabeta(headptr, 1, player, alpha, beta, 2);
                    }
                    checker.setMoveable(player, temp_r, temp_c, temp_id);
                    checker.setMoveable(player, temp_r1, temp_c1, temp_id1);
                    counterA--;
                } else {
                    if( getTotalPieceNum('A',&headptr->currentboard)<=2) {
                        notfound = false;
                    }
                    break;
                }
            }
        }
        if (player == 'B') {
                checkMoveable(player, &stepArrayA[current_id], v);
            getTotalPieceNum('A',&headptr->currentboard);
            while (checkMoveable(player, &stepArrayB[current_id], v) == 0) {
                if (counterB > 0) {
                    checker.setNotMoveable(player, BrepeatStep.row1, BrepeatStep.col1, BrepeatStep.id1);
                    checker.setNotMoveable(player, BrepeatStep.row2, BrepeatStep.col2, BrepeatStep.id2);

                    if(BrepeatStep.row1 == -1 && BrepeatStep.row2 == -1){
                        BrepeatStep.col1 = v.col;
                        BrepeatStep.row1 = v.row;
                        BrepeatStep.id1 = v.id;
                        BrepeatStep.heuristic_value1 = v.value;
                    }

                    if(BrepeatStep.row1 != -1 && BrepeatStep.row2 == -1){
                        BrepeatStep.col2 = v.col;
                        BrepeatStep.row2 = v.row;
                        BrepeatStep.id2 = v.id;
                        BrepeatStep.heuristic_value2 = v.value;
                    }
                    if (v.row == BrepeatStep.row1 && v.col == BrepeatStep.col1) {
                        temp_r1 = v.row;
                        temp_c1 = v.col;
                        temp_id1 = v.id;
                        temp_id = BrepeatStep.id2;
                        temp_r = BrepeatStep.row2;
                        temp_c = BrepeatStep.col2;
                        int tempr, tempc, tempid, temph;
                        tempc = BrepeatStep.col1;
                        tempr = BrepeatStep.row1;
                        tempid = BrepeatStep.id1;
                        temph = BrepeatStep.heuristic_value1;
                        BrepeatStep.col1 = BrepeatStep.col2;
                        BrepeatStep.row1 = BrepeatStep.row2;
                        BrepeatStep.id1 = BrepeatStep.id1;
                        BrepeatStep.heuristic_value1 = BrepeatStep.heuristic_value2;
                        BrepeatStep.col2 = tempc;
                        BrepeatStep.row2 = tempr;
                        BrepeatStep.id2 = tempid;
                        BrepeatStep.heuristic_value2 = temph;
                    } else {
                        temp_r = v.row;
                        temp_c = v.col;
                        temp_id = v.id;
                        temp_r1 = BrepeatStep.row2;
                        temp_c1 = BrepeatStep.col2;
                        temp_id1 = BrepeatStep.id2;
                    }
                    BrepeatStep.col2 = v.col;
                    BrepeatStep.row2 = v.row;
                    BrepeatStep.id2 = v.id;
                    BrepeatStep.heuristic_value2 = v.value;

                    headptr->newCurrentBoard(checker);
                    if (counter == 1) { //start with A
                        v = alphabeta(headptr, 1, player, alpha, beta, 2);
                    }
                    if (counter == 2) {
                        v = alphabeta(headptr, 1, player, alpha, beta, 3);
                    }
                    if (counter == 3) {
                        v = alphabeta(headptr, 1, player, alpha, beta, 3);
                    }
                    checker.setMoveable(player, temp_r, temp_c, temp_id);
                    checker.setMoveable(player, temp_r1, temp_c1, temp_id1);
                    counterB--;
                } else {
                    if( getTotalPieceNum('B',&headptr->currentboard)<=2) {
                        notfound = false;
                    }
                    break;
                }
            }
        }

        if(notfound == false && player == 'A'){
            player = checker.choosePlayer(player, ArepeatStep.id1, ArepeatStep.row1, ArepeatStep.col1);
        }

        if(notfound == false && player == 'B'){
            player = checker.choosePlayer(player,  BrepeatStep.id1, BrepeatStep.row1, BrepeatStep.col1);
        }
        if(notfound == true){
            player = checker.choosePlayer(player, v.id, v.row, v.col);
        }
//        cout<<"\n** In step "<<steps<<": "<< player << v.id<< "(" << v.value;
//        cout << ") moved to row  : " << v.row<<   " and column "<< v.col << endl;
//        player = checker.choosePlayer(player, v.id, v.row, v.col);
//        checker.displayCheckerBoard();
        winner = checker.winningPlayer();
        shift++;
    }
    int executionTime = clock() - time_req;
    checker.displayCheckerBoard();
    displayResult(winner, executionTime, nodesGenerated, nodesExpanded);
}

void MinMaxAlphaBeta3(int choice) { //option 3
    int counter = choice;
    clock_t time_req;
    time_req = clock();
    Checker checker;

    char winner = checker.winningPlayer();
    char player = 'A';

    Step ArepeatStep; // detect if in the loop
    Step BrepeatStep; // detect if in the loop

    ArepeatStep.heuristic_value1 = -1000;
    ArepeatStep.row1 = -1;
    ArepeatStep.col1 = -1;
    ArepeatStep.id1 = -1;
    ArepeatStep.heuristic_value2 = -1000;
    ArepeatStep.row2 = -1;
    ArepeatStep.col2 = -1;
    ArepeatStep.id2 = -1;
    BrepeatStep.heuristic_value1 = -1000;
    BrepeatStep.row1 = -1;
    BrepeatStep.col1 = -1;
    BrepeatStep.id1 = -1;
    BrepeatStep.heuristic_value2 = -1000;
    BrepeatStep.row2 = -1;
    BrepeatStep.col2 = -1;
    BrepeatStep.id2 = -1;
    bool notfound = true;

    Step stepArrayA[12]; // index means each piece id of player A
    Step stepArrayB[12]; // index means each piece id of player B

    for (int i = 0; i < 12; i++) {
        stepArrayA[i] = ArepeatStep;
    }
    for (int i = 0; i < 12; i++) {
        stepArrayB[i] = BrepeatStep;
    }

    int shift = 1;
    Checker checker1;
    Checker checker2;
    Object useVal(1000, checker1, 0, -1, -1);
    Object passVal(-1000, checker2, 0, -1, -1);
    Object alpha(-1000, checker1, 0, -1, -1);
    Object beta(1000, checker2, 0, -1, -1);

    while (winner == 'N') {
        steps++;
        CheckerTree *headptr = new CheckerTree(player);
        headptr->newCurrentBoard(checker);
        Object v;
        if (counter == 1) {
            if (shift % 2 == 1) { //start with A
                v = MinMaxAB(headptr, 1, player, useVal, passVal, 1);
            } else {
                v = alphabeta(headptr, 1, player, alpha, beta, 1);
            }
        }
        if (counter == 2) {
            if (shift % 2 == 1) { //start with A
                v = MinMaxAB(headptr, 1, player, useVal, passVal, 2);
            } else {
                v = alphabeta(headptr, 1, player, alpha, beta, 2);
            }
        }
        if (counter == 3) {
            if (shift % 2 == 1) { //start with A
                v = MinMaxAB(headptr, 1, player, useVal, passVal, 3);
            } else {
                v = alphabeta(headptr, 1, player, alpha, beta, 3);
            }
        }

        int temp_r = -1;
        int temp_c = -1;
        int temp_id = 0;
        int temp_r1 = -1;
        int temp_c1 = -1;
        int temp_id1 = 0;
        int current_id = v.id;
        int counterA = -1;
        int counterB = -1;
        bool notfound = true;
        if (player == 'A') {
            counterA = getMoveableCount(player, &headptr->currentboard);
        }
        if (player == 'B') {
            counterB = getMoveableCount(player, &headptr->currentboard);
        }

        if (player == 'A') {
                checkMoveable(player, &stepArrayA[current_id], v);
                getTotalPieceNum('A',&headptr->currentboard);

            while (checkMoveable(player, &stepArrayA[current_id], v) == 0) {
                if (counterA > 0) {
                    checker.setNotMoveable(player, ArepeatStep.row1, ArepeatStep.col1, ArepeatStep.id1);
                    checker.setNotMoveable(player, ArepeatStep.row2, ArepeatStep.col2, ArepeatStep.id2);
                    if(ArepeatStep.row1 == -1 && ArepeatStep.row2 == -1){
                        ArepeatStep.col1 = v.col;
                        ArepeatStep.row1 = v.row;
                        ArepeatStep.id1 = v.id;
                        ArepeatStep.heuristic_value1 = v.value;
                    }

                    if(ArepeatStep.row1 != -1 && ArepeatStep.row2 == -1){
                        ArepeatStep.col2 = v.col;
                        ArepeatStep.row2 = v.row;
                        ArepeatStep.id2 = v.id;
                        ArepeatStep.heuristic_value2 = v.value;
                    }

                    if (v.row == ArepeatStep.row1 && v.col == ArepeatStep.col1) {
                        temp_r1 = v.row;
                        temp_c1 = v.col;
                        temp_id1 = v.id;
                        temp_id = ArepeatStep.id2;
                        temp_r = ArepeatStep.row2;
                        temp_c = ArepeatStep.col2;
                        int tempr, tempc, tempid, temph;
                        tempc = ArepeatStep.col1;
                        tempr = ArepeatStep.row1;
                        tempid = ArepeatStep.id1;
                        temph = ArepeatStep.heuristic_value1;
                        ArepeatStep.col1 = ArepeatStep.col2;
                        ArepeatStep.row1 = ArepeatStep.row2;
                        ArepeatStep.id1 = ArepeatStep.id1;
                        ArepeatStep.heuristic_value1 = ArepeatStep.heuristic_value2;
                        ArepeatStep.col2 = tempc;
                        ArepeatStep.row2 = tempr;
                        ArepeatStep.id2 = tempid;
                        ArepeatStep.heuristic_value2 = temph;
                    } else if (v.row == ArepeatStep.row2 && v.col == ArepeatStep.col2){
                        temp_r = v.row;
                        temp_c = v.col;
                        temp_id = v.id;
                        temp_r1 = ArepeatStep.row2;
                        temp_c1 = ArepeatStep.col2;
                        temp_id1 = ArepeatStep.id2;
                    }
                    else {
                        ArepeatStep.col2 = v.col;
                        ArepeatStep.row2 = v.row;
                        ArepeatStep.id2 = v.id;
                        ArepeatStep.heuristic_value2 = v.value;
                    }

                    headptr->newCurrentBoard(checker);

                    if (counter == 1) { //start with A
                        v = MinMaxAB(headptr, 1, player, useVal, passVal, 1);
                    }
                    if (counter == 2) {
                        v = MinMaxAB(headptr, 1, player, useVal, passVal, 2);
                    }
                    if (counter == 3) {
                        v = MinMaxAB(headptr, 1, player, useVal, passVal, 3);
                    }
                    checker.setMoveable(player, temp_r, temp_c, temp_id);
                    checker.setMoveable(player, temp_r1, temp_c1, temp_id1);
                    counterA--;
                } else {
                    if(getTotalPieceNum('A',&headptr->currentboard)<=2) {
                        notfound = false;
                    }
                    break;

                }
            }
        }
        if (player == 'B') {
                checkMoveable(player, &stepArrayA[current_id], v);
                getTotalPieceNum('A',&headptr->currentboard);
            while (checkMoveable(player, &stepArrayB[current_id], v) == 0) {
                if (counterB > 0) {
                    checker.setNotMoveable(player, BrepeatStep.row1, BrepeatStep.col1, BrepeatStep.id1);
                    checker.setNotMoveable(player, BrepeatStep.row2, BrepeatStep.col2, BrepeatStep.id2);
                    if(BrepeatStep.row1 == -1 && BrepeatStep.row2 == -1){
                        BrepeatStep.col1 = v.col;
                        BrepeatStep.row1 = v.row;
                        BrepeatStep.id1 = v.id;
                        BrepeatStep.heuristic_value1 = v.value;
                    }
                    if(BrepeatStep.row1 != -1 && BrepeatStep.row2 == -1){
                        BrepeatStep.col2 = v.col;
                        BrepeatStep.row2 = v.row;
                        BrepeatStep.id2 = v.id;
                        BrepeatStep.heuristic_value2 = v.value;
                    }
                    if (v.row == BrepeatStep.row1 && v.col == BrepeatStep.col1) {
                        temp_r1 = v.row;
                        temp_c1 = v.col;
                        temp_id1 = v.id;
                        temp_id = BrepeatStep.id2;
                        temp_r = BrepeatStep.row2;
                        temp_c = BrepeatStep.col2;
                        int tempr, tempc, tempid, temph;
                        tempc = BrepeatStep.col1;
                        tempr = BrepeatStep.row1;
                        tempid = BrepeatStep.id1;
                        temph = BrepeatStep.heuristic_value1;
                        BrepeatStep.col1 = BrepeatStep.col2;
                        BrepeatStep.row1 = BrepeatStep.row2;
                        BrepeatStep.id1 = BrepeatStep.id1;
                        BrepeatStep.heuristic_value1 = BrepeatStep.heuristic_value2;
                        BrepeatStep.col2 = tempc;
                        BrepeatStep.row2 = tempr;
                        BrepeatStep.id2 = tempid;
                        BrepeatStep.heuristic_value2 = temph;
                    } else {
                        temp_r = v.row;
                        temp_c = v.col;
                        temp_id = v.id;
                        temp_r1 = BrepeatStep.row2;
                        temp_c1 = BrepeatStep.col2;
                        temp_id1 = BrepeatStep.id2;
                    }
                    BrepeatStep.col2 = v.col;
                    BrepeatStep.row2 = v.row;
                    BrepeatStep.id2 = v.id;
                    BrepeatStep.heuristic_value2 = v.value;

                    headptr->newCurrentBoard(checker);
                    if (counter == 1) { //start with A
                        v = alphabeta(headptr, 1, player, alpha, beta, 1);
                    }
                    if (counter == 2) {
                        v = alphabeta(headptr, 1, player, alpha, beta, 2);
                    }
                    if (counter == 3) {
                        v = alphabeta(headptr, 1, player, alpha, beta, 3);
                    }
                    checker.setMoveable(player, temp_r, temp_c, temp_id);
                    checker.setMoveable(player, temp_r1, temp_c1, temp_id1);
                    counterB--;
                } else {
                    if( getTotalPieceNum('B',&headptr->currentboard)<=2) {
                        notfound = false;
                    }
                    break;
                }
            }
        }
        if(player == 'A'&& v.value == -1000){
            winner = 'B';
            continue;
        }
        if(player=='B'&& v.value == 1000){
            winner = 'A';
            continue;
        }
//        cout<<"\n** In step "<<steps<<": "<< player << v.id<< "(" << v.value;
//        cout << ") moved to row  : " << v.row<<   " and column "<< v.col << endl;
        player = checker.choosePlayer(player, v.id, v.row, v.col);
//        checker.displayCheckerBoard();
        winner = checker.winningPlayer();
        shift++;
    }
    int executionTime = clock() - time_req;
    checker.displayCheckerBoard();
    displayResult(winner, executionTime, nodesGenerated, nodesExpanded);
}

void MinMaxUser4() { //Both use evaluation 2
    clock_t time_req;
    time_req = clock();
    Checker checker;
//    cout << "Lets begin the game" << endl;
//    cout << " Checker Board\n" << endl;
//    checker.displayCheckerBoard();
    char winner = checker.winningPlayer();
    char player = 'A';
//    int evaluation1 = 1;
    int evaluation2 = 2;
    int shift = 1;
    Checker ck1;
    Checker ck2;

    Object useVal(1000, ck1, 0, -1, -1);
    Object passVal(-1000, ck2, 0, -1, -1);
    Object alpha(-1000, ck1, 0, -1, -1);
    Object beta(1000, ck2, 0, -1, -1);

    while (winner == 'N') {
        steps++;
        CheckerTree *headptr = new CheckerTree(player);
        headptr->newCurrentBoard(checker);
        cout << "***Chance of " << player << "****" << endl;
        Object v;
        if (shift % 2 == 1) { //start with A
            v = MinMaxAB(headptr, 1, player, useVal, passVal, evaluation2);
        } else {
            int id = 0;
            int row = -1;
            int col = -1;
            cout << "\n Please input id: ";
            cin >> id;
            cout << "\n Please input row : ";
            cin >> row;
            cout << "\n Please input col: ";
            cin >> col;
            v.id = id;
            v.row = row;
            v.col = col;
        }
//        cout << "\n** In step " << steps << ": " << player << v.id << "(" << v.value;
//        cout << ") moved to row  : " << v.row << " and column " << v.col << endl;
        player = checker.choosePlayer(player, v.id, v.row, v.col);
        checker.displayCheckerBoard();
        winner = checker.winningPlayer();
        shift++;
        nodesGenerated = headptr->getnodeGenerated();
        nodesExpanded = headptr->getnodeExpanded();
    }
    int executionTime = clock() - time_req;
    checker.displayCheckerBoard();
    displayResult(winner, executionTime, nodesGenerated, nodesExpanded);
}

void AlphaBetaUser5() { //Both use evaluation 2
    clock_t time_req;
    time_req = clock();
    Checker checker;

    char winner = checker.winningPlayer();
    char player = 'A';
//    int evaluation1 = 1;
    int evaluation2 = 2;
    int shift = 1;
    Checker ck1;
    Checker ck2;

    Object useVal(1000, ck1, 0, -1, -1);
    Object passVal(-1000, ck2, 0, -1, -1);
    Object alpha(1000, ck1, 0, -1, -1);
    Object beta(-1000, ck2, 0, -1, -1);

    while (winner == 'N') {
        steps++;
        CheckerTree *headptr = new CheckerTree(player);
        headptr->newCurrentBoard(checker);
        cout << "*** Chance of " << player << "****" << endl;
        Object v;
        if (shift % 2 == 1) { //start with A
            v = alphabeta(headptr, 1, player, alpha, beta, 1);
        } else {
            int id = 0;
            int row = -1;
            int col = -1;
            cout << "\n Please input id: ";
            cin >> id;
            cout << "\n Please input row : ";
            cin >> row;
            cout << "\n Please input col: ";
            cin >> col;
            v.id = id;
            v.row = row;
            v.col = col;
        }

//        cout << "\n** In step " << steps << ": " << player << v.id << "(" << v.value;
//        cout << ") moved to row  : " << v.row << " and column " << v.col << endl;
        player = checker.choosePlayer(player, v.id, v.row, v.col);
        checker.displayCheckerBoard();
        winner = checker.winningPlayer();
        shift++;
        nodesGenerated = headptr->getnodeGenerated();
        nodesExpanded = headptr->getnodeExpanded();
    }
    int executionTime = clock() - time_req;
    checker.displayCheckerBoard();
    displayResult(winner, executionTime, nodesGenerated, nodesExpanded);
}

int main() {
    gameMenu();
    return 0;
}


void gameMenu() {

    Checker checker;
    cout << "Lets begin the game" << endl;
//    cout << " Checker Board" << endl;
    checker.displayCheckerBoard();

    int menu;
    cout << "\n/*******Checker Game(8X8)****/" << endl;
    cout << "/****** Choose menu option from 1-11 ********/" << endl;
    cout << "/***** Select 1 for MinMaxAB(EF1) VS MinMaxAB(EF2)****/ " << endl;
    cout << "/***** Select 2 for MinMaxAB(EF1) VS MinMaxAB(EF3)****/ " << endl;
    cout << "/***** Select 3 for MinMaxAB(EF2) VS MinMaxAB(EF3)****/ " << endl;
    cout << "/***** Select 4 for AlphaBeta(EF1) VS AlphaBeta(EF2)**/ " << endl;
    cout << "/***** Select 5 for AlphaBeta(EF1) VS AlphaBeta(EF3)**/ " << endl;
    cout << "/***** Select 6 for AlphaBeta(EF2) VS AlphaBeta(EF3)**/ " << endl;
    cout << "/******Select 7 for MinMaxAB(EF1) VS AlphaBeta(EF1)**/ " << endl;
    cout << "/**** Select 8 for MinMaxAB(EF2) VS AlphaBeta(EF2)*/ " << endl;
    cout << "/**** Select 9 for MinMaxAB(EF3) VS AlphaBeta(EF3)*/ " << endl;
    cout << "/**** Select 10 for MinMaxAB vs User */ " << endl;
    cout << "/**** Select 11 for AlphaBeta vs User */ " << endl;

    cin >> menu;

    switch (menu) {
        case 1:
            MinMax1(1);
            break;
        case 2:
            MinMax1(2);

            break;
        case 3:
            MinMax1(3);
            break;
        case 4:
            AlphaBeta2(1);
            break;
        case 5:
            AlphaBeta2(2);
            break;
        case 6:
            AlphaBeta2(3);
            break;
        case 7:
            MinMaxAlphaBeta3(1);
            break;
        case 8:
            MinMaxAlphaBeta3(2);
            break;
        case 9:
            MinMaxAlphaBeta3(3);
            break;
        case 10:
            MinMaxUser4();
            break;
        case 11:
            AlphaBetaUser5();
            break;
            //add for demo
        case 12:
            MinMax1(1);
            MinMax1(2);
            MinMax1(3);
            break;
        case 13:
            AlphaBeta2(1);
            AlphaBeta2(2);
            AlphaBeta2(3);
            break;
        case 14:
            MinMaxAlphaBeta3(1);
            MinMaxAlphaBeta3(2);
            MinMaxAlphaBeta3(3);
            break;

    }

}

