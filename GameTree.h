#ifndef GameTree_hpp
#define GameTree_hpp

#include <stdio.h>
#include<iostream>
#include"Checker.h"

using namespace std;

struct Location{
    int l1;
    int l2;
    int l3;
    int l4;
    int l5;
    int l6;
    int l7;
    int l8;
};

struct Add{
    int row_before;
    int col_before;
    int row_after;
    int col_after;
};

class GameTree {

public:
    //StepInfo step;
    char player;
    Checker board_status; //contains board status including each location info
    int number_of_children;
    GameTree *children[48]; // one step has 4 directions choices(man+king)
    int row;//the row hold the best heuristic value
    int col;//the col hold the best heuristic value
    Add address;

    GameTree();

    GameTree(char);

    void create_node(char);

    void set_heuristic_value(int);

    int get_heuristic_value();

    void add_all_children(char);

    bool deepenough(int, char);

    Location jump(int, int, Checker, char);

    void print(GameTree *, int);

    int evaluation(char);

    void copyBoardStatus(Checker kb);

    bool threaten(int, int, Checker, char);

    void getChildLocation(Checker);

    bool available_to_jump(Location);

    int getBeforeRow();

    int getBeforeCol();

    int getAfterRow();

    int getAfterCol();
};


#endif /* GameTree_hpp */
