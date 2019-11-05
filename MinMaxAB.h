
#ifndef MinMaxAB_hpp
#define MinMaxAB_hpp

#include "GameTree.h"
#include <stdio.h>
#include<iostream>

using namespace std;

struct Obj{
    int heuristic_value;
    int row;
    int col;
    char role;
};

Obj MinMaxAB(GameTree *, int, char, int, int, int);

#endif /* MinMaxAB_hpp */
