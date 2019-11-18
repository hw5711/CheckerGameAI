
#include "AlphaBetaSearch.h"
#include "GameTree.h"
#include<iostream>

using namespace std;

Object alphabeta(GameTree *node, int depth, char player, Object alpha, Object beta, int EF) {
    Object obj;
    if (node->deepenough(depth, player)){
        if(EF == 1){
            obj.setValue(node->evaluation1(player));
            obj.setTempBoard(node->board_status);
            node->set_heuristic_value(obj.getValue(), obj.getTempBoard(),node->id, node->row ,node->col);
            obj.setRow(node->row);
            obj.setCol(node->col);
            obj.setId(node->id);
            //cout<<"\n bottom child return the next step: "<<obj.id << ": "<< obj.row<<" - "<<obj.col<<" - "<<obj.value<<endl;
            return obj;
        }
        if(EF == 2){
            obj.setValue(node->evaluation2(player));//changed
            obj.setTempBoard(node->board_status);
            node->set_heuristic_value(obj.getValue(), obj.getTempBoard(),node->id, node->row ,node->col);
            obj.setRow(node->row);
            obj.setCol(node->col);
            obj.setId(node->id);
            //cout<<"\n bottom child return the next step: "<<obj.id << ": "<< obj.row<<" - "<<obj.col<<" - "<<obj.value<<endl;
            return obj;
        }
    }
    Checker ck;

    if (player == 'A') {
        Object bestVal(-1, ck, 0, -1, -1);
        Object obj1(0, ck, 0, -1, -1);
        for (int i = 0; i < 48; i++) {
            if (node->children[i] == NULL) {
                continue;
            }
            //cout<<"\nA inside player: "<< player << "   board player : "<< node->player<<endl;
            if(EF == 1) {
                obj1 = alphabeta(node->children[i], depth + 1, node->player, alpha, beta, 1);
            }
            if(EF == 2) {
                obj1 = alphabeta(node->children[i], depth + 1, node->player, alpha, beta, 2);
            }

            bestVal.setValue((bestVal.value > obj1.value) ? bestVal.value : obj1.value);
            bestVal.setTempBoard((bestVal.value > obj1.value) ? bestVal.tempBoard : obj1.tempBoard);
            bestVal.setId((bestVal.value > obj1.value) ? bestVal.id : obj1.id);
            bestVal.setRow((bestVal.value > obj1.value) ? bestVal.row : obj1.row);
            bestVal.setCol((bestVal.value > obj1.value) ? bestVal.col : obj1.col);

            alpha.setValue((alpha.value > bestVal.value) ? alpha.value : bestVal.value);
            alpha.setTempBoard((alpha.value > bestVal.value) ? alpha.tempBoard : bestVal.tempBoard);
            alpha.setId((alpha.value > bestVal.value) ? alpha.id : bestVal.id);
            alpha.setRow((alpha.value > bestVal.value) ? alpha.row: bestVal.row);
            alpha.setCol((alpha.value > bestVal.value) ? alpha.col : bestVal.col);
//            cout<<"\nin A, alpha value is :"<< alpha.value<<endl;
            if (beta.value <= alpha.value)
                break;
        }
        node->set_heuristic_value(bestVal.value, bestVal.tempBoard, bestVal.id, bestVal.row ,bestVal.col);
//        cout<<"player A return bestVal : "<< bestVal.value<<" --- id,row,col :" <<bestVal.id <<","<<bestVal.row<<","<<bestVal.col<<endl;
        return bestVal;
    } else {
        Object bestVal(1, ck, 0, -1, -1);
        Object obj1(0, ck, 0, -1, -1);
        for (int i = 0; i < 48; i++) {
            if (node->children[i] == NULL) {
                continue;
            }
            //cout<<"\nB inside player: "<< player << "   board player : "<< node->player<<endl;
            if(EF == 1) {
                obj1 = alphabeta(node->children[i], depth + 1,  node->player, alpha, beta, 1);
            }
            if(EF == 2) {
                obj1 = alphabeta(node->children[i], depth + 1, node->player, alpha, beta, 2);
            }
//I changed the operator from < to >
            bestVal.setValue((bestVal.value > obj1.value) ? bestVal.value : obj1.value);
            bestVal.setTempBoard((bestVal.value > obj1.value) ? bestVal.tempBoard : obj1.tempBoard);
            bestVal.setId((bestVal.value > obj1.value) ? bestVal.id : obj1.id);
            bestVal.setRow((bestVal.value > obj1.value) ? bestVal.row : obj1.row);
            bestVal.setCol((bestVal.value > obj1.value) ? bestVal.col : obj1.col);

            beta.setValue((beta.value > bestVal.value)? beta.value : bestVal.value);
            beta.setTempBoard((beta.value > bestVal.value)? beta.tempBoard : bestVal.tempBoard);
            beta.setId((beta.value > bestVal.value)? beta.id : bestVal.id);
            beta.setRow((beta.value > bestVal.value)? beta.row : bestVal.row);
            beta.setCol((beta.value > bestVal.value)? beta.col : bestVal.col);

            if (beta.value > alpha.value)
                break;
        }
        node->set_heuristic_value(bestVal.value, bestVal.tempBoard, bestVal.id, bestVal.row ,bestVal.col);
        //cout<<"player B return bestVal : "<< bestVal.value<<" --- id,row,col :" <<bestVal.id <<","<<bestVal.row<<","<<bestVal.col<<endl;
        return bestVal;
    }
}
