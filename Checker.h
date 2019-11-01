
#ifndef Checker_hpp
#define Checker_hpp

#include <stdio.h>
#include<iostream>

using namespace std;

struct Board{
    char player;
    int row;
    int col;
    char role;
    int heuristic_value;
};

class Checker {
public:
    Board board[8][8];
    int heuristic_value;

    Checker();

    Checker(int[], int[], int, int);

    Checker(Checker *);

    char move_A(int, int);

    char move_B(int, int);

    char move(int, int, char);

    // int evaluation();
    char checkWin();

    void setBoard(char, int, int, char, int);

    void operator=(Checker);

    void displayBoard();

    bool checkLegealMove(char player, int hole);

    char getPlayer(int, int);

    int get_heuristic_value_board();

    void set_heuristic_value_board(int);
};


#endif /* Checker_hpp */
