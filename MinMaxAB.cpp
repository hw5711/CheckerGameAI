
#include "MinMaxAB.h"
#include<iostream>

using namespace std;

//use value is min, pass value is max
Object MinMaxAB(GameTree *board, int depth, char player, Object useVal, Object passVal, int EF) {
   // cout<<"\nSHOULD INVERT :use value :" << useVal.value << " %pass value: "<< passVal.value<<endl;
    /***************************************************************/
    /*** object should carry the first layer child location ***/
    /***************************************************************/
    Object obj;
    char NewPlayer;
    if (board->deepenough(depth,player)) { // if search to the bottom child
        obj.setValue(board->evaluation(player));
        obj.setTempBoard(board->board_status);
        if (player == 'B') {
            obj.setValue(-obj.getValue());
            //cout<<"\ntest this player should be B , and value is :" << obj.value<<endl;
        }
       // cout<<"\nreach the bottom of deepest node \n";
//        cout<<"\n1MinMaxAB- id, row, col :"<< board->id <<"%"<< board->row <<"%"<< board->col<<endl;
        board->set_heuristic_value(obj.getValue(), obj.getTempBoard(),board->id, board->row ,board->col );
        obj.setId(board->id);
        obj.setRow(board->row);
        obj.setCol(board->col);
        //cout<<"\ntest this is the current player " <<player<<" next step(child) borard , and value is : "<<obj.value<<endl ;
        return obj;
    }
    Checker ck;
    Object obj1(0, ck, 0, -1, -1);

    for (int i = 0; i < 48; i++) { // need to update
        if (board->children[i] == NULL) {
            continue;
        }
        cout<<endl;
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
        //cout<<"\n3MinMaxAB- id, row, col :"<< obj1.getId() <<"%"<< obj1.getRow() <<"%"<<obj1.getCol()<<endl;
        Object newVal(-obj1.getValue(), obj1.getTempBoard(), obj1.getId(), obj1.getRow(), obj1.getCol());

        if (newVal.getValue() > passVal.getValue()) {
//            cout<<"\nnew pass > pass vale\n";
//            cout<<"\n2MinMaxAB- id, row, col :"<< newVal.getId() <<"%"<< newVal.getRow() <<"%"<<newVal.getCol()<<endl;
            board->children[i]->set_heuristic_value(newVal.getValue(),newVal.getTempBoard(),newVal.getId(), newVal.getRow() ,newVal.getCol() );
            passVal.setValue(newVal.getValue());
            passVal.setTempBoard(newVal.getTempBoard());
            passVal.setId(newVal.getId());
            passVal.setRow(newVal.getRow());
            passVal.setCol(newVal.getCol());
        }
        if (passVal.getValue() >= useVal.getValue()) {
//            cout<<"\nmeet pass >= use vale\n";
            obj1.setValue(passVal.getValue());
            obj1.setTempBoard(passVal.getTempBoard());
            obj1.setId(passVal.getId());
            obj1.setRow(passVal.getRow());
            obj1.setCol(passVal.getCol());
//            cout<<"\n5MinMaxAB- before return :id, row, col :"<< obj1.getId()
//            <<"%"<< obj1.getRow() <<"%"<<obj1.getCol()<<endl;
            return obj1;
        }
    }

    obj1.setValue(passVal.getValue());
    obj1.setTempBoard(passVal.getTempBoard());
    obj1.setId(passVal.getId());
    obj1.setRow(passVal.getRow());
    obj1.setCol(passVal.getCol());
//    cout<<"\n6MinMaxAB- before return :id, row, col :"<< obj1.getId()
//        <<"%"<< obj1.getRow() <<"%"<<obj1.getCol()<<endl;
    board->setId(obj1.getId());
    board->setRow(obj1.getRow());
    board->setCol(obj1.getCol());
//    cout<<"\n7MinMaxAB- before return :id, row, col :"<< board->getId()
//        <<"%"<< board->getRow() <<"%"<<board->getCol()<<endl;
    return obj1;
}
