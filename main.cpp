
#include <iostream>
#include <ctime>
#include "GameTree.h"
#include "Checker.h"
#include "AlphaBetaSearch.h"
#include "MinMaxAB.h"

using namespace std;

struct Step{
    int heuristic_value;
    int row;
    int col;
    char role; //k is king, m is man, e is empty
};

void print(char, int);

int nodes_generated, nodes_expanded, steps;

//MinmaxAB vs MinmaxAB
void MinMax() {
    Checker *ck = new Checker();
    cout << "Initial board " << endl;
    ck->displayBoard();
    char win = ck->checkWin();
    //cout <<" test 4: "<< win;
    char player = 'A';
    int start_s = clock();
    int shift = 1;
    while (win == 'N') {
        steps++;
        GameTree *head = new GameTree(player);
        head->copyBoardStatus(ck); //store current node info
        //cout <<" \ntest 5: "<< head->board_status.row;
        cout << "*****Turn*****" << player << endl;

        Step hole;
        int evaluation1 = 1;
        int evaluation2 = 2;

        if(shift %2 == 1) {
            cout<<"test 2";
            MinMaxAB(head, 1, player, 10000, -10000, evaluation1);
        }else{
            cout<<"test 3";
            MinMaxAB(head, 1, player, 10000, -10000, evaluation2);
        }

        hole.heuristic_value = head->board_status.heuristic_value; // need to return new place and heuristic_value
        cout <<" \ntest 4: "<< hole.heuristic_value;
        int *addr = NULL;
        addr = head->getChildLocation(ck);
        hole.row = *(addr+2);
        hole.col = *(addr+3);
        cout << "MOVE TO :hole row # " << hole.row <<  "\nhole col # "<< hole.col << endl;
        player = ck->move(*addr, *(addr+1),*(addr+2),*(addr+3), player);
        ck->displayBoard();
        win = ck->checkWin();
        shift++;
    }
    int stop_s = clock();
    int execution_time = stop_s - start_s;
    ck->displayBoard();
    print(win, execution_time);
}

//AlphaBeta vs AlphaBeta
void AlphaBeta() {
    Checker *ck = new Checker();
    cout << "Initial board " << endl;
    ck->displayBoard();
    char win = ck->checkWin();
    char player = 'A';
    int start_s = clock();
    while (win == 'N') {
        steps++;
        GameTree *head = new GameTree(player);
        head->copyBoardStatus(ck);
        cout << "*****Turn*****" << player << endl;
        alphabeta(head, 0, player, 1000, -1000);
        //head will contain best heristic value and location
        Step hole;
        hole.heuristic_value = head->board_status.heuristic_value; // need to return new place and heuristic_value
        int *addr = NULL;
        addr = head->getChildLocation(ck);
        hole.row = *(addr+2);
        hole.col = *(addr+3);
        cout << "MOVE TO :hole row # " << hole.row <<  "\nhole col # "<< hole.col << endl;
        player = ck->move(*addr, *(addr+1),*(addr+2),*(addr+3), player);
        ck->displayBoard();
        win = ck->checkWin();
    }
    int stop_s = clock();
    int execution_time = stop_s - start_s;
    ck->displayBoard();
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
   // cout << "Execution time taken is : " << (execution_time) / double(CLOCKS_PER_SEC) << " seconds" << endl;
}

void Statistics_print() {
    cout << "Number of nodes generated : " << nodes_generated << endl;
    cout << "Number of nodes expanded : " << nodes_expanded << endl;
    cout << "Number of steps : " << steps << endl;
    cout << "Memory need for 1 node is: 81 bytes." << endl;
    int x = 81 * nodes_generated;
    cout << "Total memory needed for the algorithm is : " << x << "bytes = " << x / (1024) << "ck" << endl;
    //cin>>x;
}

int main() {
    int choice_game;
    cout << "\t\t\tChecker Game(8X8)\n\t\t      *-*-*-*-*-*-*-*-*-*-*-*\n\t\t\t*-Game Begins" << endl;
    cout << "Enter 1 for MinMaxAB(EF1) VS MinMaxAB(EF2) " << endl;
    cout << "Enter 2 for AlphaBetaSearch(EF1) VS AlphaBetaSearch(EF2) " << endl;
    cout << "Enter 3 for MinMaxAB(EF1) VS AlphaBetaSearch(EF1) " << endl;
    cout << "Enter 4 for MinMaxAB(EF2) VS AlphaBetaSearch(EF2)  " << endl;

    cin >> choice_game;

    switch (choice_game) {
        case 1:
            MinMax();
            break;
        case 2:
            AlphaBeta();
            break;
    }
    // Statistics_print();

    return 0;
}
