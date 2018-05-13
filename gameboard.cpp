#include "gameboard.h"
#include "sudokuboard.h"

#include <QGroupBox>
#include <QPushButton>
#include <QLayout>
#include <QMessageBox>
#include <QComboBox>
#include <QLabel>

GameBoard::GameBoard(QWidget *parent)
	:QWidget(parent)
{
	setup();
}

void GameBoard::setup()
{
	initCheckBox();
    QVBoxLayout *switchLayout = new QVBoxLayout;
    switchLayout->addWidget(_switchCheckBox);
    QGroupBox *switchGroup = new QGroupBox;
    switchGroup->setTitle("switch");
    switchGroup->setLayout(switchLayout);
	_sudoku_board = new SudokuBoard();
    _resetGameButton = new QPushButton(tr("reset"));
    _submitButon = new QPushButton("finish");
    _clearAnswerButton = new QPushButton("clear");
    _finish_fillButton = new QPushButton("finish_fill");
    _show_ansButton = new QPushButton("show_answer");
    _show_filled_ansButton = new QPushButton("show_filled_answer");
	connect(_resetGameButton, SIGNAL(clicked()), _sudoku_board, SLOT(resetData()));
	connect(_submitButon, SIGNAL(clicked()), this, SLOT(finished()));
	connect(_clearAnswerButton, SIGNAL(clicked()), this, SLOT(clearAnswer()));
    connect(_finish_fillButton, SIGNAL(clicked()), this, SLOT(finish_fill()));
    connect(_show_ansButton, SIGNAL(clicked()), this, SLOT(showAnswer()));
    connect(_show_filled_ansButton, SIGNAL(clicked()), this, SLOT(showFilledAnswer()));
    QHBoxLayout *mainLayout = new QHBoxLayout;
	QGroupBox *buttonsBox = new QGroupBox;
    buttonsBox->setTitle("button");
	QGridLayout *buttonsLayout = new QGridLayout;
	buttonsLayout->setContentsMargins(0, 0, 0, 0);
    buttonsLayout->addWidget(_clearAnswerButton, 0, 1);
    buttonsLayout->addWidget(_submitButon, 1, 1);
    buttonsLayout->addWidget(_resetGameButton, 3, 1);
    buttonsLayout->addWidget(_finish_fillButton, 4, 1);
    buttonsLayout->addWidget(_show_ansButton, 2, 1);
    buttonsLayout->addWidget(_show_filled_ansButton, 5, 1);
	buttonsBox->setLayout(buttonsLayout);
    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(switchGroup);
    rightLayout->addWidget(buttonsBox);
	mainLayout->addWidget(_sudoku_board, Qt::AlignJustify);
    mainLayout->addLayout(rightLayout, Qt::AlignRight);
	setLayout(mainLayout);
}

void GameBoard::initCheckBox()
{
    _switchCheckBox = new QComboBox();
    _switchCheckBox->addItems(QStringList() << "sudoku" << "fill_by_yourself");
    connect(_switchCheckBox, SIGNAL(currentIndexChanged(int)), this, SLOT(switchCondition()));
}

void GameBoard::finished()
{
	if (_sudoku_board->checkAnswer()) {
        QMessageBox::information(this, " ", "Successful!", QMessageBox::Ok);
	} else {
        QMessageBox::information(this, " ", "Failed", QMessageBox::Ok);
	}
}

void GameBoard::clearAnswer()
{
	_sudoku_board->clearAnswer();
}

void GameBoard::switchCondition()
{
    int index = _switchCheckBox->currentIndex();
	switch(index) {
		case 0:
        _sudoku_board->setCondition(SudokuBoard::sudoku);
		break;
        case 1:
        _sudoku_board->setCondition(SudokuBoard::fill_by_yourself);
        break;
		default:
		break;
	}
}

void GameBoard:: finish_fill(){
    _sudoku_board->lockfilled();
}

void GameBoard:: showAnswer(){
    _sudoku_board->showAnswer();
}

void GameBoard:: showFilledAnswer(){
    _sudoku_board->show_filled_answer();
}

