//
// Created by Huan wu on 11/10/19.
//

#ifndef CHECKERGAMEAI_OBJECT_H
#define CHECKERGAMEAI_OBJECT_H


class Object {
public:

    int value;
    int row;
    int col;


    Object() {
        this->value = 0;
        this->row = 0;
        this->col = 0;
    }

    Object(int value, int row, int col) {
        this->value = value;
        this->row = row;
        this->col = col;
    }

    void setValue(int value) {
        Object::value = value;
    }

    void setRow(int row) {
        Object::row = row;
    }

    void setCol(int col) {
        Object::col = col;
    }

    int getValue() const {
        return value;
    }

    int getRow() const {
        return row;
    }

    int getCol() const {
        return col;
    }
};

#endif //CHECKERGAMEAI_OBJECT_H
