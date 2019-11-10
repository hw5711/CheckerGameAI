
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
    row = -1;
    col = -1;
    for (int i = 0; i < 48; i++) { // each node can have at most 4 children(directions)
        children[i] = NULL;
    }
}

GameTree::GameTree(char p) {
    player = p;
//    board_status.board.heuristic_value = -1000;
    number_of_children = 0;
    row = -1;
    col = -1;
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
int * GameTree::jump(int i, int j, Checker checker, char player){
//    cout << "\ntest 5 jump :"<< i << ","<<j<<"role: "<<checker.board[i][j].role<<endl;
    int arr[8]={-2,-2,-2,-2,-2,-2,-2,-2};
    char p = (player == 'A')? 'B' : 'A';
    if(checker.board[i][j].role == 'm' && checker.board[i][j].player == player){
//        arr[4]={-1,-1,-1,-1};
        if(i+1<=7 && j-1>=0){ //check down left first
            if(checker.board[i+1][j-1].player == ' '){
                arr[0] = i+1;
                arr[1] = j-1;
//                cout<<"fit condition " << i+1 << " % " << j-1 << endl;
            }
            else if(checker.board[i+1][j-1].player == p){//check down right first
                if(i+2<=7 && j-2>=0 && checker.board[i+2][j-2].player == ' '){
                    arr[0] = i+2;
                    arr[1] = j-2;
//                    cout<<"fit condition " << i+2 << " % " << j-2 << endl;
                }
            }else{}
        }

        if(i+1<=7 && j+1<=7){ //check down right first
            if(checker.board[i+1][j+1].player == ' '){
                arr[2] = i+1;
                arr[3] = j+1;
//                cout<<"fit condition " << i+1 << " % " << j+1 << endl;
            }
            else if(checker.board[i+1][j+1].player == p){//check down right first
                if(i+2<=7 && j+2<=7 && checker.board[i+2][j+2].player == ' '){
                    arr[2] = i+2;
                    arr[3] = j+2;
//                    cout<<"fit condition " << i+2 << " % " << j+2 << endl;
                }
            }else{}
        }
    }else if(checker.board[i][j].role == 'k' && checker.board[i][j].player == player){
       // int arr[8]={-1,-1,-1,-1,-1,-1,-1,-1};

        if(i+1<=7 && j-1>=0){ //check down left first
            if(checker.board[i+1][j-1].player == ' '){
                arr[0] = i+1;
                arr[1] = j-1;
//                cout<<"fit condition " << i+1 << " % " << j-1 << endl;
            }
            else if(checker.board[i+1][j-1].player == p){//check down right first
                if(i+2<=7 && j-2>=0 && checker.board[i+2][j-2].player == ' '){
                    arr[0] = i+2;
                    arr[1] = j-2;
//                    cout<<"fit condition " << i+2 << " % " << j-2 << endl;
                }
            }else{}
        }

        if(i+1<=7 && j+1<=7){ //check down right first
            if(checker.board[i+1][j+1].player == ' '){
                arr[2] = i+1;
                arr[3] = j+1;
//                cout<<"fit condition " << i+1 << " % " << j+1 << endl;
            }
            else if(checker.board[i+1][j+1].player == p){//check down right first
                if(i+2<=7 && j+2<=7 && checker.board[i+2][j+2].player == ' '){
                    arr[2] = i+2;
                    arr[3] = j+2;
//                    cout<<"fit condition " << i+2 << " % " << j+2 << endl;
                }
            }else{}
        }

        if(i-1>=0 && j-1>=0){ //check up left first
            if(checker.board[i-1][j-1].player == ' '){
                arr[4] = i-1;
                arr[5] = j-1;
//                cout<<"fit condition " << i-1 << " % " << j-1 << endl;
            }
            else if(checker.board[i-1][j-1].player == p){//check down right first
                if(i-2>=0 && j-2>=0 && checker.board[i-2][j-2].player == ' '){
                    arr[4] = i-2;
                    arr[5] = j-2;
//                    cout<<"fit condition " << i-2 << " % " << j-2 << endl;
                }
            }else{}
        }

        if(i-1>=0 && j+1<=7){ //check up right first
            if(checker.board[i-1][j+1].player == ' '){
                arr[6] = i-1;
                arr[7] = j+1;
//                cout<<"fit condition " << i-1 << " % " << j+1 << endl;
            }
            else if(checker.board[i-1][j+1].player == p){//check down right first
                if(i-2>=0 && j+2<=7 && checker.board[i-2][j+2].player == ' '){
                    arr[6] = i-2;
                    arr[7] = j+2;
//                    cout<<"fit condition " << i-2 << " % " << j+2 << endl;
                }
            }else{}
        }
    }else if(checker.board[i][j].role == 'n' && checker.board[i][j].player == player){}
    else{}
//    cout<<"\ntest9---jump: "<< arr[0]<<"--/"<<arr[1]<<"--/" <<arr[2]
//        <<"--/"<<arr[3]<<"--/" <<arr[4]<<"--/"<<arr[5]<<"--/" <<arr[6]<<"--/"<<arr[7];
    return arr;
    }


//find a right position, store it into the children array and move
void GameTree::add_all_children() {
    //go through the every potential locations of enemy and store it to created children array
    //if it's available, add it into the child list
    int *location = NULL; //stores 8 places of available jumps
    cout << "test 4--- add all children \n";
    int children_num = 0;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(this->board_status.board[i][j].player == 'A'){
                char p = (player == 'A') ? 'B' : 'A';
                location = jump(i,j,this->board_status,'A');
//                cout<<"\ntest10---add-all-children: "<< location[0]<<"--/"<<location[1]<<"--/" <<location[2]
//                    <<"--/"<<location[3]<<"--/" <<location[4]<<"--/"<<location[5]<<"--/" <<location[6]<<"--/"<<location[7];
                if(available_to_jump(location) == true){
                    continue;
                }
                cout<<"\ntest11--add all children(number): "<< children_num<<endl;
                //use location to perform jumps and generate children
                if(this->board_status.board[i][j].role == 'm'){
                    for(int k=0; k<4; k+=2){
                        if(*(location+k)!= -1){
                            children[children_num] = new GameTree(p);
                            children[children_num]->board_status = this->board_status;
                            children[children_num]->board_status.move(i,j, *(location+k), *(location+k+1),'A');
                            children_num++;
                        }
                    }
                }
                else if(this->board_status.board[i][j].role == 'k'){
                    for(int k=0; k<8; k+=2){
                        if(*(location+k)!= -1){
                            children[children_num] = new GameTree(p);
                            children[children_num]->board_status = this->board_status;
                            children[children_num]->board_status.move(i, j,*(location+k), *(location+k+1),'A');
                            children_num++;
                        }
                    }
                }
            }
            else{
                char p = (player == 'A') ? 'B' : 'A';
                location = jump(i,j,this->board_status,'B');
                if(this->board_status.board[i][j].role == 'm'){
                    for(int k=0; k<4; k+=2){
                        if(*(location+k)!= -1){
                            children[children_num] = new GameTree(p);
                            children[children_num]->board_status = this->board_status;
                            children[children_num]->board_status.move(i, j, *(location+k), *(location+k+1),'B');
                            children_num++;
                        }
                    }
                }
                else if(this->board_status.board[i][j].role == 'k'){
                    for(int k=0; k<8; k+=2){
                        if(*(location+k)!= -1){
                            children[children_num] = new GameTree(p);
                            children[children_num]->board_status = this->board_status;
                            children[children_num]->board_status.move(i, j, *(location+k), *(location+k+1),'B');
                            children_num++;
                        }
                    }
                }
            }
        }
    }

}

bool GameTree::deepenough(int depth) {
//    if (this->board_status.get_heuristic_value_board() != -1000)
//        return board_status.get_heuristic_value_board();
    //if the depth is greater than 3 or a player has won the game then it is deep enough.
    cout<<"\ntest 8---deepenough: "<< this->board_status.checkWin()<<endl;
    if (depth >= 2 || this->board_status.checkWin() != 'N'){
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

/////////////////////////////////////
///       BURAK'S EVALUATION      ///
/////////////////////////////////////

int GameTree::evaluation() { //
    int value;
    if (player == 'A') {
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
        //check side
        for (int i = 4; i < 8; i++) {
            for (int j = 4; j < 8; j++) {
                if (board_status.board[i][j].player == 'A') {
                    value += 4;
                }
            }
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (board_status.board[i][j].player == 'B') {
                    value -= 4;
                }
            }
        }

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

    } else if (player == 'B') {
        //check piece
        for (int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                if(board_status.board[i][j].role == 'm' && board_status.board[i][j].player == 'B'){
                    value +=10;
                }else if (board_status.board[i][j].role == 'k' && board_status.board[i][j].player == 'B'){
                    value +=20;
                }else if (board_status.board[i][j].role == 'm' && board_status.board[i][j].player == 'A'){
                    value -=10;
                }else if (board_status.board[i][j].role == 'k' && board_status.board[i][j].player == 'A'){
                    value -=20;
                }else{}
            }
        }
        //check side
        for (int i = 4; i < 8; i++) {
            for (int j = 4; j < 8; j++) {
                if (board_status.board[i][j].player == 'B') {
                    value += 4;
                }
            }
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (board_status.board[i][j].player == 'A') {
                    value -= 4;
                }
            }
        }

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

int * GameTree::getChildLocation(Checker child){
    int *ptr = NULL;
    //Checker cur_board = this->board_status;
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if(this->board_status.board[i][j].id != child.board[i][j].id && this->board_status.board[i][j].player != ' '){
                *(ptr) = i;
                *(ptr+1) = j;
            }
            else if(this->board_status.board[i][j].id != child.board[i][j].id && child.board[i][j].player != ' '){
                *(ptr+2) = i;
                *(ptr+3) = j;
            }else{}
        }
    }
    return ptr; //store location before and after move of each child
}

bool GameTree::available_to_jump(int *arr){

    for(int count=0; count<8; count++){
        if(arr[count] != -2){
            return true;
        }
    }
    return false;
}