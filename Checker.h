
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

    bool isMoveable() const;

    void setMoveable(bool moveable);
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

    char move_A(char , int , int , int);

    char move_B(char , int , int , int );

    char move(char , int , int , int );

    char checkWin();

    void setBoard(char, int, int, char,int, int, bool);

    void removeRepeat(char, int, int, int);

    void displayBoard();

    char getPlayer(int, int);

    char getRole(int, int);

    int getId(int, int);

    int get_heuristic_value_board();

    void set_heuristic_value_board(int);

    const Address &getAddress() const;

    void setAddress(const Address &address);

    int getPlayerNum(char);

    void setMoveable(char, int, int, int);
};


#endif /* Checker_hpp */
