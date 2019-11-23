
#include "AlphaBeta.h"
#include "CheckerTree.h"
#include<iostream>

using namespace std;

Object alphabeta(CheckerTree *node, int depth, char player, Object a, Object b, int EF) {
    Object obj;
    if (node->deepenough(depth, player)){
        if(EF == 1){
            obj.setValue(node->evaluation1(player));
            obj.setTempBoard(node->currentboard);
            node->setHeuristicValue(obj.getValue(), obj.getTempBoard(),node->id, node->row ,node->col);
            obj.setRow(node->row);
            obj.setCol(node->col);
            obj.setId(node->id);
            return obj;
        }
        if(EF == 2){
            obj.setValue(node->evaluation2(player));//changed
            obj.setTempBoard(node->currentboard);
            node->setHeuristicValue(obj.getValue(), obj.getTempBoard(),node->id, node->row ,node->col);
            obj.setRow(node->row);
            obj.setCol(node->col);
            obj.setId(node->id);
            return obj;
        }

        if(EF == 3){
            obj.setValue(node->evaluation3(player));//changed
            obj.setTempBoard(node->currentboard);
            node->setHeuristicValue(obj.getValue(), obj.getTempBoard(),node->id, node->row ,node->col);
            obj.setRow(node->row);
            obj.setCol(node->col);
            obj.setId(node->id);
            return obj;
        }
    }
    Checker ck;

    if (player == 'A') {
        Object maxvalue(-1, ck, 0, -1, -1);
        Object obj1(0, ck, 0, -1, -1);
        for (int i = 0; i < 48; i++) {
            if (node->successor[i] == NULL) {
                continue;
            }
            if(EF == 1) {
                obj1 = alphabeta(node->successor[i], depth + 1, node->player, a, b, 1);
            }
            if(EF == 2) {
                obj1 = alphabeta(node->successor[i], depth + 1, node->player, a, b, 2);
            }

            maxvalue.setValue((maxvalue.value > obj1.value) ? maxvalue.value : obj1.value);
            maxvalue.setTempBoard((maxvalue.value > obj1.value) ? maxvalue.tempBoard : obj1.tempBoard);
            maxvalue.setId((maxvalue.value > obj1.value) ? maxvalue.id : obj1.id);
            maxvalue.setRow((maxvalue.value > obj1.value) ? maxvalue.row : obj1.row);
            maxvalue.setCol((maxvalue.value > obj1.value) ? maxvalue.col : obj1.col);

            a.setValue((a.value > maxvalue.value) ? a.value : maxvalue.value);
            a.setTempBoard((a.value > maxvalue.value) ? a.tempBoard : maxvalue.tempBoard);
            a.setId((a.value > maxvalue.value) ? a.id : maxvalue.id);
            a.setRow((a.value > maxvalue.value) ? a.row: maxvalue.row);
            a.setCol((a.value > maxvalue.value) ? a.col : maxvalue.col);
            if (b.value <= a.value)
                break;
        }
        node->setHeuristicValue(maxvalue.value, maxvalue.tempBoard, maxvalue.id, maxvalue.row ,maxvalue.col);
        return maxvalue;
    } else {
        Object maxvalue(1, ck, 0, -1, -1);
        Object obj1(0, ck, 0, -1, -1);
        for (int i = 0; i < 48; i++) {
            if (node->successor[i] == NULL) {
                continue;
            }
            if(EF == 1) {
                obj1 = alphabeta(node->successor[i], depth + 1,  node->player, a, b, 1);
            }
            if(EF == 2) {
                obj1 = alphabeta(node->successor[i], depth + 1, node->player, a, b, 2);
            }
            maxvalue.setValue((maxvalue.value > obj1.value) ? maxvalue.value : obj1.value);
            maxvalue.setTempBoard((maxvalue.value > obj1.value) ? maxvalue.tempBoard : obj1.tempBoard);
            maxvalue.setId((maxvalue.value > obj1.value) ? maxvalue.id : obj1.id);
            maxvalue.setRow((maxvalue.value > obj1.value) ? maxvalue.row : obj1.row);
            maxvalue.setCol((maxvalue.value > obj1.value) ? maxvalue.col : obj1.col);

            b.setValue((b.value > maxvalue.value)? b.value : maxvalue.value);
            b.setTempBoard((b.value > maxvalue.value)? b.tempBoard : maxvalue.tempBoard);
            b.setId((b.value > maxvalue.value)? b.id : maxvalue.id);
            b.setRow((b.value > maxvalue.value)? b.row : maxvalue.row);
            b.setCol((b.value > maxvalue.value)? b.col : maxvalue.col);

            if (b.value > a.value)
                break;
        }
        node->setHeuristicValue(maxvalue.value, maxvalue.tempBoard, maxvalue.id, maxvalue.row ,maxvalue.col);
        return maxvalue;
    }
}
