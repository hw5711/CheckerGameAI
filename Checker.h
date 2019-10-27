
#ifndef Checker_hpp
#define Checker_hpp

#include <stdio.h>
#include<iostream>
using namespace std;

class Checker
{
public:
    int A[12],B[12];
    int checker_A,checker_B;
    int winDecider,numberOfSlots;
    int *ptr;
    
    Checker();
    Checker(int[],int[],int,int);
    Checker(Checker *);
    char move_A(int);
    char move_B(int);
    char move(int,char);
    // int evaluation();
    char checkWin();
    void operator=(Checker);
    void displayBoard();
    bool checkLegealMove(char player,int hole);
};


#endif /* Checker_hpp */
