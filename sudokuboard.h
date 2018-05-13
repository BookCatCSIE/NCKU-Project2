#ifndef BOARD
#define BOARD

#include <QFrame>

class QGroupBox;
class QGridLayout;
class ItemWidget;
class Sudoku;
class SudokuBoard : public QFrame {
    Q_OBJECT
  public:
    enum Condition {
        sudoku,
        fill_by_yourself
    };
    typedef QList<ItemWidget*> Items; //container
    typedef QVector<QGroupBox*> Groups; //container
    SudokuBoard(QWidget *parent = 0);
    ~SudokuBoard();

    void setCondition(Condition condition);
    bool checkAnswer();
    void clearAnswer();
    void showAnswer();
    void lockfilled();
    void show_filled_answer();

  private slots:
    void resetData();
    void updateItems();

  private:
    void init();

    void initData();

    int _blankGridNum;
    int _raw_data[9][9];//original problem
    int _going_data[9][9];//answering number
    int _filled_problem[9][9];
    int _filled_answer[9][9];

    QGridLayout *_glayout;
    Groups _groups;
    Items _items;

    Sudoku *_sudoku;
    Condition _current_condition;
};

#endif

