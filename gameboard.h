#ifndef GAMEBOARD      //遊戲整體介面
#define GAMEBOARD
#include <QWidget>

class QGroupBox;
class QPushButton;
class SudokuBoard;
class QComboBox;
class GameBoard : public QWidget
{
	    Q_OBJECT
public:
	explicit GameBoard(QWidget *parent = 0);

private slots:
	void setup();
	void finished();
	void clearAnswer();
    void switchCondition();
    void finish_fill();
    void showAnswer();
    void showFilledAnswer();

private:
	void initCheckBox();

	QPushButton *_resetGameButton;
	QPushButton *_submitButon;
	QPushButton *_clearAnswerButton;
    QPushButton *_finish_fillButton;
    QPushButton *_show_ansButton;
    QPushButton *_show_filled_ansButton;
							
	SudokuBoard * _sudoku_board;
    QComboBox *_switchCheckBox;
};
#endif
