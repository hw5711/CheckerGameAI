
#include "AlphaBetaSearch.h"
#include "GameTree.h"
#include<iostream>

using namespace std;

int alphabeta(GameTree *node, int depth, char player, int alpha, int beta) {
    if (node->deepenough(depth, player)) //node is a leaf node)
        return node->evaluation(player);
    if (player == 'A') {
        int bestVal = -100, value;
        for (int i = 0; i < 6; i++) {
            if (node->children[i] == NULL)
                continue;
            value = alphabeta(node->children[i], depth + 1, node->player, alpha, beta);
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
            value = alphabeta(node->children[i], depth + 1, node->player, alpha, beta);
            bestVal = (bestVal < value) ? bestVal : value;
            beta = (beta < bestVal) ? beta : bestVal;
            if (beta < alpha)
                break;
        }
        //node->set_heuristic_value(bestVal);
        return bestVal;
    }
}
