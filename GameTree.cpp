
#include "GameTree.h"
#include <cstdlib>
#include <ctime>

using namespace std;


int GameTree:: nodes_generated = 0;
int GameTree:: nodes_expanded = 0;


GameTree::GameTree() {

    this->player = 'n';
    this->successors = 0;
    this->row = -1;
    this->col = -1;
    for (int i = 0; i < 48; i++) { // each node can have at most 4 successor(directions)
        successor[i] = NULL;
    }
}

GameTree::GameTree(char pl) {
    this->player = pl;
    this->successors = 0;
    this->row = -1;
    this->col = -1;
    this->id = 0;
    for (int i = 0; i < 48; i++) { // go through all board
        successor[i] = NULL;
    }
}



//test if can jump more than once and return the new location
Location GameTree::jump(int i, int j, Checker checker, char player){
    Location location;
    location.l1 = -2;
    location.l2 = -2;
    location.l3 = -2;
    location.l4 = -2;
    location.l5 = -2;
    location.l6 = -2;
    location.l7 = -2;
    location.l8 = -2;
    if(player == 'A') {
        char p ='B';
        if (checker.board[i][j].role == 'm' && checker.board[i][j].player == player) {
            if (i + 1 <= 7 && j - 1 >= 0) { //check down left first
                if (checker.board[i + 1][j - 1].player == ' '&& checker.board[i + 1][j - 1].moveable == true) {
                    location.l1 = i + 1;
                    location.l2 = j - 1;
//                    cout << "fit function: " << i + 1 << "%" << j - 1 << endl;
                } else if (checker.board[i + 1][j - 1].player == p) {//check down right first
                    if (i + 2 <= 7 && j - 2 >= 0 && checker.board[i + 2][j - 2].player == ' '
                    && checker.board[i + 2][j - 2].moveable == true) {
                        location.l1 = i + 2;
                        location.l2 = j - 2;
//                        cout << "fit function: " << i + 2 << "%" << j - 2 << endl;
                    }
                } else {}
            }

            if (i + 1 <= 7 && j + 1 <= 7) { //check down right first
                if (checker.board[i + 1][j + 1].player == ' '&& checker.board[i + 1][j + 1].moveable == true) {
                    location.l3 = i + 1;
                    location.l4 = j + 1;
//                    cout << "fit function: " << i + 1 << "%" << j + 1 << endl;
                } else if (checker.board[i + 1][j + 1].player == p) {//check down right first
                    if (i + 2 <= 7 && j + 2 <= 7 && checker.board[i + 2][j + 2].player == ' '
                    && checker.board[i + 2][j + 2].moveable == true) {
                        location.l3 = i + 2;
                        location.l4 = j + 2;
//                        cout << "fit function: " << i + 2 << "%" << j + 2 << endl;
                    }
                } else {}
            }
        } else if (checker.board[i][j].role == 'k' && checker.board[i][j].player == player) {

            if (i + 1 <= 7 && j - 1 >= 0) { //check down left first
                if (checker.board[i + 1][j - 1].player == ' '
                    && checker.board[i + 1][j - 1].moveable == true) {
                    location.l1 = i + 1;
                    location.l2 = j - 1;
//                    cout << "fit function: " << i + 1 << "%" << j - 1 << endl;
                } else if (checker.board[i + 1][j - 1].player == p) {//check down right first
                    if (i + 2 <= 7 && j - 2 >= 0 && checker.board[i + 2][j - 2].player == ' '
                    && checker.board[i + 2][j - 2].moveable == true) {
                        location.l1 = i + 2;
                        location.l2 = j - 2;
//                        cout << "fit function: " << i + 2 << "%" << j - 2 << endl;
                    }
                } else {}
            }

            if (i + 1 <= 7 && j + 1 <= 7) { //check down right first
                if (checker.board[i + 1][j + 1].player == ' '
                    && checker.board[i + 1][j + 1].moveable == true) {
                    location.l3 = i + 1;
                    location.l4 = j + 1;
//                    cout << "fit function: " << i + 1 << "%" << j + 1 << endl;
                } else if (checker.board[i + 1][j + 1].player == p) {//check down right first
                    if (i + 2 <= 7 && j + 2 <= 7 && checker.board[i + 2][j + 2].player == ' '
                    && checker.board[i + 2][j + 2].moveable == true) {
                        location.l3 = i + 2;
                        location.l4 = j + 2;
//                        cout << "fit function: " << i + 2 << "%" << j + 2 << endl;
                    }
                } else {}
            }

            if (i - 1 >= 0 && j - 1 >= 0) { //check up left first
                if (checker.board[i - 1][j - 1].player == ' '
                    && checker.board[i - 1][j - 1].moveable == true) {
                    location.l5 = i - 1;
                    location.l6 = j - 1;
//                    cout << "fit function: " << i - 1 << "%" << j - 1 << endl;
                } else if (checker.board[i - 1][j - 1].player == p) {//check down right first
                    if (i - 2 >= 0 && j - 2 >= 0 && checker.board[i - 2][j - 2].player == ' '
                    && checker.board[i - 2][j - 2].moveable == true) {
                        location.l5 = i - 2;
                        location.l6 = j - 2;
//                        cout << "fit function: " << i - 2 << "%" << j - 2 << endl;
                    }
                } else {}
            }

            if (i - 1 >= 0 && j + 1 <= 7) { //check up right first
                if (checker.board[i - 1][j + 1].player == ' '
                    && checker.board[i - 1][j + 1].moveable == true) {
                    location.l7 = i - 1;
                    location.l8 = j + 1;
//                    cout << "fit function: " << i - 1 << "%" << j + 1 << endl;
                } else if (checker.board[i - 1][j + 1].player == p) {//check down right first
                    if (i - 2 >= 0 && j + 2 <= 7 && checker.board[i - 2][j + 2].player == ' '
                    && checker.board[i - 2][j + 2].moveable == true) {
                        location.l7 = i - 2;
                        location.l8 = j + 2;
//                        cout << "fit function: " << i - 2 << "%" << j + 2 << endl;
                    }
                } else {}
            }
        } else if (checker.board[i][j].role == 'n' && checker.board[i][j].player == player) {}
        else {}
    }

    if(player == 'B') {
        char p ='A';
        if (checker.board[i][j].role == 'm' && checker.board[i][j].player == player) {
            if (i - 1 >= 0 && j - 1 >= 0) { //check up left first
                if (checker.board[i - 1][j - 1].player == ' '
                    && checker.board[i - 1][j - 1].moveable == true) {
                    location.l1 = i - 1;
                    location.l2 = j - 1;
//                    cout << "fit function: " << i - 1 << "%" << j - 1 << endl;
                } else if (checker.board[i - 1][j - 1].player == p) {//check down right first
                    if (i - 2 >= 0 && j - 2 >= 0 && checker.board[i - 2][j - 2].player == ' '
                        && checker.board[i - 2][j - 2].moveable == true) {
                        location.l1 = i - 2;
                        location.l2 = j - 2;
//                        cout << "fit function: " << i - 2 << "%" << j - 2 << endl;
                    }
                } else {}
            }

            if (i - 1 >= 0 && j + 1 <= 7) { //check up right first
                if (checker.board[i - 1][j + 1].player == ' '
                    && checker.board[i - 1][j + 1].moveable == true) {
                    location.l3 = i - 1;
                    location.l4 = j + 1;
//                    cout << "fit function: " << i - 1 << "%" << j + 1 << endl;
                } else if (checker.board[i - 1][j + 1].player == p) {//check down right first
                    if (i - 2 >= 0 && j + 2 <= 7 && checker.board[i - 2][j + 2].player == ' '
                    && checker.board[i - 2][j + 2].moveable == true) {
                        location.l3 = i - 2;
                        location.l4 = j + 2;
//                        cout << "fit function: " << i - 2 << "%" << j + 2 << endl;
                    }
                } else {}
            }
        } else if (checker.board[i][j].role == 'k' && checker.board[i][j].player == player) {
            if (i - 1 >= 0 && j - 1 >= 0) { //check up left first
                if (checker.board[i - 1][j - 1].player == ' '
                    && checker.board[i - 1][j - 1].moveable == true) {
                    location.l1 = i - 1;
                    location.l2 = j - 1;
//                    cout << "fit function: " << i - 1 << "%" << j - 1 << endl;
                } else if (checker.board[i - 1][j - 1].player == p) {//check down right first
                    if (i - 2 >= 0 && j - 2 >= 0 && checker.board[i - 2][j - 2].player == ' '
                    && checker.board[i - 2][j - 2].moveable == true) {
                        location.l1 = i - 2;
                        location.l2 = j - 2;
//                        cout << "fit function: " << i - 2 << "%" << j - 2 << endl;
                    }
                } else {}
            }

            if (i - 1 >= 0 && j + 1 <= 7) { //check up right first
                if (checker.board[i - 1][j + 1].player == ' '
                    && checker.board[i - 1][j + 1].moveable == true) {
                    location.l3 = i - 1;
                    location.l4 = j + 1;
//                    cout << "fit function: " << i - 1 << "%" << j + 1 << endl;
                } else if (checker.board[i - 1][j + 1].player == p) {//check down right first
                    if (i - 2 >= 0 && j + 2 <= 7 && checker.board[i - 2][j + 2].player == ' '
                    && checker.board[i - 2][j + 2].moveable == true) {
                        location.l3 = i - 2;
                        location.l4 = j + 2;
//                        cout << "fit function: " << i - 2 << "%" << j + 2 << endl;
                    }
                } else {}
            }

            if (i + 1 <= 7 && j - 1 >= 0) { //check down left first
                if (checker.board[i + 1][j - 1].player == ' '
                    && checker.board[i + 1][j - 1].moveable == true) {
                    location.l5 = i + 1;
                    location.l6 = j - 1;
//                    cout << "fit function: " << i + 1 << "%" << j - 1 << endl;
                } else if (checker.board[i + 1][j - 1].player == p) {//check down right first
                    if (i + 2 <= 7 && j - 2 >= 0 && checker.board[i + 2][j - 2].player == ' '
                    && checker.board[i + 2][j - 2].moveable == true) {
                        location.l5 = i + 2;
                        location.l6 = j - 2;
//                        cout << "fit function: " << i + 2 << "%" << j - 2 << endl;
                    }
                } else {}
            }

            if (i + 1 <= 7 && j + 1 <= 7) { //check up right first
                if (checker.board[i + 1][j + 1].player == ' '
                    && checker.board[i + 1][j + 1].moveable == true) {
                    location.l7 = i + 1;
                    location.l8 = j + 1;
//                    cout << "fit function: " << i + 1 << "%" << j + 1 << endl;
                } else if (checker.board[i + 1][j + 1].player == p) {//check down right first
                    if (i + 2 <= 7 && j + 2 <= 7 && checker.board[i + 2][j + 2].player == ' '
                    && checker.board[i + 2][j + 2].moveable == true) {
                        location.l7 = i + 2;
                        location.l8 = j + 2;
//                        cout << "fit function: " << i + 2 << "%" << j + 2 << endl;
                    }
                } else {}
            }
        } else if (checker.board[i][j].role == 'n' && checker.board[i][j].player == player) {}
        else {}
    }

    return location;
    }

  void GameTree::setHeuristicValue(int value, Checker k, int id, int row, int col) {
    this->currentboard.heuristic_value = value;
    this->heuristic_board = k;
    this->id = id;
    this->row = row;
    this->col = col;

}

//find a right position, store it into the successor array and move
void GameTree::generateChildren(char player) {
    //go through the every potential locations of enemy and store it to created children array
    //if it's available, add it into the child list
    Location location;
    int children_num = 0;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(player == 'A'){
                char p = 'B';
                location = jump(i,j,this->currentboard,'A');

                if(available_to_jump(location) == true) {
                    //cout<<"\ncurrent ture situation -A:"<< i<<","<<j<<endl;
                    //use location to perform jumps and generate children
                    if (this->currentboard.board[i][j].role == 'm') {
                        if(location.l1 != -2 && location.l2 != -2){
                            successor[children_num] = new GameTree(p);
                            successor[children_num]->currentboard = this->currentboard;
                            successor[children_num]->currentboard.choosePlayer('A', this->currentboard.board[i][j].id,location.l1, location.l2);
                            children_num++;
                            nodes_generated++;
                        }
                        if(location.l3 != -2 && location.l4 != -2){
                            successor[children_num] = new GameTree(p);
                            successor[children_num]->currentboard = this->currentboard;
                            successor[children_num]->currentboard.choosePlayer('A', this->currentboard.board[i][j].id,location.l3, location.l4);
                            children_num++;
                            nodes_generated++;
                        }

                    } else if (this->currentboard.board[i][j].role == 'k') {
                        if(location.l1 != -2 && location.l2 != -2){
                            successor[children_num] = new GameTree(p);
                            successor[children_num]->currentboard = this->currentboard;
                            successor[children_num]->currentboard.choosePlayer('A', this->currentboard.board[i][j].id,location.l1, location.l2);
                            children_num++;
                            nodes_generated++;
                        }
                        if(location.l3 != -2 && location.l4 != -2){
                            successor[children_num] = new GameTree(p);
                            successor[children_num]->currentboard = this->currentboard;
                            successor[children_num]->currentboard.choosePlayer('A', this->currentboard.board[i][j].id,location.l3, location.l4);
                            children_num++;
                            nodes_generated++;
                        }
                        if(location.l5 != -2 && location.l6 != -2){
                            successor[children_num] = new GameTree(p);
                            successor[children_num]->currentboard = this->currentboard;
                            successor[children_num]->currentboard.choosePlayer('A', this->currentboard.board[i][j].id,location.l5, location.l6);
                            children_num++;
                            nodes_generated++;
                        }
                        if(location.l7 != -2 && location.l8 != -2){
                            successor[children_num] = new GameTree(p);
                            successor[children_num]->currentboard = this->currentboard;
                            successor[children_num]->currentboard.choosePlayer('A', this->currentboard.board[i][j].id,location.l7, location.l8);
                            children_num++;
                            nodes_generated++;
                        }
                    }else {}
                }
            }
            else if(player == 'B') {
                char p = 'A';

                location = jump(i, j, this->currentboard, 'B');
                if (available_to_jump(location) == true) {
//                    cout<<"\ncurrent ture situation-B : "<< i<<","<<j<<endl;
                    if (this->currentboard.board[i][j].role == 'm') {
                            if (location.l1 != -2 && location.l2 != -2) {
                                successor[children_num] = new GameTree(p);
                                successor[children_num]->currentboard = this->currentboard;
                                successor[children_num]->currentboard.choosePlayer('B', this->currentboard.board[i][j].id,location.l1, location.l2);
                                children_num++;
                                nodes_generated++;
                            }
                            if (location.l3 != -2 && location.l4 != -2) {
                                successor[children_num] = new GameTree(p);
                                successor[children_num]->currentboard = this->currentboard;
                                successor[children_num]->currentboard.choosePlayer('B', this->currentboard.board[i][j].id,location.l3, location.l4);
                                children_num++;
                                nodes_generated++;
                            }
                        } else if (this->currentboard.board[i][j].role == 'k') {
                            if (location.l1 != -2 && location.l2 != -2) {
                                successor[children_num] = new GameTree(p);
                                successor[children_num]->currentboard = this->currentboard;
                                successor[children_num]->currentboard.choosePlayer('B', this->currentboard.board[i][j].id,location.l1, location.l2);
                                children_num++;
                                nodes_generated++;
                            }
                            if (location.l3 != -2 && location.l4 != -2) {
                                successor[children_num] = new GameTree(p);
                                successor[children_num]->currentboard = this->currentboard;
                                successor[children_num]->currentboard.choosePlayer('B', this->currentboard.board[i][j].id,location.l3, location.l4);
                                children_num++;
                                nodes_generated++;
                            }
                            if (location.l5 != -2 && location.l6 != -2) {
                                successor[children_num] = new GameTree(p);
                                successor[children_num]->currentboard = this->currentboard;
                                successor[children_num]->currentboard.choosePlayer('B', this->currentboard.board[i][j].id,location.l5, location.l6);
                                children_num++;
                                nodes_generated++;
                            }
                            if (location.l7 != -2 && location.l8 != -2) {
                                successor[children_num] = new GameTree(p);
                                successor[children_num]->currentboard = this->currentboard;
                                successor[children_num]->currentboard.choosePlayer('B', this->currentboard.board[i][j].id,location.l7, location.l8);
                                children_num++;
                                nodes_generated++;
                            }
                        }
                        else{}
                    }
                }else{}
            }
        }
    }

bool GameTree::deepenough(int depth, char player) {

    if (depth >= 2 || this->currentboard.winningPlayer() != 'N'){
        return true;
    } else if(depth == 1){

        nodes_expanded++;
        generateChildren2(player);
        return false;
    }else{
        nodes_expanded++;
        generateChildren(player);
        return false;
    }

}



int GameTree::evaluation1( char player) {// good for player A , keep the threathen as the stratage
    int points=0;
    if (player == 'A') {
        //check piece
        for (int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                if(currentboard.board[i][j].role == 'm' && currentboard.board[i][j].player == 'A'){
                    points +=3;
                }else if (currentboard.board[i][j].role == 'k' && currentboard.board[i][j].player == 'A'){
                    points +=6;
                }else if (currentboard.board[i][j].role == 'm' && currentboard.board[i][j].player == 'B'){
                    points -=3;//1 to 3
                }else if (currentboard.board[i][j].role == 'k' && currentboard.board[i][j].player == 'B'){
                    points -=6;//2 to 6
                }else{}
            }
        }
        //check side
        for (int i = 5; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (currentboard.board[i][j].player == 'A') {
                    points += 5;
                }
            }
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 8; j++) {
                if (currentboard.board[i][j].player == 'B') {
                    points -= 5;
                }
            }
        }

//        threatened
        for (int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                if(threaten(i,j, currentboard,'A')){
                    points +=10;
                }else if(threaten(i,j, currentboard,'B')){
                    points -=5;
                }else{}
            }
        }

    } else if (player == 'B') {
        //check piece
        for (int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                if(currentboard.board[i][j].role == 'm' && currentboard.board[i][j].player == 'B'){
                    points +=3;
                }else if (currentboard.board[i][j].role == 'k' && currentboard.board[i][j].player == 'B'){
                    points +=6;
                }else if (currentboard.board[i][j].role == 'm' && currentboard.board[i][j].player == 'A'){
                    points -=3;
                }else if (currentboard.board[i][j].role == 'k' && currentboard.board[i][j].player == 'A'){
                    points -=6;
                }else{}
            }
        }

        }

    return points;
}

int GameTree::evaluation2( char player) { // good for player B ,keep the more the better
    int points=0;
    if (player == 'A') {
//        cout<<"test -- evaluationA: "<<endl;
        //check piece
        for (int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                if(currentboard.board[i][j].role == 'm' && currentboard.board[i][j].player == 'A'){
                    points +=10;
                }else if (currentboard.board[i][j].role == 'k' && currentboard.board[i][j].player == 'A'){
                    points +=20;
                }else if (currentboard.board[i][j].role == 'm' && currentboard.board[i][j].player == 'B'){
                    points -=10;
                }else if (currentboard.board[i][j].role == 'k' && currentboard.board[i][j].player == 'B'){
                    points -=20;
                }else{}
            }
        }
//        cout<<"\ntest--evaluation1: "<< value<<endl;
        //check side
        for (int i = 5; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (currentboard.board[i][j].player == 'A') {
                    points += 8;
                }
            }
        }

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 8; j++) {
                if (currentboard.board[i][j].player == 'B') {
                    points -= 8;
                }
            }
        }


    } else if (player == 'B') {

        for (int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                if(currentboard.board[i][j].role == 'm' && currentboard.board[i][j].player == 'B'){
                    points +=20;
                }else if (currentboard.board[i][j].role == 'k' && currentboard.board[i][j].player == 'B'){
                    points +=40;
                }else if (currentboard.board[i][j].role == 'm' && currentboard.board[i][j].player == 'A'){
                    points -=10;
                }else if (currentboard.board[i][j].role == 'k' && currentboard.board[i][j].player == 'A'){
                    points -=20;
                }else{}
            }
        }
//        cout<<"\ntest--evaluation1: "<< points<<endl;
        //check side
        for (int i = 5; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (currentboard.board[i][j].player == 'A') {
                    points -= 8;
                }
            }
        }

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 8; j++) {
                if (currentboard.board[i][j].player == 'B') {
                    points += 8;
                }
            }
        }

    }


    return points;
}

void GameTree::newCurrentBoard(Checker checker) {
    this->currentboard = checker;
    this->currentboard.heuristic_value = checker.heuristic_value;
    this->currentboard.address = checker.address;
}

bool GameTree::threaten(int i, int j, Checker checker, char player){
    char p = (player == 'A')? 'B':'A';
    if(i-1>=0 && j-1>=0 && checker.board[i-1][j-1].player == p){
        if(i+1<=7 && j+1<=7 && checker.board[i+1][j+1].player == ' '){
            return true;
        }
    }
    else if(i-1>=0 && j+1<=7 && checker.board[i-1][j+1].player == p){
        if(i+1<=7 && j-1>=0 && checker.board[i+1][j-1].player == ' '){
            return true;
        }
    }
    else if(i+1<=7 && j-1>=0 && checker.board[i+1][j-1].player == p){
        if(i-1>=0 && j+1<=7 && checker.board[i-1][j+1].player == ' '){
            return true;
        }
    }
    else if(i+1<=7 && j+1<=7 && checker.board[i+1][j+1].player == p){
        if(i-1>=0 && j-1>=0 && checker.board[i-1][j-1].player == ' '){
            return true;
        }
    } else{
        return false;
    }
    return false;
}

bool GameTree::available_to_jump(Location location){

    if(location.l1 != -2 && location.l2){
        return true;
    }

    if(location.l3 != -2 && location.l4){
        return true;
    }

    if(location.l5 != -2 && location.l6){
        return true;
    }

    if(location.l7 != -2 && location.l8){
        return true;
    }

    return false;
}

void GameTree::generateChildren2(char player) {
    //go through the every potential locations of enemy and store it to create children array
    //if it's available, add it into the child list
    Location location;
    int children_num = 0;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(player == 'A'){
                char p = 'B';
                location = jump(i,j,this->currentboard,'A');

                if(available_to_jump(location) == true) {
//                    cout<<"\nAdd all child 2 --current ture situation -A:"<< i<<","<<j<<endl;
                    //use location to perform jumps and generate children
                    if (this->currentboard.board[i][j].role == 'm') {
                        if(location.l1 != -2 && location.l2 != -2){
                            successor[children_num] = new GameTree(p);
                            successor[children_num]->currentboard = this->currentboard;
                            successor[children_num]->currentboard.choosePlayer('A', this->currentboard.board[i][j].id,location.l1, location.l2);
                            successor[children_num]->row = location.l1;
                            successor[children_num]->col = location.l2;
                            successor[children_num]->id = this->currentboard.board[i][j].id;
                            children_num++;
                            nodes_generated++;
                        }
                        if(location.l3 != -2 && location.l4 != -2){
                            successor[children_num] = new GameTree(p);
                            successor[children_num]->currentboard = this->currentboard;
                            successor[children_num]->currentboard.choosePlayer('A', this->currentboard.board[i][j].id,location.l3, location.l4);
                            successor[children_num]->row = location.l3;
                            successor[children_num]->col = location.l4;
                            successor[children_num]->id = this->currentboard.board[i][j].id;
                            children_num++;
                            nodes_generated++;
                        }

                    } else if (this->currentboard.board[i][j].role == 'k') {
                        if(location.l1 != -2 && location.l2 != -2){
                            successor[children_num] = new GameTree(p);
                            successor[children_num]->currentboard = this->currentboard;
                            successor[children_num]->currentboard.choosePlayer('A', this->currentboard.board[i][j].id,location.l1, location.l2);
                            successor[children_num]->row = location.l1;
                            successor[children_num]->col = location.l2;
                            successor[children_num]->id = this->currentboard.board[i][j].id;
                            children_num++;
                            nodes_generated++;
                        }
                        if(location.l3 != -2 && location.l4 != -2){
                            successor[children_num] = new GameTree(p);
                            successor[children_num]->currentboard = this->currentboard;
                            successor[children_num]->currentboard.choosePlayer('A', this->currentboard.board[i][j].id,location.l3, location.l4);
                            successor[children_num]->row = location.l3;
                            successor[children_num]->col = location.l4;
                            successor[children_num]->id = this->currentboard.board[i][j].id;
                            children_num++;
                            nodes_generated++;
                        }
                        if(location.l5 != -2 && location.l6 != -2){
                            successor[children_num] = new GameTree(p);
                            successor[children_num]->currentboard = this->currentboard;
                            successor[children_num]->currentboard.choosePlayer('A', this->currentboard.board[i][j].id,location.l5, location.l6);
                            successor[children_num]->row = location.l5;
                            successor[children_num]->col = location.l6;
                            successor[children_num]->id = this->currentboard.board[i][j].id;
                            children_num++;
                            nodes_generated++;
                        }
                        if(location.l7 != -2 && location.l8 != -2){
                            successor[children_num] = new GameTree(p);
                            successor[children_num]->currentboard = this->currentboard;
                            successor[children_num]->currentboard.choosePlayer('A', this->currentboard.board[i][j].id,location.l7, location.l8);
                            successor[children_num]->row = location.l7;
                            successor[children_num]->col = location.l8;
                            successor[children_num]->id = this->currentboard.board[i][j].id;
                            children_num++;
                            nodes_generated++;
                        }
                    }else {}
                }
            }
            else if(player == 'B') {
                char p = 'A';
                location = jump(i, j, this->currentboard, 'B');
                if (available_to_jump(location) == true) {
                    if (this->currentboard.board[i][j].role == 'm') {
                        if (location.l1 != -2 && location.l2 != -2) {
                            successor[children_num] = new GameTree(p);
                            successor[children_num]->currentboard = this->currentboard;
                            successor[children_num]->currentboard.choosePlayer('B', this->currentboard.board[i][j].id,location.l1, location.l2);
                            successor[children_num]->row = location.l1;
                            successor[children_num]->col = location.l2;
                            successor[children_num]->id = this->currentboard.board[i][j].id;
                            children_num++;
                            nodes_generated++;
                        }
                        if (location.l3 != -2 && location.l4 != -2) {
                            successor[children_num] = new GameTree(p);
                            successor[children_num]->currentboard = this->currentboard;
                            successor[children_num]->currentboard.choosePlayer('B', this->currentboard.board[i][j].id,location.l3, location.l4);
                            successor[children_num]->row = location.l3;
                            successor[children_num]->col = location.l4;
                            successor[children_num]->id = this->currentboard.board[i][j].id;
                            children_num++;
                            nodes_generated++;
                        }
                    } else if (this->currentboard.board[i][j].role == 'k') {
                        if (location.l1 != -2 && location.l2 != -2) {
                            successor[children_num] = new GameTree(p);
                            successor[children_num]->currentboard = this->currentboard;
                            successor[children_num]->currentboard.choosePlayer('B', this->currentboard.board[i][j].id,location.l1, location.l2);
                            successor[children_num]->row = location.l1;
                            successor[children_num]->col = location.l2;
                            successor[children_num]->id = this->currentboard.board[i][j].id;
                            children_num++;
                            nodes_generated++;
                        }
                        if (location.l3 != -2 && location.l4 != -2) {
                            successor[children_num] = new GameTree(p);
                            successor[children_num]->currentboard = this->currentboard;
                            successor[children_num]->currentboard.choosePlayer('B', this->currentboard.board[i][j].id,location.l3, location.l4);
                            successor[children_num]->row = location.l3;
                            successor[children_num]->col = location.l4;
                            successor[children_num]->id = this->currentboard.board[i][j].id;
                            children_num++;
                            nodes_generated++;
                        }
                        if (location.l5 != -2 && location.l6 != -2) {
                            successor[children_num] = new GameTree(p);
                            successor[children_num]->currentboard = this->currentboard;
                            successor[children_num]->currentboard.choosePlayer('B', this->currentboard.board[i][j].id,location.l5, location.l6);
                            successor[children_num]->row = location.l5;
                            successor[children_num]->col = location.l6;
                            successor[children_num]->id = this->currentboard.board[i][j].id;
                            children_num++;
                            nodes_generated++;
                        }
                        if (location.l7 != -2 && location.l8 != -2) {
                            successor[children_num] = new GameTree(p);
                            successor[children_num]->currentboard = this->currentboard;
                            successor[children_num]->currentboard.choosePlayer('B', this->currentboard.board[i][j].id,location.l7, location.l8);
                            successor[children_num]->row = location.l7;
                            successor[children_num]->col = location.l8;
                            successor[children_num]->id = this->currentboard.board[i][j].id;
                            children_num++;
                            nodes_generated++;
                        }
                    }
                    else{}
                }
            }else{}
        }
    }
}

void GameTree::setId(int id) {
    GameTree::id = id;
}

void GameTree::setRow(int row) {
    GameTree::row = row;
}

void GameTree::setCol(int col) {
    GameTree::col = col;
}

int GameTree::getnodeGenerated(){
 return nodes_generated;
}

int GameTree::getnodeExpanded(){
 return nodes_expanded;
}
