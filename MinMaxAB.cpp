
#include "MinMaxAB.h"
#include<iostream>

using namespace std;


Obj MinMaxAB(GameTree *board, int depth, char player, int UseT, int PassT, int EF) {
    Obj obj;
    int newVal;
    char NewPlayer;
//    cout<<"test1: " << board->
        if (board->deepenough(depth)) {
        obj.heuristic_value = board->evaluation();//will generate moved location
        cout<<"\nEvaluation value is : "<< obj.heuristic_value<<endl;
        if (player == 'B') {
            obj.heuristic_value = -obj.heuristic_value;
        }
        board->set_heuristic_value(obj.heuristic_value, obj.row, obj.col);
        return obj;
    }

    Obj obj1;
    obj1.heuristic_value = 0;
    obj1.row = 0;
    obj1.col = 0;

    for (int i = 0; i < 48; i++) { // need to update
        if (board->children[i] == NULL)
            continue;
        if (player == 'A')
            NewPlayer = 'B';
        else
            NewPlayer = 'A';

        obj1 = MinMaxAB(board->children[i], depth + 1, NewPlayer, -PassT, -UseT, EF);
        newVal = -obj1.heuristic_value;

        if (newVal > PassT) {
            board->set_heuristic_value(obj.heuristic_value, obj.row, obj.col);
            PassT = newVal;
        }
        if (PassT >= UseT) {
            obj1.heuristic_value = PassT;
            return obj1;
        }
    }
    obj1.heuristic_value = PassT;
    //board->set_heuristic_value(obj.heuristic_value, obj.row, obj.col);
    return obj1;
}
