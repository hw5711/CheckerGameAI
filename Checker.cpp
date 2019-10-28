
#include "Checker.h"
#include <iostream>
#include <iomanip>
#include<ctime>
#include<cstdlib>


using namespace std;

//initializing the board
Checker::Checker() {
    for (int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            A[i][j] = 0;
            B[i][j] = 0;
        }
    }
    numberOfSlots = 5;
//    checker_A = 0, checker_B = 0; // stores stones of each player
    //int (*ptr)[8][8];
    winDecider = 36;
}

//constructor to set the board values, mainly used for testing
//Checker::Checker(int arr1[][8], int arr2[][8], int a, int b) {
//    for (int i = 0; i < 8; i++) {
//        for(int j = 0; j < 8; j++) {
//            A[i][j] = arr1[i][j];
//            B[i][j] = arr2[i][j];
//        }
//    }
//    checker_A = a;
//    checker_B = b;
//}

//copy constructor to copy the value of the board from one var to another
Checker::Checker(Checker *b) {
    for (int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            this->A[i][j] = b->A[i][j];
            this->B[i][j] = b->B[i][j];
        }
    }

}

//Function to move for the A player
char Checker::move_A(int hole_number_r, int hole_number_c) {
    int tempPos_r = hole_number_r;
    int tempPos_c = hole_number_c;

    for (int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            ptr[i][j] = A[i][j];//ptr[]
        }
    }
    int numberOfStones = ptr[tempPos_r][tempPos_c];
    ptr[tempPos_r][tempPos_c] = 0;
    int opponentPos, opponentStones;


    return 'B';
}

//Function to move for the B player
char Checker::move_B(int hole_number_r, int hole_number_c) {
    int tempPos = hole_number;
    ptr = B;
    int numberOfStones = ptr[tempPos];
    ptr[hole_number] = 0;
    int opponentPos, opponentStones;

    tempPos++;
    while (numberOfStones > 0) {
        if (tempPos >= 0 && tempPos <= 5) {
            if (numberOfStones == 1) {
                numberOfStones--;
                opponentPos = numberOfSlots - tempPos;
                if (ptr[tempPos] == 0) {
                    ptr = A;
                    opponentStones = ptr[opponentPos];
                    ptr[opponentPos] = 0;
                    checker_B += opponentStones + 1;
                    if (numberOfStones == 0)
                        return 'A';
                } else {
                    ptr[tempPos] += 1;
                    if (numberOfStones == 0)
                        return 'A';
                }
            } else if (numberOfStones > 1) {
                numberOfStones--;
                ptr[tempPos] += 1;
            }
        } else if (tempPos == 6 && numberOfStones >= 1) {
            numberOfStones--;
            checker_B += 1;
            if (numberOfStones == 0)
                return 'B';
        } else if (tempPos > 6 && tempPos <= 12) {
            ptr = A;
            numberOfStones--;
            ptr[tempPos - 7] += 1;
            if (numberOfStones == 0)
                return 'A';
        } else if (tempPos >= 12) {
            tempPos = -1;
            ptr = B;
        }
        tempPos++;
    }
    return 'A';
}

//Function which decides as to who should move
char Checker::move(int hole_number_r, int hole_number_c, char player) {
    char v;
    if (player == 'A')
        v = move_A(hole_number_r, hole_number_c);
    else
        v = move_B((hole_number_r, hole_number_c);
    return v;
}

//Function to decide as to which player wins
char Checker::checkWin() {
    int a0 = 0, b0 = 0, a_stones = 0, b_stones = 0;
    for (int i = 0; i < 6; i++) {
        if (A[i] == 0) {
            a0++;
        }
        if (B[i] == 0) {
            b0++;
        }
        a_stones += A[i];
        b_stones += B[i];

    }
    if (a0 == 6) {
        checker_B += b_stones;
        for (int i = 0; i < 6; i++) {
            B[i] = 0;
        }
        cout << "A has no stones left to play" << endl;
    }
    if (b0 == 6) {
        checker_A += a_stones;
        for (int i = 0; i < 6; i++) {
            A[i] = 0;
        }
        cout << "B has no stones left to play" << endl;
    }
    if (checker_A > winDecider)//A wins
    {
        return 'A';   // A wins
    } else if (checker_B > winDecider)//B Wins
    {
        return 'B';  // B wins
    } else if (a0 == 6 || b0 == 6) {
        return 'T'; // indicates that a tie occurred
    } else//No win
    {
        return 'N';
    }
}

//
void Checker::operator=(Checker kb) {
    for (int i = 0; i < 6; i++) {
        A[i] = kb.A[i];
        B[i] = kb.B[i];

    }
    numberOfSlots = 5;
    checker_A = kb.checker_A;
    checker_B = kb.checker_B;
    ptr = NULL;
    winDecider = 36;
}

//Function to display the board
void Checker::displayBoard() {
    cout << endl;
    cout << "\t\t\tA PLAYER";
    cout << endl;
    // First Line
    cout << "\t\t";
    for (int i = 0; i < 25; i++) {
        cout << "-";
    }
    //Second Line
    cout << endl;
    cout << "\t\t" << "|";
    cout << setw(2);

    for (int i = 5; i >= 0; i--) {
        cout << A[i] << setw(2) << "|";
        cout << " ";
    }
    cout << endl;
    cout << endl;
    cout << " |" << setw(3) << checker_A << " |"; // Fourth Line
    cout << "\t\t\t\t\t\t\t   |" << setw(3) << checker_B << " |"; // Fourth Line
    cout << endl;
    // Fifth Line
    cout << "\t\t";
    for (int i = 0; i < 25; i++) {
        cout << "-";
    }
    cout << endl;
    //Sixth Line
    cout << "\t\t" << "|";
    cout << setw(2);

    for (int i = 0; i < 6; i++) {
        cout << B[i] << setw(2) << "|";
        cout << " ";
    }
    cout << endl;
    cout << "\t\t\tB PLAYER";
    cout << endl << endl << endl << endl;
}

bool Checker::checkLegealMove(char player, int hole) {
    if (hole > 5 || hole < 0)
        return false;
    if (player == 'A' && A[hole] == 0) {
        return false;
    } else if (player == 'B' && B[hole] == 0) {
        return false;
    }
    return true;
}
