
#include "MinMaxAB.h"
#include<iostream>

using namespace std;

Object MinMaxAB(GameTree *board, int depth, char player, Object useVal, Object passVal, int EF) {
    Object obj;
    Object newVal;
    char NewPlayer;

//    cout<<"test--MINMAXAB: "<< player << endl;
//    board->board_status.displayBoard();
    if (board->deepenough(depth,player)) {
        obj.value = board->evaluation(player);//will generate moved location
        obj.row = board->row;
        obj.col = board->col;
        // cout<<"\nEvaluation value is : "<<obj<<endl;
        if (player == 'B') {
            obj.setValue(-obj.getValue());
        }
        board->set_heuristic_value(obj.getValue(), obj.getRow(), obj.getCol());
//        cout<<"\ntest minimaxab --- obj: "<< obj<< endl;
        return obj;
    }
    Object obj1(0,-1,-1);

   // obj1.heuristic_value = 0;

    for (int i = 0; i < 48; i++) { // need to update
        if (board->children[i] == NULL)
            continue;
        if (player == 'A')
            NewPlayer = 'B';
        else
            NewPlayer = 'A';

        Object passVal1(passVal.getValue(),passVal.getRow(),passVal.getCol());
        Object useVal1(useVal.getValue(),useVal.getRow(),useVal.getCol());

        int temp = passVal1.getValue();
        passVal1.setValue(-useVal1.getValue());
        useVal1.setValue(-temp);

        int temp_r = passVal1.getRow();
        passVal1.setRow(useVal1.getRow());
        useVal1.setRow(temp_r);

        int temp_c = passVal1.getCol();
        passVal1.setCol(useVal1.getCol());
        useVal1.setCol(temp_c);

        obj1 = MinMaxAB(board->children[i], depth + 1, NewPlayer, useVal1, passVal1, EF);

        Object newVal(-obj1.getValue(), obj1.getRow(), obj1.getCol());

        if (newVal.getValue() > passVal.getValue()) {
            board->set_heuristic_value(i, newVal.getRow(), newVal.getCol());
            passVal.setValue(newVal.getValue());
            passVal.setRow(newVal.getRow());
            passVal.setCol(newVal.getCol());

        }
        if (passVal.getValue() >= useVal.getValue()) {
            obj1.setValue(passVal.getValue());
            obj1.setRow(passVal.getRow());
            obj1.setCol(passVal.getCol());
            return obj1;
        }
    }
    obj1.setValue(passVal.getValue());
    obj1.setRow(passVal.getRow());
    obj1.setCol(passVal.getCol());
    //board->set_heuristic_value(obj.heuristic_value, obj.row, obj.col);
    return obj1;
}
