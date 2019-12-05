
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
            }
            obj.setId(passVal.getId());
            obj.setRow(passVal.getRow());
            obj.setCol( passVal.getCol());
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

            //Object negPass;
            if(depth !=  1) {
                useVal.setValue(-passVal.getValue());
            }
            useVal.setTempBoard(useVal.getTempBoard());

            if (depth == 1) {
                passVal.setId(checkerboard->successor[i]->currentboard.getDiffId(checkerboard->currentboard.board));
                passVal.setRow(checkerboard->successor[i]->currentboard.getDiffRow(checkerboard->currentboard.board));
                passVal.setCol(checkerboard->successor[i]->currentboard.getDiffCol(checkerboard->currentboard.board));
            }
//          else {
//                useVal.setId(useVal.getId());
//                useVal.setRow(useVal.getRow());
//                useVal.setCol(useVal.getCol());
//            }

           // Object negUse;
           if(depth !=  1) {
               passVal.setValue(-useVal.getValue());
           }
            passVal.setTempBoard(passVal.getTempBoard());

//            if(depth == 1){
//                passVal.setId(checkerboard->successor[i]->currentboard.getDiffId(checkerboard->currentboard.board));
//                passVal.setRow(checkerboard->successor[i]->currentboard.getDiffRow(checkerboard->currentboard.board));
//                passVal.setCol(checkerboard->successor[i]->currentboard.getDiffCol(checkerboard->currentboard.board));
//            }
//            else {
//                passVal.setId(passVal.getId());
//                passVal.setRow(passVal.getRow());
//                passVal.setCol(passVal.getCol());
//            }

            obj1 = MinMaxAB(checkerboard->successor[i], depth + 1, player1, useVal, passVal, EF);
            Object newVal(-obj1.getValue(), obj1.getTempBoard(), obj1.getId(), obj1.getRow(), obj1.getCol());

            if (newVal.getValue() > passVal.getValue()) {
                passVal.setValue(newVal.getValue());
                passVal.setTempBoard(newVal.getTempBoard());
                passVal.setId(newVal.getId());
                passVal.setRow(newVal.getRow());
                passVal.setCol(newVal.getCol());

                if (passVal.getValue() >= useVal.getValue()) {
//                    cout << "2 UPDATE pass and return {{pass val >= use val}} : " << passVal.getValue() << ": "
//                         << useVal.getValue() << ": " <<
//                         passVal.getRow() << "*" << passVal.getCol() << "*$" << useVal.getRow() << "*"
//                         << useVal.getCol() << endl;
                    obj1.setValue(passVal.getValue());
                    obj1.setTempBoard(passVal.getTempBoard());
                    obj1.setId(passVal.getId());
                    obj1.setRow(passVal.getRow());
                    obj1.setCol(passVal.getCol());
                    return obj1;
                }
            }
        }

        obj1.setValue(passVal.getValue());
        obj1.setTempBoard(passVal.getTempBoard());
        obj1.setId(passVal.getId());
        obj1.setRow(passVal.getRow());
        obj1.setCol(passVal.getCol());
        return obj1;

}
