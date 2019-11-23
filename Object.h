//
// Created by Huan wu on 11/10/19.
//

#ifndef CHECKERGAMEAI_OBJECT_H
#define CHECKERGAMEAI_OBJECT_H


class Object {
public:

    int value;
    Checker tempBoard;
    int row;
    int col;
    int id;

    Object() {

    }

    void setTempBoard(const Checker &tempBoard) {
        Object::tempBoard = tempBoard;
    }

    const Checker &getTempBoard() const {
        return tempBoard;
    }

    Object(int value, Checker b, int id, int r, int c) {
        this->value = value;
        this->tempBoard = b;
        this->id = id;
        this->row = r;
        this->col = c;
    }

    void setValue(int value) {
        Object::value = value;
    }

    int getValue() const {
        return value;
    }

    Object operator-(Object obj) {
        Object newObj;
        newObj.setValue(-obj.value);
        newObj.setTempBoard(obj.getTempBoard());
        newObj.setId(obj.id);
        newObj.setRow(obj.row);
        newObj.setCol(obj.col);
        return newObj;
    }

    int getRow() const {
        return row;
    }

    void setRow(int row) {
        Object::row = row;
    }

    int getCol() const {
        return col;
    }

    void setCol(int col) {
        Object::col = col;
    }


    int getId() const {
        return id;
    }

    void setId(int id) {
        Object::id = id;
    }
};

#endif //CHECKERGAMEAI_OBJECT_H
