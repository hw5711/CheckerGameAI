#ifndef GameTree_hpp
#define GameTree_hpp

#include <stdio.h>
#include<iostream>
#include"Checker.h"

using namespace std;

//struct StepInfo{
//    int heuristic_value;
//    int row;
//    int col;
//    char role;
//};

class GameTree {

public:
    //StepInfo step;
    char player;
    Checker board_status; //contains board status including each location info
    int number_of_children;
    GameTree *children[4]; // one step has 4 directions choices(man+king)

    GameTree();

    GameTree(char);

    void create_node(char);

    void set_heuristic_value(int, int, int);

    int get_heuristic_value();

    void add_all_children();

    bool deepenough(int);

    int* jump(int, int, Checker, char);

    void print(GameTree *, int);

    int evaluation();

    int get_hole_number();

    void copyBoardStatus(Checker kb);

    bool threaten(int, int, Checker, char);
};


#endif /* GameTree_hpp */
