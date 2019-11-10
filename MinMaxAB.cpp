
#include "MinMaxAB.h"
#include<iostream>

using namespace std;


int MinMaxAB(GameTree *board, int depth, char player, int UseT, int PassT, int EF) {
    int obj;
    int newVal;
    char NewPlayer;
   // cout<<"test--MINMAXAB: "<< player << endl;
    if (board->deepenough(depth,player)) {
        obj = board->evaluation(player);//will generate moved location
       // cout<<"\nEvaluation value is : "<<obj<<endl;
        if (player == 'B') {
            obj = -obj;
        }
        board->set_heuristic_value(obj);
        cout<<"\ntest minimaxab --- obj: "<< obj<< endl;
        return obj;
    }
    int obj1 = 0;
   // obj1.heuristic_value = 0;

    for (int i = 0; i < 48; i++) { // need to update
        if (board->children[i] == NULL)
            continue;
        if (player == 'A')
            NewPlayer = 'B';
        else
            NewPlayer = 'A';

        obj1 = MinMaxAB(board->children[i], depth + 1, NewPlayer, -PassT, -UseT, EF);

        newVal = -obj1;

        if (newVal > PassT) {
            board->set_heuristic_value(obj);
            PassT = newVal;
        }
        if (PassT >= UseT) {
            obj1 = PassT;
            return obj1;
        }
    }
    obj1 = PassT;
    //board->set_heuristic_value(obj.heuristic_value, obj.row, obj.col);
    return obj1;
}
