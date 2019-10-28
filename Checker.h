
#ifndef Checker_hpp
#define Checker_hpp

#include <stdio.h>
#include<iostream>

using namespace std;

class Checker {
public:
    int A[8][8], B[8][8];
    int winDecider, numberOfSlots;
    int (**ptr);

    Checker();

    Checker(int[], int[], int, int);

    Checker(Checker *);

    char move_A(int, int);

    char move_B(int, int);

    char move(int, int, char);

    // int evaluation();
    char checkWin();

    void operator=(Checker);

    void displayBoard();

    bool checkLegealMove(char player, int hole);
};


#endif /* Checker_hpp */
