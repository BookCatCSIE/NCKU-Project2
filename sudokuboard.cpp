#include "sudokuboard.h"
#include "sudoku.h"
#include "itemwidget.h"

#include <QLayout>
#include <QPushButton>
#include <QGroupBox>


SudokuBoard::SudokuBoard(QWidget *parent)
    :QFrame(parent) {
    resize(450, 450);
    _blankGridNum = 15;
    _sudoku = new Sudoku();
    setEnabled(true);
    _glayout = NULL;
    init();
}

SudokuBoard::~SudokuBoard() {
    delete _sudoku;
}

void SudokuBoard::initData() {
    _sudoku->makeCondition(_raw_data, _blankGridNum);
    _sudoku->copyArray(_raw_data, _going_data);
}

void SudokuBoard::init() {
    initData();
    _items.clear();
    _groups.clear();
    _glayout = new QGridLayout;

    for (int i = 0; i < 9; ++i) {
        QGroupBox* group = new QGroupBox;
        QGridLayout *layout = new QGridLayout;
        layout->setContentsMargins(0, 0, 0, 0);
        group->setLayout(layout);
        _glayout->addWidget(group, i / 3 * 3, i % 3 * 3, 3, 3);
        _groups.append(group);
    }
    _glayout->setSpacing(1);

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            ItemWidget *w = new ItemWidget(_going_data[i][j]);
            _items.append(w);
            int pos = i / 3 * 3 + j / 3; //index of 3 * 3 grid in group
            QGridLayout *layout = qobject_cast<QGridLayout*>(_groups[pos]->layout());
            if (!layout) {
                continue;
            }

            layout->addWidget(w, i % 3, j % 3);
        }
    }
    setLayout(_glayout);
}

void SudokuBoard::resetData() {
    initData();
    updateItems();
}

void SudokuBoard::updateItems() {
    int index = 0;
    foreach(ItemWidget *w, _items) {
        if (!w) {
            ++index;
            continue;
        }
        w->setValue(_going_data[index / 9][index % 9], true);
        ++index;
    }
}

bool SudokuBoard::checkAnswer() {
    int index = 0;
    foreach(ItemWidget *w, _items) {
        if (!w) {
            ++index;
            continue;
        }
        _going_data[index / 9][index % 9] = w->text().toInt();
        ++index;
    }
    return _sudoku->checkSolution(_going_data);
}

void SudokuBoard::setCondition(Condition condition) {
    switch (condition) {
    case sudoku:
        _blankGridNum = 15;
        break;
    case fill_by_yourself:
        _blankGridNum = 81;
        break;
    default:
        _blankGridNum = 15;
        break;
    }
}

void SudokuBoard::clearAnswer() {
    _sudoku->copyArray(_raw_data, _going_data);
    updateItems();
}

void SudokuBoard::showAnswer(){
    _sudoku->copyArray(_sudoku->_answer, _going_data);
    updateItems();
}

void SudokuBoard::lockfilled(){
    int index = 0;
    foreach(ItemWidget *w, _items) {
        if (!w) {
            ++index;
            continue;
        }
        _going_data[index / 9][index % 9] = w->text().toInt();
        w->lock_filled(_going_data[index / 9][index % 9]);
        ++index;
    }
    _sudoku->copyArray(_going_data,_filled_problem);
}

void SudokuBoard::show_filled_answer(){
    _sudoku->get_filled_answer(_filled_problem);
    _sudoku->copyArray(_sudoku->_filled_ans, _going_data);
    updateItems();
}
