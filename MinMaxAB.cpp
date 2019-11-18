
#include "MinMaxAB.h"
#include<iostream>

using namespace std;

//use value is min, pass value is max
Object MinMaxAB(GameTree *board, int depth, char player, Object useVal, Object passVal, int EF) {
    Object obj;
    char NewPlayer;
    if (board->deepenough(depth,player)) { // if search to the bottom child
        if(EF == 1) {
            if(player == 'A'){
               // cout<<"\nMIN- A - value is : "<< board->evaluation1(player);
            }
            obj.setValue(board->evaluation1(player));
        }
        if(EF == 2) {
            obj.setValue(board->evaluation2(player));
        }
        obj.setTempBoard(board->board_status);
        if (player == 'B') {
            obj.setValue(-obj.getValue());
            //cout<<"\nMIN- B - value is : "<< obj.getValue()<<endl;
        }
        board->set_heuristic_value(obj.getValue(), obj.getTempBoard(),board->id, board->row ,board->col );
        obj.setId(board->id);
        obj.setRow(board->row);
        obj.setCol(board->col);
        return obj;
    }
    Checker ck;
    Object obj1(0, ck, 0, -1, -1);

    for (int i = 0; i < 48; i++) { // need to update
        if (board->children[i] == NULL) {
            continue;
        }
        if (player == 'A')
            NewPlayer = 'B';
        else
            NewPlayer = 'A';

        Object negPass;
        negPass.setValue(-useVal.getValue());
        negPass.setTempBoard(useVal.getTempBoard());
        negPass.setId(useVal.getId());
        negPass.setRow(useVal.getRow());
        negPass.setCol(useVal.getCol());

        Object negUse;
        negUse.setValue(-passVal.getValue());
        negUse.setTempBoard(passVal.getTempBoard());
        negUse.setId(passVal.getId());
        negUse.setRow(passVal.getRow());
        negUse.setCol(passVal.getCol());

        obj1 = MinMaxAB(board->children[i], depth + 1, NewPlayer, negPass, negUse, EF);
        Object newVal(-obj1.getValue(), obj1.getTempBoard(), obj1.getId(), obj1.getRow(), obj1.getCol());

        if (newVal.getValue() > passVal.getValue()) {
            board->children[i]->set_heuristic_value(newVal.getValue(),newVal.getTempBoard(),newVal.getId(), newVal.getRow() ,newVal.getCol() );
            passVal.setValue(newVal.getValue());
            passVal.setTempBoard(newVal.getTempBoard());
            passVal.setId(newVal.getId());
            passVal.setRow(newVal.getRow());
            passVal.setCol(newVal.getCol());
        }
        if (passVal.getValue() >= useVal.getValue()) {
            obj1.setValue(passVal.getValue());
            obj1.setTempBoard(passVal.getTempBoard());
            obj1.setId(passVal.getId());
            obj1.setRow(passVal.getRow());
            obj1.setCol(passVal.getCol());
            return obj1;
        }
    }

    obj1.setValue(passVal.getValue());
    obj1.setTempBoard(passVal.getTempBoard());
    obj1.setId(passVal.getId());
    obj1.setRow(passVal.getRow());
    obj1.setCol(passVal.getCol());
    board->setId(obj1.getId());
    board->setRow(obj1.getRow());
    board->setCol(obj1.getCol());
    return obj1;
}
