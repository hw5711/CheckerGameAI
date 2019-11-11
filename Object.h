//
// Created by Huan wu on 11/10/19.
//

#ifndef CHECKERGAMEAI_OBJECT_H
#define CHECKERGAMEAI_OBJECT_H


class Object {
public:

    int value;
    Checker tempBoard;

    void setTempBoard(const Checker &tempBoard) {
        Object::tempBoard = tempBoard;
    }

    const Checker &getTempBoard() const {
        return tempBoard;
    }


    Object() {
        this->value = 0;
        this->tempBoard;
    }

    Object(int value, Checker b) {
        this->value = value;
        this->tempBoard = b;
    }

    void setValue(int value) {
        Object::value = value;
    }

    int getValue() const {
        return value;
    }

};

#endif //CHECKERGAMEAI_OBJECT_H
