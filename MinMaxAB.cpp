
#include "MinMaxAB.h"
#include<iostream>

using namespace std;

Object MinMaxAB(CheckerTree *checkerboard, int depth, char player, Object useVal, Object passVal, int EF) {
    Object obj;
    char player1;
    if (checkerboard->deepenough(depth, player)) { // if search to the bottom child
        if (EF == 1) {
            obj.setValue(checkerboard->evaluation1(player));
        }
        if (EF == 2) {
            obj.setValue(checkerboard->evaluation2(player));
        }
        if (EF == 3) {
            obj.setValue(checkerboard->evaluation3(player));
        }
        obj.setTempBoard(checkerboard->currentboard);
        if (player == 'B') {
            obj.setValue(-obj.getValue());
            //cout<<"\nMIN- B - value is : "<< obj.getValue()<<endl;
        }
        checkerboard->setHeuristicValue(obj.getValue(), obj.getTempBoard(), checkerboard->id, checkerboard->row,
                                        checkerboard->col);
        obj.setId(checkerboard->id);
        obj.setRow(checkerboard->row);
        obj.setCol(checkerboard->col);
        return obj;
    }
    Checker ck;
    Object obj1(0, ck, 0, -1, -1);

    for (int i = 0; i < 48; i++) { // need to update
        if (checkerboard->successor[i] == NULL) {
            continue;
        }
        if (player == 'A')
            player1 = 'B';
        else
            player1 = 'A';

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

        obj1 = MinMaxAB(checkerboard->successor[i], depth + 1, player1, negPass, negUse, EF);
        Object newVal(-obj1.getValue(), obj1.getTempBoard(), obj1.getId(), obj1.getRow(), obj1.getCol());

        if (newVal.getValue() > passVal.getValue()) {
            checkerboard->successor[i]->setHeuristicValue(newVal.getValue(), newVal.getTempBoard(), newVal.getId(),
                                                          newVal.getRow(), newVal.getCol());
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
    checkerboard->setId(obj1.getId());
    checkerboard->setRow(obj1.getRow());
    checkerboard->setCol(obj1.getCol());
    return obj1;
}
