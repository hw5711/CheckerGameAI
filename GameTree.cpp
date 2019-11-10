
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
//    board_status.board.heuristic_value = -1000;
    this->number_of_children = 0;
    this->row = -1;
    this->col = -1;
    for (int i = 0; i < 48; i++) { // go through all board
        children[i] = NULL;
    }
}

void GameTree::create_node(char p) {
    children[number_of_children++] = new GameTree(p);
}

void GameTree::set_heuristic_value(int value, int r, int c) {
    this->board_status.heuristic_value = value;
    this->row = r;
    this->col = c;
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
                if (checker.board[i + 1][j - 1].player == ' ') {
                    location.l1 = i + 1;
                    location.l2 = j - 1;
//                    cout << "fit function: " << i + 1 << "%" << j - 1 << endl;
                } else if (checker.board[i + 1][j - 1].player == p) {//check down right first
                    if (i + 2 <= 7 && j - 2 >= 0 && checker.board[i + 2][j - 2].player == ' ') {
                        location.l1 = i + 2;
                        location.l2 = j - 2;
//                        cout << "fit function: " << i + 2 << "%" << j - 2 << endl;
                    }
                } else {}
            }

            if (i + 1 <= 7 && j + 1 <= 7) { //check down right first
                if (checker.board[i + 1][j + 1].player == ' ') {
                    location.l3 = i + 1;
                    location.l4 = j + 1;
//                    cout << "fit function: " << i + 1 << "%" << j + 1 << endl;
                } else if (checker.board[i + 1][j + 1].player == p) {//check down right first
                    if (i + 2 <= 7 && j + 2 <= 7 && checker.board[i + 2][j + 2].player == ' ') {
                        location.l3 = i + 2;
                        location.l4 = j + 2;
//                        cout << "fit function: " << i + 2 << "%" << j + 2 << endl;
                    }
                } else {}
            }
        } else if (checker.board[i][j].role == 'k' && checker.board[i][j].player == player) {
            // int arr[8]={-1,-1,-1,-1,-1,-1,-1,-1};

            if (i + 1 <= 7 && j - 1 >= 0) { //check down left first
                if (checker.board[i + 1][j - 1].player == ' ') {
                    location.l1 = i + 1;
                    location.l2 = j - 1;
//                    cout << "fit function: " << i + 1 << "%" << j - 1 << endl;
                } else if (checker.board[i + 1][j - 1].player == p) {//check down right first
                    if (i + 2 <= 7 && j - 2 >= 0 && checker.board[i + 2][j - 2].player == ' ') {
                        location.l1 = i + 2;
                        location.l2 = j - 2;
//                        cout << "fit function: " << i + 2 << "%" << j - 2 << endl;
                    }
                } else {}
            }

            if (i + 1 <= 7 && j + 1 <= 7) { //check down right first
                if (checker.board[i + 1][j + 1].player == ' ') {
                    location.l3 = i + 1;
                    location.l4 = j + 1;
//                    cout << "fit function: " << i + 1 << "%" << j + 1 << endl;
                } else if (checker.board[i + 1][j + 1].player == p) {//check down right first
                    if (i + 2 <= 7 && j + 2 <= 7 && checker.board[i + 2][j + 2].player == ' ') {
                        location.l3 = i + 2;
                        location.l4 = j + 2;
//                        cout << "fit function: " << i + 2 << "%" << j + 2 << endl;
                    }
                } else {}
            }

            if (i - 1 >= 0 && j - 1 >= 0) { //check up left first
                if (checker.board[i - 1][j - 1].player == ' ') {
                    location.l5 = i - 1;
                    location.l6 = j - 1;
//                    cout << "fit function: " << i - 1 << "%" << j - 1 << endl;
                } else if (checker.board[i - 1][j - 1].player == p) {//check down right first
                    if (i - 2 >= 0 && j - 2 >= 0 && checker.board[i - 2][j - 2].player == ' ') {
                        location.l5 = i - 2;
                        location.l6 = j - 2;
//                        cout << "fit function: " << i - 2 << "%" << j - 2 << endl;
                    }
                } else {}
            }

            if (i - 1 >= 0 && j + 1 <= 7) { //check up right first
                if (checker.board[i - 1][j + 1].player == ' ') {
                    location.l7 = i - 1;
                    location.l8 = j + 1;
//                    cout << "fit function: " << i - 1 << "%" << j + 1 << endl;
                } else if (checker.board[i - 1][j + 1].player == p) {//check down right first
                    if (i - 2 >= 0 && j + 2 <= 7 && checker.board[i - 2][j + 2].player == ' ') {
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
                if (checker.board[i - 1][j - 1].player == ' ') {
                    location.l1 = i - 1;
                    location.l2 = j - 1;
//                    cout << "fit function: " << i - 1 << "%" << j - 1 << endl;
                } else if (checker.board[i - 1][j - 1].player == p) {//check down right first
                    if (i - 2 >= 0 && j - 2 >= 0 && checker.board[i - 2][j - 2].player == ' ') {
                        location.l1 = i - 2;
                        location.l2 = j - 2;
//                        cout << "fit function: " << i - 2 << "%" << j - 2 << endl;
                    }
                } else {}
            }

            if (i - 1 >= 0 && j + 1 <= 7) { //check up right first
                if (checker.board[i - 1][j + 1].player == ' ') {
                    location.l3 = i - 1;
                    location.l4 = j + 1;
//                    cout << "fit function: " << i - 1 << "%" << j + 1 << endl;
                } else if (checker.board[i - 1][j + 1].player == p) {//check down right first
                    if (i - 2 >= 0 && j + 2 <= 7 && checker.board[i - 2][j + 2].player == ' ') {
                        location.l3 = i - 2;
                        location.l4 = j + 2;
//                        cout << "fit function: " << i - 2 << "%" << j + 2 << endl;
                    }
                } else {}
            }
        } else if (checker.board[i][j].role == 'k' && checker.board[i][j].player == player) {
            if (i - 1 >= 0 && j - 1 >= 0) { //check up left first
                if (checker.board[i - 1][j - 1].player == ' ') {
                    location.l1 = i - 1;
                    location.l2 = j - 1;
//                    cout << "fit function: " << i - 1 << "%" << j - 1 << endl;
                } else if (checker.board[i - 1][j - 1].player == p) {//check down right first
                    if (i - 2 >= 0 && j - 2 >= 0 && checker.board[i - 2][j - 2].player == ' ') {
                        location.l1 = i - 2;
                        location.l2 = j - 2;
//                        cout << "fit function: " << i - 2 << "%" << j - 2 << endl;
                    }
                } else {}
            }

            if (i - 1 >= 0 && j + 1 <= 7) { //check up right first
                if (checker.board[i - 1][j + 1].player == ' ') {
                    location.l3 = i - 1;
                    location.l4 = j + 1;
//                    cout << "fit function: " << i - 1 << "%" << j + 1 << endl;
                } else if (checker.board[i - 1][j + 1].player == p) {//check down right first
                    if (i - 2 >= 0 && j + 2 <= 7 && checker.board[i - 2][j + 2].player == ' ') {
                        location.l3 = i - 2;
                        location.l4 = j + 2;
//                        cout << "fit function: " << i - 2 << "%" << j + 2 << endl;
                    }
                } else {}
            }

            if (i + 1 <= 7 && j - 1 >= 0) { //check down left first
                if (checker.board[i + 1][j - 1].player == ' ') {
                    location.l5 = i + 1;
                    location.l6 = j - 1;
//                    cout << "fit function: " << i + 1 << "%" << j - 1 << endl;
                } else if (checker.board[i + 1][j - 1].player == p) {//check down right first
                    if (i + 2 <= 7 && j - 2 >= 0 && checker.board[i + 2][j - 2].player == ' ') {
                        location.l5 = i + 2;
                        location.l6 = j - 2;
//                        cout << "fit function: " << i + 2 << "%" << j - 2 << endl;
                    }
                } else {}
            }

            if (i + 1 <= 7 && j + 1 <= 7) { //check up right first
                if (checker.board[i + 1][j + 1].player == ' ') {
                    location.l7 = i + 1;
                    location.l8 = j + 1;
//                    cout << "fit function: " << i + 1 << "%" << j + 1 << endl;
                } else if (checker.board[i + 1][j + 1].player == p) {//check down right first
                    if (i + 2 <= 7 && j + 2 <= 7 && checker.board[i + 2][j + 2].player == ' ') {
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
   // cout<<"\ntest add all children1: " << player << endl;
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
                            children[children_num]->board_status.move(i, j, location.l1, location.l2,'A');
                            children_num++;
                        }
                        if(location.l3 != -2 && location.l4 != -2){
                            children[children_num] = new GameTree(p);
                            children[children_num]->board_status = this->board_status;
                            children[children_num]->board_status.move(i, j, location.l3, location.l4,'A');
                            children_num++;
                        }

                    } else if (this->board_status.board[i][j].role == 'k') {
                        if(location.l1 != -2 && location.l2 != -2){
                            children[children_num] = new GameTree(p);
                            children[children_num]->board_status = this->board_status;
                            children[children_num]->board_status.move(i, j, location.l1, location.l2,'A');
                            children_num++;
                        }
                        if(location.l3 != -2 && location.l4 != -2){
                            children[children_num] = new GameTree(p);
                            children[children_num]->board_status = this->board_status;
                            children[children_num]->board_status.move(i, j, location.l3, location.l4,'A');
                            children_num++;
                        }
                        if(location.l5 != -2 && location.l6 != -2){
                            children[children_num] = new GameTree(p);
                            children[children_num]->board_status = this->board_status;
                            children[children_num]->board_status.move(i, j, location.l5, location.l6,'A');
                            children_num++;
                        }
                        if(location.l7 != -2 && location.l8 != -2){
                            children[children_num] = new GameTree(p);
                            children[children_num]->board_status = this->board_status;
                            children[children_num]->board_status.move(i, j, location.l7, location.l8,'A');
                            children_num++;
                        }
                    }else {}
                }
            }
            else if(player == 'B') {
                char p = 'A';
                location = jump(i, j, this->board_status, 'B');
//                cout << "\ntest add all children 2: \n";
//                this->board_status.displayBoard();
//                cout << endl;
                if (available_to_jump(location) == true) {
//                    cout<<"\ncurrent ture situation-B : "<< i<<","<<j<<endl;
                    if (this->board_status.board[i][j].role == 'm') {
                            if (location.l1 != -2 && location.l2 != -2) {
                                children[children_num] = new GameTree(p);
                                children[children_num]->board_status = this->board_status;
                                children[children_num]->board_status.move(i, j, location.l1, location.l2, 'B');
                                children_num++;
                            }
                            if (location.l3 != -2 && location.l4 != -2) {
                                children[children_num] = new GameTree(p);
                                children[children_num]->board_status = this->board_status;
                                children[children_num]->board_status.move(i, j, location.l3, location.l4, 'B');
                                children_num++;
                            }
                        } else if (this->board_status.board[i][j].role == 'k') {
                            if (location.l1 != -2 && location.l2 != -2) {
                                children[children_num] = new GameTree(p);
                                children[children_num]->board_status = this->board_status;
                                children[children_num]->board_status.move(i, j, location.l1, location.l2, 'B');
                                children_num++;
                            }
                            if (location.l3 != -2 && location.l4 != -2) {
                                children[children_num] = new GameTree(p);
                                children[children_num]->board_status = this->board_status;
                                children[children_num]->board_status.move(i, j, location.l3, location.l4, 'B');
                                children_num++;
                            }
                            if (location.l5 != -2 && location.l6 != -2) {
                                children[children_num] = new GameTree(p);
                                children[children_num]->board_status = this->board_status;
                                children[children_num]->board_status.move(i, j, location.l5, location.l6, 'B');
                                children_num++;
                            }
                            if (location.l7 != -2 && location.l8 != -2) {
                                children[children_num] = new GameTree(p);
                                children[children_num]->board_status = this->board_status;
                                children[children_num]->board_status.move(i, j, location.l7, location.l8, 'B');
                                children_num++;
                            }
                        }
                        else{}
                    }
                }else{}
            }
        }
   // cout << "\ntest11--add all children(number): " << children_num << endl;
    }

bool GameTree::deepenough(int depth, char player) {
//    if (this->board_status.get_heuristic_value_board() != -1000)
//        return board_status.get_heuristic_value_board();
    //if the depth is greater than 3 or a player has won the game then it is deep enough.
   // cout<<"\ntest 8---deepenough: "<< this->board_status.checkWin()<<endl;
    if (depth >= 3 || this->board_status.checkWin() != 'N'){
        return true;
    } else {
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

int GameTree::evaluation( char player) {
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
        for (int i = 4; i < 8; i++) {
            for (int j = 4; j < 8; j++) {
                if (board_status.board[i][j].player == 'A') {
                    value += 4;
                }
            }
        }
//        cout<<"\ntest--evaluation2: "<< value<<endl;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (board_status.board[i][j].player == 'B') {
                    value -= 4;
                }
            }
        }
//        cout<<"\ntest--evaluation3: "<< value<<endl;
        //threatened
        for (int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                if(threaten(i,j, board_status,'A')){
                    value +=10;
                }else if(threaten(i,j, board_status,'B')){
                    value -=10;
                }else{}
            }
        }
//        cout<<"\ntest--evaluation4: "<< value<<endl;

    } else if (player == 'B') {
//        cout<<"test -- evaluationB : "<<endl;
        //check piece
        for (int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                if(board_status.board[i][j].role == 'm' && board_status.board[i][j].player == 'B'){
                    value +=1;
                }else if (board_status.board[i][j].role == 'k' && board_status.board[i][j].player == 'B'){
                    value +=4;
                }else if (board_status.board[i][j].role == 'm' && board_status.board[i][j].player == 'A'){
                    value -=1;
                }else if (board_status.board[i][j].role == 'k' && board_status.board[i][j].player == 'A'){
                    value -=4;
                }else{}
            }
        }
//        cout<<"\ntest--evaluation1: "<< value<<endl;
        //check side
        for (int i = 4; i < 8; i++) {
            for (int j = 4; j < 8; j++) {
                if (board_status.board[i][j].player == 'B') {
                    value += 4;
                }
            }
        }
//        cout<<"\ntest--evaluation2: "<< value<<endl;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (board_status.board[i][j].player == 'A') {
                    value -= 4;
                }
            }
        }
//        cout<<"\ntest--evaluation3: "<< value<<endl;
        //threatened
        for (int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                if(threaten(i,j, board_status,'B')){
                    value +=10;
                }else if(threaten(i,j, board_status,'A')){
                    value -=10;
                }else{}
            }
        }
//        cout<<"\ntest--evaluation4: "<< value<<endl;
    }

    //set_heuristic_value(value);
    return value;
}

void GameTree::copyBoardStatus(Checker kb) {
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            this->board_status.board[i][j] = kb.board[i][j];
            this->board_status.heuristic_value = kb.heuristic_value;
        }
    }
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

void GameTree::getChildLocation(Checker child){
    Add address;
    //Checker cur_board = this->board_status;
//    cout<<'\n get Child location1(child board) \n';
//    child.displayBoard();
//    cout<<'\n get Child location1(father board) \n';
//    this->board_status.displayBoard();
//    cout << endl;
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if(this->board_status.board[i][j].id != child.board[i][j].id && this->board_status.board[i][j].player != ' '){
                address.row_before= i;
                address.col_before = j;
            }
           if(this->board_status.board[i][j].id != child.board[i][j].id && child.board[i][j].player != ' '){
               address.row_after = i;
               address.col_after = j;
            }
        }
    }
    this->address = address; //store location before and after move of each child
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

int GameTree::getBeforeRow(){
    return this->address.row_before;
}

int GameTree::getBeforeCol(){
    return this->address.col_before;
}
int GameTree::getAfterRow(){
    return this->address.row_after;
}
int GameTree::getAfterCol(){
    return this->address.col_after;
}