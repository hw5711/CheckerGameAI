
#include "AlphaBetaSearch.h"
#include "GameTree.h"
#include<iostream>

using namespace std;

Object alphabeta(GameTree *node, int depth, char player, Object alpha, Object beta, int EF) {
    //node is a leaf node)
    Object obj;
    if (node->deepenough(depth, player)){
        if(EF == 1){
            obj.setValue(node->evaluation1(player));
            obj.setTempBoard(node->board_status);
            obj.setRow(node->row);
            obj.setCol(node->col);
            obj.setId(node->id);
            node->set_heuristic_value(obj.getValue(), obj.getTempBoard(),node->id, node->row ,node->col);
            return obj;
        }
        if(EF == 2){
            obj.setValue(node->evaluation2(player));
            obj.setTempBoard(node->board_status);
            obj.setRow(node->row);
            obj.setCol(node->col);
            obj.setId(node->id);
            node->set_heuristic_value(obj.getValue(), obj.getTempBoard(),node->id, node->row ,node->col);
            return obj;
        }
    }
    Checker ck;
    Object obj1(0, ck, 0, -1, -1);
    Object bestVal(0, ck, 0, -1, -1);
//    Object bestVal(0, ck, 0, -1, -1);

    if (player == 'A') {
        //int bestVal = -100, value;
        for (int i = 0; i < 48; i++) {
            if (node->children[i] == NULL)
                continue;
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

            if (beta.value <= alpha.value)
                break;
        }
        return bestVal;
    } else {
        for (int i = 0; i < 48; i++) {
            if (node->children[i] == NULL)
                continue;
            if(EF == 1) {
                obj1 = alphabeta(node->children[i], depth + 1, node->player, alpha, beta, 1);
            }
            if(EF == 2) {
                obj1 = alphabeta(node->children[i], depth + 1, node->player, alpha, beta, 2);
            }

            bestVal.setValue((bestVal.value < obj1.value) ? bestVal.value : obj1.value);
            bestVal.setTempBoard((bestVal.value < obj1.value) ? bestVal.tempBoard : obj1.tempBoard);
            bestVal.setId((bestVal.value < obj1.value) ? bestVal.id : obj1.id);
            bestVal.setRow((bestVal.value < obj1.value) ? bestVal.row : obj1.row);
            bestVal.setCol((bestVal.value < obj1.value) ? bestVal.col : obj1.col);

            beta.setValue((beta.value < bestVal.value)? beta.value : bestVal.value);
            beta.setTempBoard((beta.value < bestVal.value)? beta.tempBoard : bestVal.tempBoard);
            beta.setId((beta.value < bestVal.value)? beta.id : bestVal.id);
            beta.setRow((beta.value < bestVal.value)? beta.row : bestVal.row);
            beta.setCol((beta.value < bestVal.value)? beta.col : bestVal.col);

            if (beta.value > alpha.value)
                break;
        }
        return bestVal;
    }
}
