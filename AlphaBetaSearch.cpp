
#include "AlphaBetaSearch.h"
#include "GameTree.h"
#include<iostream>

using namespace std;

int alphabeta(GameTree *node, int depth, char player, int alpha, int beta, int EF) {
    //node is a leaf node)
    if (node->deepenough(depth, player)){
        if(EF == 1){
            return node->evaluation1(player);
        }
        if(EF == 2){
            return node->evaluation2(player);
        }
    }

    if (player == 'A') {
        int bestVal = -100, value;
        for (int i = 0; i < 6; i++) {
            if (node->children[i] == NULL)
                continue;
            if(EF == 1) {
                value = alphabeta(node->children[i], depth + 1, node->player, alpha, beta, 1);
            }
            if(EF == 2) {
                value = alphabeta(node->children[i], depth + 1, node->player, alpha, beta, 2);
            }
            bestVal = (bestVal > value) ? bestVal : value;
            alpha = (alpha > bestVal) ? alpha : bestVal;
            if (beta <= alpha)
                break;
        }
        //node->set_heuristic_value(bestVal);
        return bestVal;
    } else {
        int bestVal = +100, value;
        for (int i = 0; i < 6; i++) {
            if (node->children[i] == NULL)
                continue;
            if(EF == 1) {
                value = alphabeta(node->children[i], depth + 1, node->player, alpha, beta, 1);
            }
            if(EF == 2) {
                value = alphabeta(node->children[i], depth + 1, node->player, alpha, beta, 2);
            }
            bestVal = (bestVal < value) ? bestVal : value;
            beta = (beta < bestVal) ? beta : bestVal;
            if (beta < alpha)
                break;
        }
        //node->set_heuristic_value(bestVal);
        return bestVal;
    }
}
