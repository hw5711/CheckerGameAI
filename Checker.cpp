
#include "Checker.h"
#include <iostream>
#include <iomanip>
#include<ctime>
#include<cstdlib>


using namespace std;

Checker::Checker() {
    int id_num = 1;
    int id_num_otherplayer = 1;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            //set player A side board
            if (i == 0 && j % 2 == 0) { //A side 1st row
                setBoard('A', i, j, 'm', id_num, -1000, true);
                id_num++;
                continue;
            }

            if (i == 0 && j % 2 != 0) {
                setBoard(' ', i, j, 'n', 0, -1000, true);
                continue;
            }

            if (i == 1 && j % 2 != 0) { //A side 2nd row
                setBoard('A', i, j, 'm', id_num, -1000, true);
                id_num++;
                continue;
            }

            if (i == 1 && j % 2 == 0) {
                setBoard(' ', i, j, 'n', 0, -1000, true);
                continue;
            }

            if (i == 2 && j % 2 == 0) { //A side 3rd row
                setBoard('A', i, j, 'm', id_num, -1000, true);
                id_num++;
                continue;
            }
            if (i == 2 && j % 2 != 0) {
                setBoard(' ', i, j, 'n', 0, -1000, true);
                continue;
            }

            //set middle 2 lines board
            if (i == 3 || i == 4) {
                setBoard(' ', i, j, 'n', 0, -1000, true);
                continue;
            }
            //set player B side board
            if (i == 5 && j % 2 != 0) { //A side 1st row
                setBoard('B', i, j, 'm', id_num_otherplayer, -1000, true);
                id_num_otherplayer++;
                continue;
            }

            if (i == 5 && j % 2 == 0) {
                setBoard(' ', i, j, 'n', 0, -1000, true); // N means not possessed by both playler
                continue;
            }

            if (i == 6 && j % 2 == 0) { //A side 2nd row
                setBoard('B', i, j, 'm', id_num_otherplayer, -1000, true);
                id_num_otherplayer++;
                continue;
            }

            if (i == 6 && j % 2 != 0) {
                setBoard(' ', i, j, 'n', 0, -1000, true);
                continue;
            }

            if (i == 7 && j % 2 != 0) { //A side 3rd row
                setBoard('B', i, j, 'm', id_num_otherplayer, -1000, true);
                id_num_otherplayer++;
                continue;
            }

            if (i == 7 && j % 2 == 0) {
                setBoard(' ', i, j, 'n', 0, -1000, true);
                continue;
            }
        }
    }
    set_heuristic_value_board(-1000);
}


void Checker::setBoard(char p, int r, int c, char ro, int i, int he, bool t) {
    board[r][c].player = p;
    board[r][c].row = r;
    board[r][c].col = c;
    board[r][c].role = ro;
    board[r][c].id = i;
    board[r][c].heuristic_value = he;
    board[r][c].moveable = t;

}

char Checker::getPlayer(int r, int c) {
    return board[r][c].player;
}

char Checker::getRole(int r, int c) {
    return board[r][c].role;
}

int Checker::getId(int r, int c) {
    return board[r][c].id;
}

//This function allows to display the checker board
void Checker::displayCheckerBoard() {
    cout << "***** DISPLAY BOARD *****\n";
    cout << "\nCol      0  1  2  3  4  5  6  7\n";
    for (int i = 0; i < 8; i++) {
        cout << "row " << i << "   ";
        for (int j = 0; j < 8; j++) {
            if (getPlayer(i, j) != ' ') {
                cout << "|" << getPlayer(i, j) << getId(i, j) << getRole(i, j) << "| ";
            } else {
                cout << " - ";
            }
        }
        cout << endl;
    }
}


int Checker::get_heuristic_value_board() {
    return heuristic_value;
}

void Checker::set_heuristic_value_board(int v) {
    heuristic_value = v;
}

//This function will allows to move player A
char Checker::chanceOfA(char player, int id, int r, int c) {

    int before_r = -1;
    int before_c = -1;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j].player == player && board[i][j].id == id) {
                before_r = i;
                before_c = j;
            }
        }
    }

    int row_diff = abs(r - before_r);
    int col_diff = abs(c - before_c);
    if (row_diff == 1 && col_diff == 1) {
        char role = board[before_r][before_c].role;
        setBoard(player, r, c, role, id, -1000, true);
        setBoard(' ', before_r, before_c, 'n', 0, -1000, true);
        before_r = r;
        before_c = c;
    } else {
        char role = board[before_r][before_c].role;
        setBoard(' ', r, c, 'n', 0, -1000, true);
        if (r > before_r && c > before_c) {
            int en_id = board[before_r + 1][before_c + 1].id;
            setBoard(player, r, c, role, id, -1000, true);
            setBoard(' ', before_r + 1, before_c + 1, 'n', en_id, -1000, true);
            setBoard(' ', before_r, before_c, 'n', 0, -1000, true);
        } else if (r > before_r && c < before_c) {
            int en_id = board[before_r + 1][before_c - 1].id;
            setBoard(player, r, c, role, id, -1000, true);
            setBoard(' ', before_r + 1, before_c - 1, en_id, 'n', -1000, true);
            setBoard(' ', before_r, before_c, 'n', 0, -1000, true);
        } else if (r < before_r && c > before_c) {
            int en_id = board[before_r - 1][before_c + 1].id;
            setBoard(player, r, c, role, id, -1000, true);
            setBoard(' ', before_r - 1, before_c + 1, 'n', en_id, -1000, true);
            setBoard(' ', before_r, before_c, 'n', 0, -1000, true);
        } else if (r < before_r && c < before_c) {
            int en_id = board[before_r - 1][before_c - 1].id;
            setBoard(player, r, c, role, id, -1000, true);
            setBoard(' ', before_r - 1, before_c - 1, 'n', en_id, -1000, true);
            setBoard(' ', before_r, before_c, 'n', 0, -1000, true);
        } else {}

    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (i == 0 && getPlayer(i, j) == 'B') {
                int id = board[i][j].id;
                setBoard('B', i, j, 'k', id, -1000, true);
            }
            if (i == 7 && getPlayer(i, j) == 'A') {
                int id = board[i][j].id;
                setBoard('A', i, j, 'k', id, -1000, true);
            }
        }
    }
    return 'B';
}

//This function allows to move player B
char Checker::chanceOfB(char player, int id, int r, int c) {
    int before_r = -1;
    int before_c = -1;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j].player == player && board[i][j].id == id) {
                before_r = i;
                before_c = j;
            }
        }
    }

    int row_diff = abs(r - before_r);
    int col_diff = abs(c - before_c);
    if (row_diff == 1 && col_diff == 1) {
        char role = board[before_r][before_c].role;
        setBoard(player, r, c, role, id, -1000, true); // set the moving place
        setBoard(' ', before_r, before_c, 'n', 0, -1000, true); //set current place as empty
        before_r = r; //change the current head row
        before_c = c; //change the current head col
    } else {
        char role = board[before_r][before_c].role;
        setBoard(' ', r, c, 'n', 0, -1000, true);
        if (r > before_r && c > before_c) {
            int en_id = board[before_r + 1][before_c + 1].id;
            setBoard(player, r, c, role, id, -1000, true);
            setBoard(' ', before_r + 1, before_c + 1, 'n', en_id, -1000, true);
            setBoard(' ', before_r, before_c, 'n', 0, -1000, true);
        } else if (r > before_r && c < before_c) {
            int en_id = board[before_r + 1][before_c - 1].id;
            setBoard(player, r, c, role, id, -1000, true);
            setBoard(' ', before_r + 1, before_c - 1, en_id, 'n', -1000, true);
            setBoard(' ', before_r, before_c, 'n', 0, -1000, true);
        } else if (r < before_r && c > before_c) {
            int en_id = board[before_r - 1][before_c + 1].id;
            setBoard(player, r, c, role, id, -1000, true);
            setBoard(' ', before_r - 1, before_c + 1, 'n', en_id, -1000, true);
            setBoard(' ', before_r, before_c, 'n', 0, -1000, true);
        } else if (r < before_r && c < before_c) {
            int en_id = board[before_r - 1][before_c - 1].id;
            setBoard(player, r, c, role, id, -1000, true);
            setBoard(' ', before_r - 1, before_c - 1, 'n', en_id, -1000, true);
            setBoard(' ', before_r, before_c, 'n', 0, -1000, true);
        } else {}

    }
    //update king role
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (i == 0 && getPlayer(i, j) == 'B') {
                int id = board[i][j].id;
                setBoard('B', i, j, 'k', id, -1000, true);
            }
            if (i == 7 && getPlayer(i, j) == 'A') {
                int id = board[i][j].id;
                setBoard('A', i, j, 'k', id, -1000, true);
            }
        }
    }
    return 'A';
}


void Checker::setNotMoveable(char player, int row, int col, int id) {
    if (board[row][col].player == player && board[row][col].id == id) {
        board[row][col].moveable = false;
    }
}

char Checker::choosePlayer(char player, int id, int row, int col) {
    char result;
    if (player == 'A') {
        result = chanceOfA(player, id, row, col);
    } else {
        result = chanceOfB(player, id, row, col);
    }
    return result;
}

void Checker::setMoveable(char player, int row, int col, int id) {
    if (board[row][col].player == player && board[row][col].id == id) {
        board[row][col].moveable = true;
    }
}

int Checker::stepAvaliable(char player) {
    int counter = 0;
    if (player == 'A') {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (this->board[i][j].player == player && this->board[i][j].role == 'm') {
                    if (i + 1 <= 7 && j - 1 >= 0 && this->board[i + 1][j - 1].player == ' ') {
                        counter++;
                        continue;
                    }
                    if (i + 1 <= 7 && j - 1 >= 0 && this->board[i + 1][j - 1].player == 'B') {
                        if (i + 2 <= 7 && j - 2 >= 0 && this->board[i + 2][j - 2].player == ' ') {
                            counter++;
                            continue;
                        }
                    }
                    if (i + 1 <= 7 && j + 1 <= 7 && this->board[i + 1][j + 1].player == ' ') {
                        counter++;
                        continue;
                    }
                    if (i + 1 <= 7 && j + 1 <= 7 && this->board[i + 1][j + 1].player == 'B') {
                        if (i + 2 <= 7 && j + 2 <= 7 && this->board[i + 2][j + 2].player == ' ') {
                            counter++;
                            continue;
                        }
                    }
                }
                if (this->board[i][j].player == player && this->board[i][j].role == 'k') {
                    if (i + 1 <= 7 && j - 1 >= 0 && this->board[i + 1][j - 1].player == ' ') {
                        counter++;
                        continue;
                    }
                    if (i + 1 <= 7 && j - 1 >= 0 && this->board[i + 1][j - 1].player == 'B') {
                        if (i + 2 <= 7 && j - 2 >= 0 && this->board[i + 2][j - 2].player == ' ') {
                            counter++;
                            continue;
                        }
                    }
                    if (i + 1 <= 7 && j + 1 <= 7 && this->board[i + 1][j + 1].player == ' ') {
                        counter++;
                        continue;
                    }
                    if (i + 1 <= 7 && j + 1 <= 7 && this->board[i + 1][j + 1].player == 'B') {
                        if (i + 2 <= 7 && j + 2 <= 7 && this->board[i + 2][j + 2].player == ' ') {
                            counter++;
                            continue;
                        }
                    }

                    if (i - 1 >= 0 && j - 1 >= 0 && this->board[i - 1][j - 1].player == ' ') {
                        counter++;
                        continue;
                    }
                    if (i - 1 >= 0 && j - 1 >= 0 && this->board[i - 1][j - 1].player == 'B') {
                        if (i - 2 >= 0 && j - 2 >= 0 && this->board[i - 2][j - 2].player == ' ') {
                            counter++;
                            continue;
                        }
                    }
                    if (i - 1 >= 0 && j + 1 <= 7 && this->board[i - 1][j + 1].player == ' ') {
                        counter++;
                        continue;
                    }
                    if (i - 1 >= 0 && j + 1 <= 7 && this->board[i - 1][j + 1].player == 'B') {
                        if (i - 2 >= 0 && j + 2 <= 7 && this->board[i - 2][j + 2].player == ' ') {
                            counter++;
                            continue;
                        }
                    }
                }

            }
        }
    }

    if (player == 'B') {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (this->board[i][j].player == player && this->board[i][j].role == 'm') {
                    if (i - 1 >= 0 && j - 1 >= 0 && this->board[i - 1][j - 1].player == ' ') {
                        counter++;
                        continue;
                    }
                    if (i - 1 >= 0 && j - 1 >= 0 && this->board[i - 1][j - 1].player == 'A') {
                        if (i - 2 >= 0 && j - 2 >= 0 && this->board[i - 2][j - 2].player == ' ') {
                            counter++;
                            continue;
                        }
                    }
                    if (i - 1 >= 0 && j + 1 <= 7 && this->board[i - 1][j + 1].player == ' ') {
                        counter++;
                        continue;
                    }
                    if (i - 1 >= 0 && j + 1 <= 7 && this->board[i - 1][j + 1].player == 'A') {
                        if (i - 2 >= 0 && j + 2 <= 7 && this->board[i - 2][j + 2].player == ' ') {
                            counter++;
                            continue;
                        }
                    }
                }
                if (this->board[i][j].player == player && this->board[i][j].role == 'k') {
                    if (i - 1 >= 0 && j - 1 >= 0 && this->board[i - 1][j - 1].player == ' ') {
                        counter++;
                        continue;
                    }
                    if (i - 1 >= 0 && j - 1 >= 0 && this->board[i - 1][j - 1].player == 'A') {
                        if (i - 2 >= 0 && j - 2 >= 0 && this->board[i - 2][j - 2].player == ' ') {
                            counter++;
                            continue;
                        }
                    }
                    if (i - 1 >= 0 && j + 1 <= 7 && this->board[i - 1][j + 1].player == ' ') {
                        counter++;
                        continue;
                    }
                    if (i - 1 >= 0 && j + 1 <= 7 && this->board[i - 1][j + 1].player == 'A') {
                        if (i - 2 >= 0 && j + 2 <= 7 && this->board[i - 2][j + 2].player == ' ') {
                            counter++;
                            continue;
                        }
                    }

                    if (i + 1 <= 7 && j - 1 >= 0 && this->board[i + 1][j - 1].player == ' ') {
                        counter++;
                        continue;
                    }
                    if (i + 1 <= 7 && j - 1 >= 0 && this->board[i + 1][j - 1].player == 'A') {
                        if (i + 2 <= 7 && j - 2 >= 0 && this->board[i + 2][j - 2].player == ' ') {
                            counter++;
                            continue;
                        }
                    }
                    if (i + 1 <= 7 && j + 1 <= 7 && this->board[i + 1][j + 1].player == ' ') {
                        counter++;
                        continue;
                    }
                    if (i + 1 <= 7 && j + 1 <= 7 && this->board[i + 1][j + 1].player == 'A') {
                        if (i + 2 <= 7 && j + 2 <= 7 && this->board[i + 2][j + 2].player == ' ') {
                            counter++;
                            continue;
                        }
                    }
                }
            }
        }
    }
    return counter;
}

//This function evaluates who is the winner of the game and returns the winning player
char Checker::winningPlayer() {
    int noOfPlayerA = 0;
    int noOfPlayerB = 0;

    noOfPlayerA = stepAvaliable('A');
    noOfPlayerB = stepAvaliable('B');

//    cout<<"\n noOfPlayerA: "<< noOfPlayerA;
//    cout<<"\n noOfPlayerB: "<< noOfPlayerB<<endl;

    if (noOfPlayerA == 0) {
        return 'B';
    }
    if (noOfPlayerB == 0) {
        return 'A';
    }
    if (noOfPlayerA == 1 && noOfPlayerB > 1) {
        return 'B';
    }

    if (noOfPlayerB == 1 && noOfPlayerA > 1) {
        return 'A';
    }

    if (noOfPlayerB == noOfPlayerA && noOfPlayerA == 1) {
        return 'T';
    }
    return 'N';
}



