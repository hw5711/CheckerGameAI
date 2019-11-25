
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
            checkerboard->setHeuristicValue(obj.getValue(), obj.getTempBoard(), passVal.getId(), passVal.getRow(),
                                            passVal.getCol());
            cout << "!!! is : " << obj.getValue()<<"_"<< passVal.getId()<<"-"  << passVal.getRow()<<"_"<<  passVal.getCol()<< endl;
            obj.setId(passVal.getId());
            obj.setRow(passVal.getRow());
            obj.setCol(  passVal.getCol());
            return obj;
        }
        Checker ck;
        Object obj1(0, ck, 0, -1, -1);

        cout << "DEPTH : "<< depth<< endl;
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

//            if (depth == 1) {
//                useVal.setId(checkerboard->successor[i]->currentboard.getDiffId(checkerboard->currentboard.board));
//                useVal.setRow(checkerboard->successor[i]->currentboard.getDiffRow(checkerboard->currentboard.board));
//                useVal.setCol(checkerboard->successor[i]->currentboard.getDiffCol(checkerboard->currentboard.board));
//            }
//          else {
//                useVal.setId(passVal.getId());
//                useVal.setRow(passVal.getRow());
//                useVal.setCol(passVal.getCol());
//            }

           // Object negUse;
           if(depth !=  1) {
               passVal.setValue(-useVal.getValue());
           }
            passVal.setTempBoard(passVal.getTempBoard());
            if(depth == 1){
                passVal.setId(checkerboard->successor[i]->currentboard.getDiffId(checkerboard->currentboard.board));
                passVal.setRow(checkerboard->successor[i]->currentboard.getDiffRow(checkerboard->currentboard.board));
                passVal.setCol(checkerboard->successor[i]->currentboard.getDiffCol(checkerboard->currentboard.board));
            }
            else {
                passVal.setId(passVal.getId());
                passVal.setRow(passVal.getRow());
                passVal.setCol(passVal.getCol());
            }

            checkerboard->successor[i]->setHeuristicValue(passVal.value, checkerboard->successor[i]->currentboard,
                                                          passVal.getId(), passVal.getRow(),
                                                          passVal.getCol());
            cout<<"Go next depth: "<<  passVal.getValue()<<endl;
            obj1 = MinMaxAB(checkerboard->successor[i], depth + 1, player1, useVal, passVal, EF);
            cout<<"555555 obj value is "<< obj1.getValue()<<" in depth "<<depth<<endl;
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
        return obj1;

}
