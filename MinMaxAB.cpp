
#include "MinMaxAB.h"
#include<iostream>

using namespace std;

Object MinMaxAB(GameTree *board, int depth, char player, Object useVal, Object passVal, int EF) {
    Object obj;
    char NewPlayer;
//    cout<<"test--MINMAXAB: "<< player << endl;
//    board->board_status.displayBoard();
    if (board->deepenough(depth,player)) {
        obj.setValue(board->evaluation(player));//will generate moved location
        obj.setTempBoard(board->board_status);
        // cout<<"\nEvaluation value is : "<<obj<<endl;
        if (player == 'B') {
            obj.setValue(-obj.getValue());
        }
        //cout<<"\ntest minimaxab --- obj location: "<< obj.getRow()<< "  /" << obj.getCol()<<endl;
        board->board_status.displayBoard();
        board->set_heuristic_value(obj.getValue());
        cout<<"\ntest minimaxab -0: value is :" << board->board_status.heuristic_value<<" %% "<<obj.getValue()<<endl;
        return obj;
    }
    Object obj1(0,new Checker());

    for (int i = 0; i < 48; i++) { // need to update
        if (board->children[i] == NULL)
            continue;
        if (player == 'A')
            NewPlayer = 'B';
        else
            NewPlayer = 'A';

        Object passVal1(passVal.getValue(),new Checker());
        Object useVal1(useVal.getValue(), new Checker ());

        int temp = passVal1.getValue();
        passVal1.setValue(-useVal1.getValue());
        useVal1.setValue(-temp);


        Checker tempChecker = passVal1.getTempBoard();
        passVal1.setTempBoard(useVal1.getTempBoard());
        useVal1.setTempBoard(tempChecker);

        obj1 = MinMaxAB(board->children[i], depth + 1, NewPlayer, useVal1, passVal1, EF);

        Object newVal(-obj1.getValue(), new Checker());

        if (newVal.getValue() > passVal1.getValue()) {
            board->set_heuristic_value(i);
            passVal1.setValue(newVal.getValue());
            passVal1.setTempBoard(newVal.getTempBoard());
           // cout<<"\ntest minimaxab-1 --- obj location: "<< endl;
           // passVal1.tempBoard.displayBoard();

        }
        if (passVal1.getValue() >= useVal1.getValue()) {
            obj1.setValue(passVal1.getValue());
            obj1.setTempBoard(passVal1.getTempBoard());
           // cout<<"\ntest minimaxab-2 --- obj location: "<< endl;
            //obj1.tempBoard.displayBoard();
            return obj1;
        }
    }
    obj1.setValue(passVal.getValue());
    obj1.setTempBoard(passVal.getTempBoard());
//    board->set_heuristic_value(obj.getValue(), obj.getRow(), obj.getCol());
    return obj1;
}
