#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Pathplanning Visualizer");
    setFixedSize(720, 720);

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    gridLayout = new QGridLayout(centralWidget);
    gridLayout->setSpacing(1);
    gridLayout->setContentsMargins(8, 8, 8, 8);

    setupGrid();
}

MainWindow::~MainWindow() {}

void MainWindow::setupGrid() {
    grid.resize(ROWS, std::vector<Cell*>(COLS, nullptr));

    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            Cell *cell = new Cell(r, c, this);
            grid[r][c] = cell;
            gridLayout->addWidget(cell, r, c);
        }
    }
}