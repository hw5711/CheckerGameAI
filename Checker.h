
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
    int id;
    int heuristic_value;
    bool moveable;
};

struct Address{
    int row_before;
    int col_before;
    int row_after;
    int col_after;
};

class Checker {
public:
    Board board[8][8];
    int heuristic_value;
    Address address;
    Checker();
    void setBoard(char, int, int, char,int, int, bool);

    void displayCheckerBoard();

    char getPlayer(int, int);

    char getRole(int, int);

    int getId(int, int);

    int get_heuristic_value_board();

    void set_heuristic_value_board(int);

    char chanceOfA(char , int , int , int);

    char chanceOfB(char , int , int , int );

    void setNotMoveable(char, int, int, int);

    char choosePlayer(char , int , int , int );

    void setMoveable(char, int, int, int);
    char winningPlayer();

};


#endif /* Checker_hpp */
