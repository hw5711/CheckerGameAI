#ifndef GameTree_hpp
#define GameTree_hpp

#include <stdio.h>
#include<iostream>
#include"Checker.h"

using namespace std;

struct StepInfo{
    int heuristic_value;
    int row;
    int clo;
};

class GameTree {

public:
    StepInfo heuristic_value;
    char player;
    Checker board_status;
    int number_of_children;
    GameTree *children[4]; // one step has 4 directions choices(man+king)

    GameTree();

    GameTree(char);

    void create_node(char);

    void set_heuristic_value(int, int, int);

    void add_all_children();

    bool deepenough(int);

    void print(GameTree *, int);

    int evaluation();

    int get_hole_number();

    void copyBoardStatus(Checker kb);
};


#endif /* GameTree_hpp */
