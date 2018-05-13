#include "sudoku.h"

#include <QPoint>  //x,y,operator
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


Sudoku::Sudoku() {
    srand((unsigned)time(NULL));
}

Sudoku::~Sudoku() {
}

void Sudoku::genRandom(int line[]) {
    for (int i = 0; i < 9; ++i) {
        line[i] = i + 1;
    }
    for (int i = 0; i < 9; ++i) {
        int pos = rand() % (9 - i); // exchange with 9 - i number
        if (pos == 8 - i) {
            continue;
        } else {
            int temp = line[pos];
            line[pos] = line[8 - i];
            line[8 - i] = temp;
        }
    }

}

//try to fill k, success then return true
bool Sudoku::tryfill(int i, int j, int k) {
    if (_table[i][j] != 0) {
        return false;
    }

    //check column
    for (int row = 0; row < 9; ++row) {
        if (_table[row][j] == k) {
            return false;
        }
    }

    //check row
    for (int col = 0; col < 9; ++col) {
        if (_table[i][col] == k) {
            return false;
        }
    }

    //check 3*3
    int up1 = (i / 3) * 3 + 3 ; // up i in 3*3
    int up2 = (j / 3) * 3 + 3;   // up j in 3*3
    for (int p = up1 - 3; p < up1; ++p) {
        for (int q = up2 - 3; q < up2; ++q) {
            if (_table[p][q] == k) {
                return false;
            }
        }
    }

    _table[i][j] = k;
    return true;
}

//(8, 8)go to(9, 9); (0, 0)back to(8, 8）
void Sudoku::next(int &x, int &y) {
    ++y;
    x += (y / 9);
    if (x < 9) {
        y %= 9;
    }
}

//(8, 8)go to(9, 9); (0, 0)back to(8, 8）
void Sudoku::previous(int &x, int &y) {
    --y;
    if (y < 0) {
        x -= 1;
        x < 0 ? x = 8: x;
        y = 8;
    }
}

//generate sudoku
void Sudoku::initsudoku() {
    clear();
    genRandom(_table[0]);
    int row(1), col(0);//fill from row 2, column 1
    int marks[9][9][9] = { { {0} } }; //marks[i][j][k] = 1 indicates that（i，j）fill (k+1) has been tried

    for (;;) {
        if (row == 9) { //generate successful
            return;
        }

        int ranNums[9] = {0};
        genRandom(ranNums);

        bool fill_row_success = false;
        for (int k = 0; k < 9; ++k) {
            if (marks[row][col][ranNums[k] - 1] != 0) {
                continue;
            }
            if(tryfill(row, col, ranNums[k])) {
                next(row, col);

                fill_row_success = true;
                break;
            }
        }
        if (!fill_row_success) {
            for (int i = 0; i < 9; ++i) {
                marks[row][col][i] = 0; //reset
            }

            previous(row, col);
            if (_table[row][col] != 0) {
                marks[row][col][_table[row][col] - 1] = 1; //tried,mark
            }

            if (row == 0 && col == 8) {  //finish
                break;
            }
            _table[row][col] = 0;
        }
    }
}

//check what can be filled in (i,j)
bool Sudoku::parseState(int i, int j) {
    if (_solution[i][j] != 0) {
        if (j < 8) {
            if (parseState(i, j + 1))   //same i, j+1
                return true;
        } else {
            if (i < 8) {
                if (parseState(i + 1, 0))    //i+1, j=0
                    return true;
            } else {
                return true;  //i >= 9  && j >= 9, finish
            }
        }
        return false;
    }
    int k, m, n, p, q;
    if (i >= 9 || j >= 9)
        return true;

    for (k = 1; k <= 9; k++) {
        int can = 1;                // can mark k
        for (m = 0; m < 9; ++m) {
            if (_solution[m][j] == k) {  // check column
                can = 0 ;
                break ;
            }
        }

        if (can) {
            for (n = 0; n < 9; ++n) {
                if (_solution[i][n] == k) {  // check row
                    can = 0 ;
                    break;
                }
            }
        }
        if (can) {         // check 3*3
            int up1 = (i / 3) * 3 + 3 ;
            int up2 = (j / 3) * 3 + 3;

            for (p = up1 - 3; p < up1; ++p) {
                if (can == 0)
                    break ;
                for (q = up2-3; q < up2; ++q) {
                    if (_solution[p][q] == k) {
                        can = 0;
                        break;
                    }
                }
            }
        }
        if (can) {
            _solution[i][j] = k;
            if (j < 8) {
                if (parseState(i, j + 1))
                    return true;
            } else {
                if (i < 8) {
                    if (parseState(i + 1, 0))
                        return true;
                } else {
                    return false; // i >= 9  && j >= 9, finish
                }
            }
            _solution[i][j] = 0 ;  //re
        }
    }
    return false; // can't fill 1 to 9
}
void Sudoku::initialize(int table[9][9]) {
    initsudoku();
    copyArray(_table, table);
    copyArray(_table, _answer);
}

void Sudoku::copyArray(int aArray[9][9], int bArray[9][9]) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            bArray[i][j] = aArray[i][j];
        }
    }
}

bool Sudoku::getSolution(int question[9][9], int answer[9][9]) {
    copyArray(question, _table);
    if (parseState(0, 0)) {
        copyArray(_solution, answer);
        return true;
    }
    return false;
}

bool Sudoku::checkSolution(int answer[9][9]) {
    //check row
    for (int i = 0; i < 9; ++i) {
        if (!isvalidOfArray(answer[i])) {
            return false;
        }
    }
    //reverse
    int temp_array[9][9]; //for a while
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            temp_array[i][j] = answer[j][i];
        }
    }

    for (int i = 0; i < 9; ++i) {
        if (!isvalidOfArray(temp_array[i])) {
            return false;
        }
    }
    return true;
}

//check 1 to 9
bool Sudoku::isvalidOfArray(int array[]) {
    int bucket[9] = {0};
    for (int i = 0; i < 9; ++i) {
        bucket[array[i] - 1]++;
    }

    for (int i = 0; i < 9; ++i) {
        if (bucket[i] != 1)
            return false;
    }
    return true;
}

void Sudoku::makeCondition(int table[9][9], int blankGridNum) {
    initialize(table);
    int answer[9][9];
    int backupArray[9][9];
    copyArray(table, backupArray);

    for (int k = 0; k < blankGridNum;) {
        int i = rand() % 9;
        int j = rand() % 9;
        if (table[i][j] == 0) {
            continue;
        }
        table[i][j] = 0;
        if (this->getSolution(table, answer)) {
            ++k;
            backupArray[i][j] = table[i][j];
        } else {
            //restore array
            copyArray(backupArray, table);
        }
    }
}

void Sudoku::clear() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            _table[i][j] = 0;
        }
    }
}

void Sudoku:: get_filled_answer(int question[9][9]){
    copyArray(question,_table);
    solve_filled_problem(0,0);
    //copyArray(_table,_filled_ans);
}

void Sudoku::solve_filled_problem(int i,int j){
    if(i>=9||j>=9){
        copyArray(_table,_filled_ans);
    }
    else if (_table[i][j] != 0) {
        if(j<8){
            ++j;
            solve_filled_problem(i,j);
        }else{
            j=0;
            ++i;
            if(i<9){
                solve_filled_problem(i,j);
            }
        }
    }else{
        for (int k=1;k<=9;++k){
            int can = 1;
            for (int row = 0; row < 9; ++row) {
                if (_table[row][j] == k) {
                    can = 0;
                    break;
                }
            }

            if(can){
                for (int col = 0; col < 9; ++col) {
                    if (_table[i][col] == k) {
                        can = 0;
                        break;
                    }
                }
            }

            if(can){
                int up1 = (i / 3) * 3 + 3 ;
                int up2 = (j / 3) * 3 + 3;
                for (int p = up1 - 3; p < up1; ++p) {
                    if(can == 0){
                        break;
                    }
                    for (int q = up2 - 3; q < up2; ++q) {
                        if (_table[p][q] == k) {
                            can = 0;
                            break;
                        }
                    }
                }
            }

            if(can){
                _table[i][j] = k;
                if(j<8){
                    ++j;
                    solve_filled_problem(i,j);
                }else{
                    j=0;
                    ++i;
                    if(i<9){
                        solve_filled_problem(i,j);
                    }
                }
            }
        }
    }
}
