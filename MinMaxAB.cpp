
#include "MinMaxAB.h"
#include<iostream>

using namespace std;

//use value is min, pass value is max
Object MinMaxAB(GameTree *board, int depth, char player, Object useVal, Object passVal, int EF) {
    //cout<<"\nSHOULD INVERT :use value :" << useVal.value << " %pass value: "<< passVal.value<<endl;

    /***************************************************************/
    /*** object should carry the first layer child location ***/
    /***************************************************************/

    cout<<"\nplayer: "<< player << endl;
    Object obj;
    char NewPlayer;
    if (board->deepenough(depth,player)) { // if search to the bottom child
        obj.setValue(board->evaluation(player));
        obj.setTempBoard(board->board_status);
        if (player == 'B') {
            obj.setValue(-obj.getValue());
            //cout<<"\ntest this player should be B , and value is :" << obj.value<<endl;
        }
        board->set_heuristic_value(obj.getValue(), obj.getTempBoard());
        cout<<"\ntest this is the curent player " <<player<<" next step(child) borard , and value is : "<<obj.value<<endl ;
        return obj;
    }
    Object obj1(0,new Checker());

    for (int i = 0; i < 48; i++) { // need to update
        if (board->children[i] == NULL) {
            continue;
        }
        cout<<"\ndiplay child board of :"<< player<<"-" <<i<<":\n";
        board->children[i]->board_status.displayBoard();

        cout<<endl;
        if (player == 'A')
            NewPlayer = 'B';
        else
            NewPlayer = 'A';

        //Checker childBoard = board->children[i]->board_status;
       // cout<<"useValue: "<<useVal.value<<" passValue is: "<<passVal.value<<endl;
        obj1 = MinMaxAB(board->children[i], depth + 1, NewPlayer, passVal.operator-(passVal),useVal.operator-(useVal), EF);
        Object newVal(-obj1.getValue(), obj1.getTempBoard());
        //choose proper value
        if (newVal.getValue() > passVal.getValue()) {
            board->set_heuristic_value(newVal.getValue(),newVal.getTempBoard());
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
//    cout<<"\nChildren use value :" << useVal.getValue() << " %pass value: "<< passVal.getValue()<<endl;
    return obj1;
}
