
#include "GameTree.h"
#include <cstdlib>
#include <ctime>

using namespace std;
//extern int  ALGO_FLAG;

extern int nodes_generated, nodes_expanded;

GameTree::GameTree() {
//    board_status.board.heuristic_value = -1000;
    player = 'n';
    number_of_children = 0;
    for (int i = 0; i < 4; i++) { // each node can have at most 4 children(directions)
        children[i] = NULL;
    }
}

GameTree::GameTree(char p) {
    player = p;
//    board_status.board.heuristic_value = -1000;
    number_of_children = 0;
    for (int i = 0; i < 4; i++) { // go through all board
        children[i] = NULL;
    }
}

void GameTree::create_node(char p) {
    children[number_of_children++] = new GameTree(p);
}

void GameTree::set_heuristic_value(int value) {
    board_status.set_heuristic_value_board(value);
}

//test if jump available
bool GameTree::jump_available(int i, int j, Checker board, char player){

}

//test if can jump more than once and return the new location
int * GameTree::jump_further(int i, int j, Checker board){
    int layer = 1;


}


//find a right position, store it into the children array and move
void GameTree::add_all_children() {
    char p = (player == 'A') ? 'B' : 'A';
    //go through the every potential locations of enemy and store it to created children array
    //if it's available, add it into the child list
    int children_num = 0;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){

            if(this->board_status.board[i][j].player == 'A' && player == 'A')
                if(this->board_status.board[i][j].role == 'm'){
                    int location[2];
                    int *ptr = NULL;
//                    ptr = location;
                    ptr = jump_further(i,j, this->board_status);


//                    if(i+1<=7 && j-1>=0 && j+1<=7){
//                        if(this->board_status.board[i+1][j-1].player == ' '){
//                            children[children_num]=new GameTree(p);
//                            children[children_num]->board_status = this->board_status;
//                            //children[children_num]->board_status.move(i,j);
//                        }else if(this->board_status.board[i+1][j-1].player == 'B'){ // if the available place is enemy
//                            int temp = 2;
//                            while(i+temp<=7 && j-temp<=7){
//                                if( this->board_status.board[i+1][j-1].player == ' '){
//                                    temp++;
//                                }else break;
//
//                            }
//                            children[children_num]=new GameTree(p);
//                            children[children_num]->board_status = this->board_status;
//                            //children[children_num]->board_status.move(i+temp,j-temp);
//                        }else break; //??? continue
//                        if(this->board_status.board[i+1][j+1].player == ' '){
//                            children[children_num++]=new GameTree(p);
//                            children[children_num++]->board_status = this->board_status;
//                        }
//                    }
                }
                else if(this->board_status.board[i][j].role == 'k'){
                    if(i-1>=0 && i+1<=7 && j-1>=0 && j+1<=7){

                    }
                }

        }
    }

//    for (int i = 0; i < 6; i++) {
//        number_of_children++;
//        children[i] = new GameTree(p);
//        if (this->board_status.A[i] != 0 && player == 'A')
//            children[i]->board_status = this->board_status;
//        else if (this->board_status.B[i] != 0 && player == 'B')
//            children[i]->board_status = this->board_status;
//        else
//            children[i] = NULL;
//        if (children[i] != NULL) {
//            nodes_generated++;
//            children[i]->board_status.move(i, children[i]->player);
//        }
//    }
}

bool GameTree::deepenough(int depth) {
    if (board_status.get_heuristic_value_board() != -1000)
        return board_status.get_heuristic_value_board();
    //if the depth is greater than 3 or a player has won the game then it is deep enough.
    if (depth >= 3 || board_status.checkWin() != 'N'){
        return true;
    } else {
        nodes_expanded++;
        add_all_children();
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

int GameTree::get_hole_number() {
    for (int i = 0; i < 6; i++) {
        if (children[i] == NULL)
            continue;
        if (children[i]->board_status.get_heuristic_value_board() == board_status.get_heuristic_value_board()) {
            cout << "hole #" << i;
            return i;
        }
    }
    return -1;
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
// }

/////////////////////////////////////
///       BURAK'S EVALUATION      ///
/////////////////////////////////////

int GameTree::evaluation() { //
    int value;
    if (player == 'A') {
        for (int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                if(board_status.board.role ==)
            }
            }


    } else if (player == 'B') {
        int b_rocks = 0;
        for (int i = 0; i < 6; i++) {
            if (board_status.A[i] == 0) {
                b_rocks++;
            } else if (board_status.A[i] > 0 && board_status.A[i] < 3) {
                value = 100;
            } else if (board_status.A[i] >= 3 && board_status.A[i] < 5) {
                value = 950;
            } else {
                value = 0;
            }
        }
    }
    set_heuristic_value(value);
    return value;
}

void GameTree::copyBoardStatus(Checker kb) {

}
