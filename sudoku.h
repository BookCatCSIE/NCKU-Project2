#ifndef SUDOKU  //題目產生法 解法
#define SUDOKU

class Sudoku {
  public:
    Sudoku();
    ~Sudoku();

    bool getSolution(int question[9][9], int answer[9][9]);
    void initialize(int table[9][9]);

    bool checkSolution(int answer[9][9]);
    bool isvalidOfArray(int array[9]);
    void makeCondition(int table[9][9], int blankGridNum);
    void copyArray(int aArray[9][9], int bArray[9][9]);
    int _answer[9][9];
    int _filled_ans[9][9];
    void get_filled_answer(int question[9][9]);

  private:
    void initsudoku();
    int  initialState(int i, int j);
    bool tryfill(int i, int j, int k);
    void next(int &x, int &y);
    void previous(int &x, int &y);
    void genRandom(int line[]);
    bool parseState(int i, int j);
    void clear();
    void solve_filled_problem(int i, int j);

    int _table[9][9];  //for a while
    int _solution[9][9]; //choosen number
};

#endif
