
#include "GameTree.h"
#include <cstdlib>
#include <ctime>

using namespace std;
//extern int  ALGO_FLAG;

extern int nodes_generated, nodes_expanded;

GameTree::GameTree() {
//    board_status.board.heuristic_value = -1000;
    this->player = 'n';
    this->number_of_children = 0;
    this->row = -1;
    this->col = -1;
    for (int i = 0; i < 48; i++) { // each node can have at most 4 children(directions)
        children[i] = NULL;
    }
}

GameTree::GameTree(char p) {
    this->player = p;
//    this->board_status.board.heuristic_value = -1000;
    this->number_of_children = 0;
    this->row = -1;
    this->col = -1;
    this->id = 0;
    for (int i = 0; i < 48; i++) { // go through all board
        children[i] = NULL;
    }
}

void GameTree::create_node(char p) {
    children[number_of_children++] = new GameTree(p);
}

void GameTree::set_heuristic_value(int value, Checker k, int id, int row, int col) {
    this->board_status.heuristic_value = value;
    this->heuristic_board = k;
    this->id = id;
    this->row = row;
    this->col = col;

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

//find a right position, store it into the children array and move
void GameTree::add_all_children(char player) {
    //go through the every potential locations of enemy and store it to created children array
    //if it's available, add it into the child list
    Location location;
    int children_num = 0;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(player == 'A'){
                char p = 'B';
                location = jump(i,j,this->board_status,'A');

                if(available_to_jump(location) == true) {
                    //cout<<"\ncurrent ture situation -A:"<< i<<","<<j<<endl;
                    //use location to perform jumps and generate children
                    if (this->board_status.board[i][j].role == 'm') {
                        if(location.l1 != -2 && location.l2 != -2){
                            children[children_num] = new GameTree(p);
                            children[children_num]->board_status = this->board_status;
                            children[children_num]->board_status.move('A', this->board_status.board[i][j].id,location.l1, location.l2);
                            children_num++;
                        }
                        if(location.l3 != -2 && location.l4 != -2){
                            children[children_num] = new GameTree(p);
                            children[children_num]->board_status = this->board_status;
                            children[children_num]->board_status.move('A', this->board_status.board[i][j].id,location.l3, location.l4);
                            children_num++;
                        }

                    } else if (this->board_status.board[i][j].role == 'k') {
                        if(location.l1 != -2 && location.l2 != -2){
                            children[children_num] = new GameTree(p);
                            children[children_num]->board_status = this->board_status;
                            children[children_num]->board_status.move('A', this->board_status.board[i][j].id,location.l1, location.l2);
                            children_num++;
                        }
                        if(location.l3 != -2 && location.l4 != -2){
                            children[children_num] = new GameTree(p);
                            children[children_num]->board_status = this->board_status;
                            children[children_num]->board_status.move('A', this->board_status.board[i][j].id,location.l3, location.l4);
                            children_num++;
                        }
                        if(location.l5 != -2 && location.l6 != -2){
                            children[children_num] = new GameTree(p);
                            children[children_num]->board_status = this->board_status;
                            children[children_num]->board_status.move('A', this->board_status.board[i][j].id,location.l5, location.l6);
                            children_num++;
                        }
                        if(location.l7 != -2 && location.l8 != -2){
                            children[children_num] = new GameTree(p);
                            children[children_num]->board_status = this->board_status;
                            children[children_num]->board_status.move('A', this->board_status.board[i][j].id,location.l7, location.l8);
                            children_num++;
                        }
                    }else {}
                }
            }
            else if(player == 'B') {
                char p = 'A';
                location = jump(i, j, this->board_status, 'B');
                if (available_to_jump(location) == true) {
//                    cout<<"\ncurrent ture situation-B : "<< i<<","<<j<<endl;
                    if (this->board_status.board[i][j].role == 'm') {
                            if (location.l1 != -2 && location.l2 != -2) {
                                children[children_num] = new GameTree(p);
                                children[children_num]->board_status = this->board_status;
                                children[children_num]->board_status.move('B', this->board_status.board[i][j].id,location.l1, location.l2);
                                children_num++;
                            }
                            if (location.l3 != -2 && location.l4 != -2) {
                                children[children_num] = new GameTree(p);
                                children[children_num]->board_status = this->board_status;
                                children[children_num]->board_status.move('B', this->board_status.board[i][j].id,location.l3, location.l4);
                                children_num++;
                            }
                        } else if (this->board_status.board[i][j].role == 'k') {
                            if (location.l1 != -2 && location.l2 != -2) {
                                children[children_num] = new GameTree(p);
                                children[children_num]->board_status = this->board_status;
                                children[children_num]->board_status.move('B', this->board_status.board[i][j].id,location.l1, location.l2);
                                children_num++;
                            }
                            if (location.l3 != -2 && location.l4 != -2) {
                                children[children_num] = new GameTree(p);
                                children[children_num]->board_status = this->board_status;
                                children[children_num]->board_status.move('B', this->board_status.board[i][j].id,location.l3, location.l4);
                                children_num++;
                            }
                            if (location.l5 != -2 && location.l6 != -2) {
                                children[children_num] = new GameTree(p);
                                children[children_num]->board_status = this->board_status;
                                children[children_num]->board_status.move('B', this->board_status.board[i][j].id,location.l5, location.l6);
                                children_num++;
                            }
                            if (location.l7 != -2 && location.l8 != -2) {
                                children[children_num] = new GameTree(p);
                                children[children_num]->board_status = this->board_status;
                                children[children_num]->board_status.move('B', this->board_status.board[i][j].id,location.l7, location.l8);
                                children_num++;
                            }
                        }
                        else{}
                    }
                }else{}
            }
        }
    }

bool GameTree::deepenough(int depth, char player) {
//    if (this->board_status.get_heuristic_value_board() != -1000)
//        return board_status.get_heuristic_value_board();
    //if the depth is greater than 3 or a player has won the game then it is deep enough.
    if (depth >= 2 || this->board_status.checkWin() != 'N'){
        return true;
    } else if(depth == 1){
//        cout<<"\ndeepenough---when depth == 1, add child with it's location"<<endl;
        nodes_expanded++;
        add_all_children2(player); //store the level one child location
        return false;
    }else{
        nodes_expanded++;
        add_all_children(player);
        return false;
    }

}

void GameTree::print(GameTree *node, int nestLevel) {
    cout << node->player << ":" << board_status.get_heuristic_value_board() << endl;
    int i, j;
    for (i = 0; node->children[i] != NULL && i < 6; i++) {
        for (j = 0; j < nestLevel; j++)
            cout << "\t";
        print(node->children[i], nestLevel + 1);
    }
}

/////////////////////////////////////
///       BURAK'S EVALUATION      ///
/////////////////////////////////////

int GameTree::evaluation1( char player) {// good for player A
    int value=0;
    if (player == 'A') {
        //check piece
        for (int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                if(board_status.board[i][j].role == 'm' && board_status.board[i][j].player == 'A'){
                    value +=2;
                }else if (board_status.board[i][j].role == 'k' && board_status.board[i][j].player == 'A'){
                    value +=4;
                }else if (board_status.board[i][j].role == 'm' && board_status.board[i][j].player == 'B'){
                    value -=1;
                }else if (board_status.board[i][j].role == 'k' && board_status.board[i][j].player == 'B'){
                    value -=2;
                }else{}
            }
        }
        //check side
        for (int i = 5; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (board_status.board[i][j].player == 'A') {
                    value += 5;
                }
            }
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 8; j++) {
                if (board_status.board[i][j].player == 'B') {
                    value -= 5;
                }
            }
        }

//        threatened
        for (int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                if(threaten(i,j, board_status,'A')){
                    value +=10;
                }else if(threaten(i,j, board_status,'B')){
                    value -=5;
                }else{}
            }
        }

    } else if (player == 'B') {
        //check piece
        for (int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                if(board_status.board[i][j].role == 'm' && board_status.board[i][j].player == 'B'){
                    value +=2;
                }else if (board_status.board[i][j].role == 'k' && board_status.board[i][j].player == 'B'){
                    value +=4;
                }else if (board_status.board[i][j].role == 'm' && board_status.board[i][j].player == 'A'){
                    value -=1;
                }else if (board_status.board[i][j].role == 'k' && board_status.board[i][j].player == 'A'){
                    value -=2;
                }else{}
            }
        }
        //check side

        for (int i = 5; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (board_status.board[i][j].player == 'A') {
                    value -= 5;
                }
            }
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 8; j++) {
                if (board_status.board[i][j].player == 'B') {
                    value += 5;
                }
            }
        }
        //threatened
        for (int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                if(threaten(i,j, board_status,'B')){
                    value +=8;
                }else if(threaten(i,j, board_status,'A')){
                    value -=4;
                }else{}
            }
        }
    }
    return value;
}

int GameTree::evaluation2( char player) { // good for player B
    int value=0;
    if (player == 'A') {
//        cout<<"test -- evaluationA: "<<endl;
        //check piece
        for (int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                if(board_status.board[i][j].role == 'm' && board_status.board[i][j].player == 'A'){
                    value +=10;
                }else if (board_status.board[i][j].role == 'k' && board_status.board[i][j].player == 'A'){
                    value +=20;
                }else if (board_status.board[i][j].role == 'm' && board_status.board[i][j].player == 'B'){
                    value -=10;
                }else if (board_status.board[i][j].role == 'k' && board_status.board[i][j].player == 'B'){
                    value -=20;
                }else{}
            }
        }
//        cout<<"\ntest--evaluation1: "<< value<<endl;
        //check side
        for (int i = 5; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (board_status.board[i][j].player == 'A') {
                    value += 8;
                }
            }
        }

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 8; j++) {
                if (board_status.board[i][j].player == 'B') {
                    value -= 8;
                }
            }
        }
//        cout<<"\ntest--evaluation2: "<< value<<endl;
//        for (int i = 0; i < 4; i++) {
//            for (int j = 0; j < 4; j++) {
//                if (board_status.board[i][j].player == 'B') {
//                    value -= 10;
//                }
//            }
//        }
//        cout<<"\ntest--evaluation3: "<< value<<endl;
        //threatened
//        for (int i = 0; i < 8; i++) {
//            for(int j = 0; j < 8; j++) {
//                if(threaten(i,j, board_status,'A')){
//                    value +=2;
//                }else if(threaten(i,j, board_status,'B')){
//                    value -=11;
//                }else{}
//            }
//        }
//        cout<<"\ntest--evaluation4: "<< value<<endl;

    } else if (player == 'B') {
//        cout<<"test -- evaluationB : "<<endl;
        //check piece
        for (int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                if(board_status.board[i][j].role == 'm' && board_status.board[i][j].player == 'B'){
                    value +=20;
                }else if (board_status.board[i][j].role == 'k' && board_status.board[i][j].player == 'B'){
                    value +=40;
                }else if (board_status.board[i][j].role == 'm' && board_status.board[i][j].player == 'A'){
                    value -=10;
                }else if (board_status.board[i][j].role == 'k' && board_status.board[i][j].player == 'A'){
                    value -=20;
                }else{}
            }
        }
//        cout<<"\ntest--evaluation1: "<< value<<endl;
        //check side
        for (int i = 5; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (board_status.board[i][j].player == 'A') {
                    value -= 8;
                }
            }
        }

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 8; j++) {
                if (board_status.board[i][j].player == 'B') {
                    value += 8;
                }
            }
        }
//        cout<<"\ntest--evaluation2: "<< value<<endl;
//        for (int i = 0; i < 4; i++) {
//            for (int j = 0; j < 4; j++) {
//                if (board_status.board[i][j].player == 'A') {
//                    value -= 4;
//                }
//            }
//        }
//        cout<<"\ntest--evaluation3: "<< value<<endl;
        //threatened
//        for (int i = 0; i < 8; i++) {
//            for(int j = 0; j < 8; j++) {
//                if(threaten(i,j, board_status,'B')){
//                    value +=10;
//                }else if(threaten(i,j, board_status,'A')){
//                    value -=10;
//                }else{}
//            }
//        }
//        cout<<"\ntest--evaluation : "<< value<<endl;
    }

    //set_heuristic_value(value);
    return value;
}

void GameTree::copyBoardStatus(Checker kb) {
    this->board_status = kb;
    this->board_status.heuristic_value = kb.heuristic_value;
    this->board_status.address = kb.address;
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

/////////////////////////////////////
///       HURSH'S EVALUATION      ///
/////////////////////////////////////
// int GameTree::evaluation()
// {
//     int value;
//     if(player == 'A')
//     {
//         int a_stones = 0;
//         for(int i = 0 ; i < 6 ; i++)
//         {
//             if(board_status.A[i] == 0)
//                 a_stones++;
//         }
//         if(a_stones == 6)
//             value = 1000;
//     }
//     else if(player == 'B')
//     {
//         int b_stones = 0;
//         for(int i = 0 ; i < 6 ; i++)
//         {
//             if(board_status.B[i] == 0)
//                 b_stones++;
//         }
//         if(b_stones == 6)
//             value = -1000;
//     }
//     set_heuristic_value(value);
//     return value;
// }


/////////////////////////////////////
///       RANDY'S EVALUATION      ///
/////////////////////////////////////

// int GameTree::evaluation()
// {
//     int value;
//     if(player == 'A')
//     {
//         int a_pits = 0;
//         for(int i = 0 ; i < 6 ; i++)
//         {
//             if(board_status.A[i] == 0)
//                 a_pits++;
//             else if (board_status.A[i] == i) // last stone in checker. one more chance to play
//                 value = 2000;
//             else if (board_status.A[i] > i ) // last stone in self side
//                 value = 800;
//             else
//                 value = 300; // last stone in opponent side
//         }
//         if(a_pits == 6)
//             value = 5000;
//     }
//     else if(player == 'B')
//     {
//         int b_pits = 0;
//         for(int i = 0 ; i < 6 ; i++)
//         {
//             if(board_status.B[i] == 0)
//                 b_pits++;
//             else if (board_status.B[i] == i) // last stone in checker. one more chance to play
//                 value = 2000;
//             else if (board_status.B[i] < i ) // last stone in opponent side
//                 value = 800;
//             else
//                 value = 300; // last stone in opponent side
//         }
//         if(b_pits == 6)
//             value = 5000;
//     }
//     set_heuristic_value(value);
//     return value;


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

const Checker &GameTree::getHeuristicBoard() const {
    return heuristic_board;
}

void GameTree::add_all_children2(char player) {
    //go through the every potential locations of enemy and store it to created children array
    //if it's available, add it into the child list
    Location location;
    int children_num = 0;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(player == 'A'){
                char p = 'B';
                location = jump(i,j,this->board_status,'A');

                if(available_to_jump(location) == true) {
//                    cout<<"\nAdd all child 2 --current ture situation -A:"<< i<<","<<j<<endl;
                    //use location to perform jumps and generate children
                    if (this->board_status.board[i][j].role == 'm') {
                        if(location.l1 != -2 && location.l2 != -2){
                            children[children_num] = new GameTree(p);
                            children[children_num]->board_status = this->board_status;
                            children[children_num]->board_status.move('A', this->board_status.board[i][j].id,location.l1, location.l2);
                            children[children_num]->row = location.l1;
                            children[children_num]->col = location.l2;
                            children[children_num]->id = this->board_status.board[i][j].id;
//                            cout<<"\nadd all children2, child info(num, id, row, col) : "<<children_num<<" -- "
//                            <<children[children_num]->id <<" %%  "<< children[children_num]->row << " %% "
//                            << children[children_num]->col<<endl;
                            children_num++;
                        }
                        if(location.l3 != -2 && location.l4 != -2){
                            children[children_num] = new GameTree(p);
                            children[children_num]->board_status = this->board_status;
                            children[children_num]->board_status.move('A', this->board_status.board[i][j].id,location.l3, location.l4);
                            children[children_num]->row = location.l3;
                            children[children_num]->col = location.l4;
                            children[children_num]->id = this->board_status.board[i][j].id;
//                            cout<<"\nadd all children2, child info(num, id, row, col) : "<<children_num<<" -- "
//                                <<children[children_num]->id <<" %%  "<< children[children_num]->row << " %% "
//                                << children[children_num]->col<<endl;
                            children_num++;
                        }

                    } else if (this->board_status.board[i][j].role == 'k') {
                        if(location.l1 != -2 && location.l2 != -2){
                            children[children_num] = new GameTree(p);
                            children[children_num]->board_status = this->board_status;
                            children[children_num]->board_status.move('A', this->board_status.board[i][j].id,location.l1, location.l2);
                            children[children_num]->row = location.l1;
                            children[children_num]->col = location.l2;
                            children[children_num]->id = this->board_status.board[i][j].id;
//                            cout<<"\nadd all children2, child info(num, id, row, col) : "<<children_num<<" -- "
//                                <<children[children_num]->id <<" %%  "<< children[children_num]->row << " %% "
//                                << children[children_num]->col<<endl;
                            children_num++;
                        }
                        if(location.l3 != -2 && location.l4 != -2){
                            children[children_num] = new GameTree(p);
                            children[children_num]->board_status = this->board_status;
                            children[children_num]->board_status.move('A', this->board_status.board[i][j].id,location.l3, location.l4);
                            children[children_num]->row = location.l3;
                            children[children_num]->col = location.l4;
                            children[children_num]->id = this->board_status.board[i][j].id;
//                            cout<<"\nadd all children2, child info(num, id, row, col) : "<<children_num<<" -- "
//                                <<children[children_num]->id <<" %%  "<< children[children_num]->row << " %% "
//                                << children[children_num]->col<<endl;
                            children_num++;
                        }
                        if(location.l5 != -2 && location.l6 != -2){
                            children[children_num] = new GameTree(p);
                            children[children_num]->board_status = this->board_status;
                            children[children_num]->board_status.move('A', this->board_status.board[i][j].id,location.l5, location.l6);
                            children[children_num]->row = location.l5;
                            children[children_num]->col = location.l6;
                            children[children_num]->id = this->board_status.board[i][j].id;
//                            cout<<"\nadd all children2, child info(num, id, row, col) : "<<children_num<<" -- "
//                                <<children[children_num]->id <<" %%  "<< children[children_num]->row << " %% "
//                                << children[children_num]->col<<endl;
                            children_num++;
                        }
                        if(location.l7 != -2 && location.l8 != -2){
                            children[children_num] = new GameTree(p);
                            children[children_num]->board_status = this->board_status;
                            children[children_num]->board_status.move('A', this->board_status.board[i][j].id,location.l7, location.l8);
                            children[children_num]->row = location.l7;
                            children[children_num]->col = location.l8;
                            children[children_num]->id = this->board_status.board[i][j].id;
//                            cout<<"\nadd all children2, child info(num, id, row, col) : "<<children_num<<" -- "
//                                <<children[children_num]->id <<" %%  "<< children[children_num]->row << " %% "
//                                << children[children_num]->col<<endl;
                            children_num++;
                        }
                    }else {}
                }
            }
            else if(player == 'B') {
                char p = 'A';
                location = jump(i, j, this->board_status, 'B');
                if (available_to_jump(location) == true) {
//                    cout<<"\nADD ALL CHILD2 --current ture situation-B : "<< i<<","<<j<<endl;
                    if (this->board_status.board[i][j].role == 'm') {
                        if (location.l1 != -2 && location.l2 != -2) {
                            children[children_num] = new GameTree(p);
                            children[children_num]->board_status = this->board_status;
                            children[children_num]->board_status.move('B', this->board_status.board[i][j].id,location.l1, location.l2);
                            children[children_num]->row = location.l1;
                            children[children_num]->col = location.l2;
                            children[children_num]->id = this->board_status.board[i][j].id;
//                            cout<<"\nadd all children2, child info(num, id, row, col) : "<<children_num<<" -- "
//                                <<children[children_num]->id <<" %%  "<< children[children_num]->row << " %% "
//                                << children[children_num]->col<<endl;
                            children_num++;
                        }
                        if (location.l3 != -2 && location.l4 != -2) {
                            children[children_num] = new GameTree(p);
                            children[children_num]->board_status = this->board_status;
                            children[children_num]->board_status.move('B', this->board_status.board[i][j].id,location.l3, location.l4);
                            children[children_num]->row = location.l3;
                            children[children_num]->col = location.l4;
                            children[children_num]->id = this->board_status.board[i][j].id;
//                            cout<<"\nadd all children2, child info(num, id, row, col) : "<<children_num<<" -- "
//                                <<children[children_num]->id <<" %%  "<< children[children_num]->row << " %% "
//                                << children[children_num]->col<<endl;
                            children_num++;
                        }
                    } else if (this->board_status.board[i][j].role == 'k') {
                        if (location.l1 != -2 && location.l2 != -2) {
                            children[children_num] = new GameTree(p);
                            children[children_num]->board_status = this->board_status;
                            children[children_num]->board_status.move('B', this->board_status.board[i][j].id,location.l1, location.l2);
                            children[children_num]->row = location.l1;
                            children[children_num]->col = location.l2;
                            children[children_num]->id = this->board_status.board[i][j].id;
                            children_num++;
                        }
                        if (location.l3 != -2 && location.l4 != -2) {
                            children[children_num] = new GameTree(p);
                            children[children_num]->board_status = this->board_status;
                            children[children_num]->board_status.move('B', this->board_status.board[i][j].id,location.l3, location.l4);
                            children[children_num]->row = location.l3;
                            children[children_num]->col = location.l4;
                            children[children_num]->id = this->board_status.board[i][j].id;
                            children_num++;
                        }
                        if (location.l5 != -2 && location.l6 != -2) {
                            children[children_num] = new GameTree(p);
                            children[children_num]->board_status = this->board_status;
                            children[children_num]->board_status.move('B', this->board_status.board[i][j].id,location.l5, location.l6);
                            children[children_num]->row = location.l5;
                            children[children_num]->col = location.l6;
                            children[children_num]->id = this->board_status.board[i][j].id;
                            children_num++;
                        }
                        if (location.l7 != -2 && location.l8 != -2) {
                            children[children_num] = new GameTree(p);
                            children[children_num]->board_status = this->board_status;
                            children[children_num]->board_status.move('B', this->board_status.board[i][j].id,location.l7, location.l8);
                            children[children_num]->row = location.l7;
                            children[children_num]->col = location.l8;
                            children[children_num]->id = this->board_status.board[i][j].id;
                            children_num++;
                        }
                    }
                    else{}
                }
            }else{}
        }
    }
}

int GameTree::getRow() const {
    return row;
}

int GameTree::getCol() const {
    return col;
}

int GameTree::getId() const {
    return id;
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
