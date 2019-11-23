
#include <iostream>
#include <ctime>
#include "CheckerTree.h"
#include "Checker.h"
#include "MinMaxAB.h"
#include "Object.h"
#include "AlphaBeta.h"
#include <stdio.h>

using namespace std;

struct Step{
    int heuristic_value;
    int row;
    int col;
    int id; // keep track of each piece last 2 steps
};

int nodesGenerated, nodesExpanded, steps;
void gameMenu();

int getMoveableCount(char player, Checker *ck){
    int cA = 0;
    int cB = 0;

    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if(ck->board[i][j].player == player && player == 'A'
               && ck->board[i][j].moveable == true){
                cA++;
            }
            if(ck->board[i][j].player == player && player == 'B'
               && ck->board[i][j].moveable == true){
                cB++;
            }
        }
    }
    if(player =='A') return cA;
    if(player =='B') return cB;
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

    cout << "No: of nodes expanded : " << nodesExpanded << endl;
    cout << "No: of nodes generated : " << nodesGenerated<< endl;
    cout << "Total length of path : " << steps << endl;
    cout << "Memory need for 1 node is: 1236 bytes." << endl;
    int x = 1236 * nodesGenerated;
    cout << "Total memory needed for the algorithm is : " << x << "bytes = " << x / (1024) << "kb" <<endl;
}

bool checkMoveable(char player, Step *repeat, Object v ){
    //two are empty
    if(repeat[0].row == -1 && repeat[1].row == -1) {
        repeat[0].heuristic_value = v.value;
        repeat[0].row = v.row;
        repeat[0].col = v.col;
        return true;
    }
    //second one is empty and not equal to first one
    if(repeat[0].row != -1 && repeat[1].row == -1){
        if(repeat[0].heuristic_value != v.value || repeat[0].row != v.row || repeat[0].col != v.col){
            repeat[1].heuristic_value = v.value;
            repeat[1].row = v.row;
            repeat[1].col = v.col;
            return true;
        }
        //equal to the first one
        if(repeat[0].heuristic_value == v.value && repeat[1].row != v.row && repeat[0].col == v.col){
            return false;
        }
    }
    //both are not empty
    if(repeat[0].row != -1 && repeat[1].row != -1 ) {
        //match first one
        if (repeat[0].heuristic_value == v.value && repeat[0].row == v.row && repeat[0].col == v.col) {
            if (repeat[1].heuristic_value != v.value || repeat[1].row != v.row || repeat[1].col != v.col) {
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
                return false;
            }
        }
        repeat[0].heuristic_value = repeat[1].heuristic_value;
        repeat[0].row = repeat[1].row;
        repeat[0].col = repeat[1].col;
        repeat[1].heuristic_value = v.value;
        repeat[1].row = v.row;
        repeat[1].col = v.col;
        return true;
    }
    return true;
}

//MinmaxAB vs MinmaxAB ( using ev1,ev2)
void MinMax1() {  //option 1
    int counter = 1;
    do {
        clock_t time_req;
        time_req = clock();
        char player = 'A';
        Checker checker; // checker is the board to be displayed
        char winner = checker.winningPlayer();
//        cout << "Lets begin the game" << endl;
//        cout << " Checker Board\n" << endl;
       // checker.displayCheckerBoard();

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

        Step stepArrayA[12]; // index means each piece id of player A
        Step stepArrayB[12]; // index means each piece id of player B

        for(int i=0; i<12; i++){
            stepArrayA[i] = ArepeatStep[2];
        }
        for(int i=0; i<12; i++){
            stepArrayB[i] = ArepeatStep[2];
        }

        Checker checker1;
        Checker checker2;
        Object useVal(1000, checker1, 0, -1, -1);
        Object passVal(-1000, checker2, 0, -1, -1);

        int evaluation1 = 1;
        int evaluation2 = 2;
        int evaluation3 = 3;
        int n;
        while (winner == 'N') {
            steps++;
            CheckerTree *headptr = new CheckerTree(player);
            headptr->newCurrentBoard(checker);
            //cout << "***Chance of " << player << "****" << endl;
            Object v;
            if (counter == 1) { //start with A
                v = MinMaxAB(headptr, 1, player, useVal, passVal, evaluation1);
            }
            if (counter == 2) {
                v = MinMaxAB(headptr, 1, player, useVal, passVal, evaluation2);
            }
            if(counter == 3){
                v = MinMaxAB(headptr, 1, player, useVal, passVal, evaluation3);
            }

            int temp_r = -1;
            int temp_c = -1;
            int temp_r1 = -1;
            int temp_c1 = -1;
            int temp_id = 0;
            int current_id = v.id;
            int counterA = -1;
            int counterB = -1;
            if(player == 'A'){
                counterA = getMoveableCount(player, &headptr->currentboard);
//                cout << "\nHow many moveable A: "<< counterA << endl;
            }
            if(player == 'B') {
                counterB = getMoveableCount(player, &headptr->currentboard);
//                cout << "\nHow many moveable B: " << counterB << endl;
            }

            if (player == 'A'){
                while(checkMoveable(player, &stepArrayA[current_id], v) == false)
               {
                    if(counterA > 0) {
                        checker.setNotMoveable(player, ArepeatStep[0].row, ArepeatStep[0].col, ArepeatStep[0].id);
                        checker.setNotMoveable(player, ArepeatStep[1].row, ArepeatStep[1].col, ArepeatStep[1].id);
                        if (v.row == ArepeatStep[0].row && v.col == ArepeatStep[0].col) {
                            temp_r1 = v.row;
                            temp_c1 = v.col;
                        } else {
                            ArepeatStep[0].row = v.row;
                            ArepeatStep[0].col = v.col;
                        }
                        temp_id = ArepeatStep[1].id;
                        temp_r = ArepeatStep[1].row;
                        temp_c = ArepeatStep[1].col;
                        headptr->newCurrentBoard(checker);
                        v = MinMaxAB(headptr, 1, player, useVal, passVal, counter);
                        checker.setMoveable(player, temp_r, temp_c, temp_id);
                        checker.setMoveable(player, temp_r1, temp_c1, temp_id);
                        counterA--;
                    }
                    else break;
                }
            }


            if(player == 'B'){
                while(checkMoveable(player, &stepArrayB[current_id], v) == false) {
                    if(counterB > 0) {
                        checker.setNotMoveable(player, BrepeatStep[0].row, BrepeatStep[0].col, BrepeatStep[0].id);
                        checker.setNotMoveable(player, BrepeatStep[1].row, BrepeatStep[1].col, BrepeatStep[1].id);
                        if(v.row == BrepeatStep[0].row && v.col == BrepeatStep[0].col ) {
                            temp_r1 = v.row;
                            temp_c1 = v.col;
                        }else{
                            BrepeatStep[0].row = v.row;
                            BrepeatStep[0].col = v.col;
                        }
                        temp_id = BrepeatStep[1].id;
                        temp_r = BrepeatStep[1].row;
                        temp_c = BrepeatStep[1].col;
                        headptr->newCurrentBoard(checker);
                        v = MinMaxAB(headptr, 1, player, useVal, passVal, counter);
                        checker.setMoveable(player, temp_r, temp_c, temp_id);
                        checker.setMoveable(player, temp_r1, temp_c1, temp_id);
                        counterB--;
                    }
                    else break;
                }
            }
            v = MinMaxAB(headptr, 1, player, useVal, passVal, counter);

//            cout << "\n** In step " << steps << ": " << player << v.getId() << "(" << v.getValue();
//            cout << ") moved to row  : " << v.getRow() << " and column " << v.getCol() << endl;
            player = checker.choosePlayer(player, v.getId(), v.getRow(), v.getCol());
           //checker.displayCheckerBoard();
            winner = checker.winningPlayer();
            nodesGenerated = headptr->getnodeGenerated();
            nodesExpanded = headptr->getnodeExpanded();
        }
        int executionTime = clock() - time_req;
        cout<<"\n*******  Here is the result of Option 1 with evaluation "<< counter << "  ********"<< endl;
        checker.displayCheckerBoard();
        displayResult(winner, executionTime, nodesGenerated, nodesExpanded);
        counter ++;
    }while(counter < 4);
}

//AlphaBeta vs AlphaBeta

void AlphaBeta2() {  //option 2
    int counter = 1;
    do {
    clock_t time_req;
    time_req = clock();
    Checker checker;
    //cout << "Lets begin the game" << endl;
    //cout<<" Checker Board\n"<<endl;
   // checker.displayCheckerBoard();
    char winner = checker.winningPlayer();
    char player = 'A';
    int evaluation1 = 1;
    int evaluation2 = 2;
    int evaluation3 = 3;
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

    Step stepArrayA[12]; // index means each piece id of player A
    Step stepArrayB[12]; // index means each piece id of player B

    for(int i=0; i<12; i++){
        stepArrayA[i] = ArepeatStep[2];
    }
    for(int i=0; i<12; i++){
        stepArrayB[i] = ArepeatStep[2];
    }

    Checker checker1;
    Checker checker2;
    Object alpha(1000,checker1,0,-1,-1);
    Object beta(-1000,checker2,0,-1,-1);

    while (winner == 'N') {
        steps++;
        CheckerTree *headptr = new CheckerTree(player);
        headptr->newCurrentBoard(checker);
       // cout << "***Chance of "<< player<<"****"<<endl;
        Object v;
        if(counter == 1) { //start with A
            v = alphabeta(headptr, 1, player, alpha, beta, evaluation1);
        }
        if(counter == 2){
            v = alphabeta(headptr, 1, player, alpha, beta, evaluation2);
        }
        if(counter == 3){
            v = alphabeta(headptr, 1, player, alpha, beta, evaluation3);
        }
        int temp_r = -1;
        int temp_c = -1;
        int temp_r1 = -1;
        int temp_c1 = -1;
        int temp_id = 0;
        int current_id = v.id;
        int counterA = -1;
        int counterB = -1;
        if(player == 'A'){
            counterA = getMoveableCount(player, &headptr->currentboard);
//                cout << "\nHow many moveable A: "<< counterA << endl;
        }
        if(player == 'B') {
            counterB = getMoveableCount(player, &headptr->currentboard);
//                cout << "\nHow many moveable B: " << counterB << endl;
        }

        if (player == 'A'){
            while(checkMoveable(player, &stepArrayA[current_id], v) == false)
            {
                if(counterA > 0) {
                    checker.setNotMoveable(player, ArepeatStep[0].row, ArepeatStep[0].col, ArepeatStep[0].id);
                    checker.setNotMoveable(player, ArepeatStep[1].row, ArepeatStep[1].col, ArepeatStep[1].id);
                    if (v.row == ArepeatStep[0].row && v.col == ArepeatStep[0].col) {
                        temp_r1 = v.row;
                        temp_c1 = v.col;
                    } else {
                        ArepeatStep[0].row = v.row;
                        ArepeatStep[0].col = v.col;
                    }
                    temp_id = ArepeatStep[1].id;
                    temp_r = ArepeatStep[1].row;
                    temp_c = ArepeatStep[1].col;
                    headptr->newCurrentBoard(checker);
                    v = MinMaxAB(headptr, 1, player, alpha, beta, counter);
                    checker.setMoveable(player, temp_r, temp_c, temp_id);
                    checker.setMoveable(player, temp_r1, temp_c1, temp_id);
                    counterA--;
                }
                else break;
            }
        }


        if(player == 'B'){
            while(checkMoveable(player, &stepArrayB[current_id], v) == false) {
                if(counterB > 0) {
                    checker.setNotMoveable(player, BrepeatStep[0].row, BrepeatStep[0].col, BrepeatStep[0].id);
                    checker.setNotMoveable(player, BrepeatStep[1].row, BrepeatStep[1].col, BrepeatStep[1].id);
                    if(v.row == BrepeatStep[0].row && v.col == BrepeatStep[0].col ) {
                        temp_r1 = v.row;
                        temp_c1 = v.col;
                    }else{
                        BrepeatStep[0].row = v.row;
                        BrepeatStep[0].col = v.col;
                    }
                    temp_id = BrepeatStep[1].id;
                    temp_r = BrepeatStep[1].row;
                    temp_c = BrepeatStep[1].col;
                    headptr->newCurrentBoard(checker);
                    v = MinMaxAB(headptr, 1, player, alpha, beta, counter);
                    checker.setMoveable(player, temp_r, temp_c, temp_id);
                    checker.setMoveable(player, temp_r1, temp_c1, temp_id);
                    counterB--;
                }
                else break;
            }
        }
        v = MinMaxAB(headptr, 1, player, alpha, beta, counter);

//        cout<<"\n** In step " <<steps<<": "<< player << v.id<< "(" << v.value;
//        cout << ") moved to row  : "<< v.row<< " and column "" - "<< v.col << endl;
        player = checker.choosePlayer(player, v.id, v.row, v.col);
        //checker.displayCheckerBoard();
        winner = checker.winningPlayer();
        shift++;
        nodesGenerated= headptr->getnodeGenerated();
        nodesExpanded=headptr->getnodeExpanded();
    }
    int executionTime = clock()- time_req;
    //checker.displayCheckerBoard();
        cout<<"\n*******  Here is the result of Option 2 with evaluation "<< counter << "  ********"<< endl;
    displayResult(winner, executionTime, nodesGenerated,nodesExpanded);
        counter ++;
    }while(counter < 4);
}

void MinMaxAlphaBeta1() { //option 3
    clock_t time_req;
    time_req = clock();
    Checker checker;
    cout << "Lets begin the game" << endl;
    cout<<" Checker Board\n"<<endl;
    checker.displayCheckerBoard();
    char winner = checker.winningPlayer();
    char player = 'A';
    int evaluation1 = 1;
    int evaluation2 = 2;
    int shift = 1;
    Checker checker1;
    Checker checker2;

    Object useVal(1000,checker1,0,-1,-1);
    Object passVal(-1000,checker2,0,-1,-1);
    Object alpha(1000,checker1,0,-1,-1);
    Object beta(-1000,checker2,0,-1,-1);

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

    Step stepArrayA[12]; // index means each piece id of player A
    Step stepArrayB[12]; // index means each piece id of player B

    for(int i=0; i<12; i++){
        stepArrayA[i] = ArepeatStep[2];
    }
    for(int i=0; i<12; i++){
        stepArrayB[i] = ArepeatStep[2];
    }

    while (winner == 'N') {
        steps++;
        CheckerTree *headptr = new CheckerTree(player);
        headptr->newCurrentBoard(checker);
        //cout << "***Chance of "<< player<<"****"<<endl;
        Object v;
        if(shift %2 == 1) { //start with A
            v = MinMaxAB(headptr, 1, player, useVal, passVal, evaluation1);
        }else{
            v = alphabeta(headptr, 1, player, alpha, beta, evaluation1);
        }
//        int temp_r = -1;
//        int temp_c = -1;
//        int temp_r1 = -1;
//        int temp_c1 = -1;
//        while(player == 'A' && checkMoveable(player, ArepeatStep, v) == false) {
//            checker.setNotMoveable(player, ArepeatStep[0].row, ArepeatStep[0].col);
//            checker.setNotMoveable(player, ArepeatStep[1].row, ArepeatStep[1].col);
//            if(v.row == ArepeatStep[0].row && v.col == ArepeatStep[0].col ) {
//                temp_r1 = v.row;
//                temp_c1 = v.col;
//            }else{
//                ArepeatStep[0].row = v.row;
//                ArepeatStep[0].col = v.col;
//            }
//            temp_r = ArepeatStep[1].row;
//            temp_c = ArepeatStep[1].col;
//            headptr->newCurrentBoard(checker);
//            v = alphabeta(headptr, 1, player, alpha, beta, evaluation1);
//            checker.setMoveable(player, temp_r, temp_c);
//            checker.setMoveable(player, temp_r1, temp_c1);
//        }
//        while(player == 'B' && checkMoveable(player, BrepeatStep, v) == false) {
//            checker.setNotMoveable(player, BrepeatStep[0].row, BrepeatStep[0].col);
//            checker.setNotMoveable(player, BrepeatStep[1].row, BrepeatStep[1].col);
//            if(v.row == BrepeatStep[0].row && v.col == BrepeatStep[0].col ) {
//                temp_r1 = v.row;
//                temp_c1 = v.col;
//            }else{
//                BrepeatStep[0].row = v.row;
//                BrepeatStep[0].col = v.col;
//            }
//            temp_r = BrepeatStep[1].row;
//            temp_c = BrepeatStep[1].col;
//            headptr->newCurrentBoard(checker);
//            v = alphabeta(headptr, 1, player, alpha, beta, evaluation2);
//            checker.setMoveable(player, temp_r, temp_c);
//            checker.setMoveable(player, temp_r1, temp_c1);
//        }
        cout<<"\n** In step "<<steps<<": "<< player << v.id<< "(" << v.value;
        cout << ") moved to row  : " << v.row<<   " and column "<< v.col << endl;
        player = checker.choosePlayer(player, v.id, v.row, v.col);
        //ck.displayBoard();
        winner = checker.winningPlayer();
        shift++;
        nodesGenerated= headptr->getnodeGenerated();
        nodesExpanded=headptr->getnodeExpanded();
    }
    int executionTime = clock()- time_req;
    checker.displayCheckerBoard();
    displayResult(winner, executionTime, nodesGenerated,nodesExpanded);

}

void MinMaxAlphaBeta2() { //Both use evaluation 2
    clock_t time_req;
    time_req = clock();
    Checker checker;
    cout << "Lets begin the game" << endl;
    cout<<" Checker Board\n"<<endl;
    checker.displayCheckerBoard();
    char winner = checker.winningPlayer();
    char player = 'A';

    int evaluation2 = 2;
    int shift = 1;
    Checker ck1;
    Checker ck2;

    Object useVal(1000,ck1,0,-1,-1);
    Object passVal(-1000,ck2,0,-1,-1);
    Object alpha(1000,ck1,0,-1,-1);
    Object beta(-1000,ck2,0,-1,-1);

    while (winner == 'N') {
        steps++;
        CheckerTree *headptr = new CheckerTree(player);
        headptr->newCurrentBoard(checker);
        cout << "***Chance of "<< player<<"****"<<endl;
        Object v;
        if(shift %2 == 1) { //start with A
            v = MinMaxAB(headptr, 1, player, useVal, passVal, evaluation2);
        }else{
            v = alphabeta(headptr, 1, player, alpha, beta, evaluation2);
        }

        cout<<"\n** In step " <<steps<<": "<< player << v.id<< "(" << v.value;
        cout << ") moved to row  : "  << v.row<<   " and column "<< v.col << endl;
        player = checker.choosePlayer(player, v.id, v.row, v.col);
        checker.displayCheckerBoard();
        winner = checker.winningPlayer();
        shift++;
        nodesGenerated= headptr->getnodeGenerated();
        nodesExpanded=headptr->getnodeExpanded();
    }
    int executionTime = clock()- time_req;
    checker.displayCheckerBoard();
    displayResult(winner, executionTime, nodesGenerated,nodesExpanded);

}

void MinMaxUser() { //Both use evaluation 2
    clock_t time_req;
    time_req = clock();
    Checker checker;
    cout << "Lets begin the game" << endl;
    cout<<" Checker Board\n"<<endl;
    checker.displayCheckerBoard();
    char winner = checker.winningPlayer();
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

    while (winner == 'N') {
        steps++;
        CheckerTree *headptr = new CheckerTree(player);
        headptr->newCurrentBoard(checker);
        cout << "***Chance of "<< player<<"****"<<endl;
        Object v;
        if(shift %2 == 1) { //start with A
            v = MinMaxAB(headptr, 1, player, useVal, passVal, evaluation2);
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

        cout<<"\n** In step "<<steps<<": "<< player << v.id<< "(" << v.value;
        cout << ") moved to row  : " << v.row<<  " and column "<< v.col << endl;
        player = checker.choosePlayer(player, v.id, v.row, v.col);
        checker.displayCheckerBoard();
        winner = checker.winningPlayer();
        shift++;
        nodesGenerated= headptr->getnodeGenerated();
        nodesExpanded=headptr->getnodeExpanded();
    }
    int executionTime = clock()- time_req;
    checker.displayCheckerBoard();
    displayResult(winner, executionTime, nodesGenerated,nodesExpanded);
}


int main() {

    gameMenu();
    return 0;
}


void gameMenu(){

    int menu;
    cout << "/******************Checker Game(8X8)*************/" << endl;
    cout<<"/*****************Choose menu option from 1-4***********************/"<<endl;
    cout << "/*************** Select 1 for MinMaxAB(EF1, EF2, EF3)**********/ " << endl;
    cout << "/*************** Select 2 for AlphaBetaSearch(EF1) VS AlphaBetaSearch(EF2)****/ " << endl;
    cout << "/***************Select 3 for MinMaxAB(EF1) VS AlphaBetaSearch(EF1)*****/ " << endl;
    cout << "/************ Select 4 for MinMaxAB(EF2) VS AlphaBetaSearch(EF2)***/ " << endl;
    cout << "/************ Select 5 for MinMaxAB vs User ***/ " << endl;

    cin >> menu;

    switch (menu) {
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

}
