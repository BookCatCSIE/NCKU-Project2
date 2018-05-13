#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "gameboard.h"
#include <QLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle(tr("Funny Sudoku!"));
    setMinimumSize(1050, 750);//設定視窗最小長寬
    GameBoard * gameBoard = new GameBoard(this);
    setCentralWidget(gameBoard);
}

MainWindow::~MainWindow()
{
    delete ui;
}
