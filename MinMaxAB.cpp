
#include "MinMaxAB.h"
#include<iostream>

using namespace std;

Object MinMaxAB(GameTree *board, int depth, char player, Object useVal, Object passVal, int EF) {
    cout<<"\nuse value :" << useVal.getValue() << " %pass value: "<< passVal.getValue()<<endl;
    Object obj;
    char NewPlayer;
    if (board->deepenough(depth,player)) {
        obj.setValue(board->evaluation(player));
        obj.setTempBoard(board->board_status);
        if (player == 'B') {
            obj.setValue(-obj.getValue());
        }
        board->set_heuristic_value(obj.getValue(), obj.getTempBoard());
        Checker k = obj.getTempBoard();
        cout<<"\ntest minimaxab -0: value is :" << player << "% "<<board->board_status.heuristic_value<<" %% "<<obj.getValue()<<endl;
        k.displayBoard();
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

        obj1 = MinMaxAB(board->children[i], depth + 1, NewPlayer, passVal.operator-(passVal),useVal.operator-(useVal), EF);

        Object newVal(-obj1.getValue(), obj1.getTempBoard());

        if (newVal.getValue() > passVal.getValue()) {
            board->set_heuristic_value(board->children[i]->board_status.heuristic_value,board->children[i]->heuristic_board);
            passVal.setValue(newVal.getValue());
            passVal.setTempBoard(newVal.getTempBoard());
        }
        if (passVal.getValue() >= useVal.getValue()) {
            obj1.setValue(passVal.getValue());
            obj1.setTempBoard(passVal.getTempBoard());
            return obj1;
        }
    }
    obj1.setValue(passVal.getValue());
    obj1.setTempBoard(passVal.getTempBoard());
    cout<<"\nChildren use value :" << useVal.getValue() << " %pass value: "<< passVal.getValue()<<endl;
    return obj1;
}
