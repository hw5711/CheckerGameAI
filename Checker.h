
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

    //Checker(int[], int[], int, int);

    //Checker(const Checker &);

    char move_A(char , int , int , int);

    char move_B(char , int , int , int );

    char move(char , int , int , int );

    // int evaluation();
    char checkWin();

    void setBoard(char, int, int, char,int, int);

 //   void operator=(Checker);

    void displayBoard();

    //bool checkLegealMove(char player, int hole);

    char getPlayer(int, int);

    char getRole(int, int);

    int getId(int, int);

    int get_heuristic_value_board();

    void set_heuristic_value_board(int);

    //void getChildLocation(char, int, int, int);

    int getHeuristicValue() const;

    void setHeuristicValue(int heuristicValue);

    const Address &getAddress() const;

    void setAddress(const Address &address);
};


#endif /* Checker_hpp */
