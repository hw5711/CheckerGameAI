#ifndef GameTree_hpp
#define GameTree_hpp

#include <stdio.h>
#include<iostream>
#include"Checker.h"

using namespace std;

class GameTree {

public:
    //StepInfo step;
    char player;
    Checker board_status; //contains board status including each location info
    int number_of_children;
    GameTree *children[48]; // one step has 4 directions choices(man+king)
    int row;//the row hold the best heuristic value
    int col;//the col hold the best heuristic value

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

    void copyBoardStatus(Checker kb);

    bool threaten(int, int, Checker, char);

    int *getChildLocation(Checker);
};


#endif /* GameTree_hpp */
