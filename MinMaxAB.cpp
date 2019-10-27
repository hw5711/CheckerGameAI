
#include "MinMaxAB.h"
#include<iostream>

using namespace std;

int MinMaxAB(GameTree *board,int depth, char player, int UseT, int PassT)
{
    int obj;
    int newVal;
    char NewPlayer;

    if(board->deepenough(depth))
    {
        //board->player = player;
        obj = board->evaluation();
        if(player == 'B')
            obj = -obj;
        board->set_heuristic_value(obj);
        return obj;
    }
    int obj1=0;
    for(int i = 0 ; i < 6; i++)
    {
        if(board->children[i] == NULL)
            continue;
        if(player == 'A')
            NewPlayer = 'B';
        else
            NewPlayer = 'A';

        obj1 = MinMaxAB(board->children[i],depth+1,NewPlayer,-PassT,-UseT);
        newVal = -obj1;

        if(newVal > PassT)
        {
            board->set_heuristic_value(i);
            PassT = newVal;
        }
        if(PassT >= UseT)
        {
            obj1=PassT;
            //board->set_heuristic_value(obj1);
            return obj1;
        }
    }
    obj1=PassT;
    //board->set_heuristic_value(obj1);
    return obj1;
}
