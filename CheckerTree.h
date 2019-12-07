#ifndef CHECKERTREE_H
#define CHECKERTREE_H

#include <stdio.h>
#include<iostream>
#include"Checker.h"
#include"Object.h"

using namespace std;

struct Location {
    int l1;
    int l2;
    int l3;
    int l4;
    int l5;
    int l6;
    int l7;
    int l8;
};

struct Add {
    int row_before;
    int col_before;
    int row_after;
    int col_after;
};

class CheckerTree {
public:

    static int nodes_expanded;
    static int nodes_generated;
    char player;
    int row;// to strore the second child move to location of this board
    int col;// to strore the second child move to location of this board
    int id;
    Add address;
    int successors;
    Checker currentboard; //contains board status including each location info
    Checker heuristic_board; //store it's best children
    CheckerTree *successor[48]; // one step has 4 directions choices(man+king)
    CheckerTree();

    CheckerTree(char);

    bool deepenough(int, char);

    void newCurrentBoard(Checker);

    Location jump(int, int, Checker, char);

    void setHeuristicValue(int, Checker, int, int, int);

    int evaluation1(char);

    int evaluation2(char);

    int evaluation3(char);

    bool threaten(int, int, Checker, char);

    bool available_to_jump(Location);

    void generateChildren(char);

    void generateChildren2(char);

    void setRow(int row);

    void setCol(int col);

    void setId(int id);

    int getnodeGenerated();

    int getnodeExpanded();

};

#endif // CHECKERTREE_H
