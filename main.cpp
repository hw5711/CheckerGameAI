
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


void MinMax() {
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
        MinMaxAB(head, 0, player, 10000, -10000);

        Step hole;
        hole.heuristic_value = head->step.heuristic_value; // need to return new place and heuristic_value
        hole.row = head->step.row;
        hole.col = head->step.col;

        cout << "hole row # " << hole.row <<  "hole col # "<< hole.col << endl;
        player = ck->move(hole.row, hole.col, player);
        ck->displayBoard();
        win = ck->checkWin();
    }
    int stop_s = clock();
    int execution_time = stop_s - start_s;
    ck->displayBoard();
    print(win, execution_time);

}

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

        Step hole;
        hole.heuristic_value = head->step.heuristic_value; // need to return new place and heuristic_value
        hole.row = head->step.row;
        hole.col = head->step.col;

        player = ck->move(hole.row, hole.col, player);
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

    cout << "\n\t\t\tGame Ends-*\n" << endl;

    cout << "Execution time taken is : " << (execution_time) / double(CLOCKS_PER_SEC) << " seconds" << endl;
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
    cout << "Enter 1 for MinMaxAB " << endl;
    cout << "Enter 2 for AlphaBetaSearch " << endl;

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
