#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Pathfinding Visualizer");
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

            connect(cell, &Cell::pressed, this, &MainWindow::onCellPressed);
            connect(cell, &Cell::entered, this, &MainWindow::onCellEntered);
        }
    }
}

void MainWindow::onCellPressed(int row, int col) {
    isMouseDown = true;

    Cell *cell = grid[row][col];

    if (currentMode == PlacingMode::Start) {
        // 기존 Start 제거
        for (auto &r : grid)
            for (auto &c : r)
                if (c->getType() == CellType::Start)
                    c->reset();

        cell->setType(CellType::Start);
        currentMode = PlacingMode::Goal; // 자동으로 Goal 모드로

    } else if (currentMode == PlacingMode::Goal) {
        // 기존 Goal 제거
        for (auto &r : grid)
            for (auto &c : r)
                if (c->getType() == CellType::Goal)
                    c->reset();

        cell->setType(CellType::Goal);
        currentMode = PlacingMode::Wall; // 자동으로 Wall 모드로

    } else if (currentMode == PlacingMode::Wall) {
        if (cell->getType() == CellType::Empty)
            cell->setType(CellType::Wall);

    } else if (currentMode == PlacingMode::Eraser) {
        if (cell->getType() != CellType::Start &&
            cell->getType() != CellType::Goal)
            cell->reset();
    }
}

void MainWindow::onCellEntered(int row, int col) {
    if (!isMouseDown) return;
    if (currentMode != PlacingMode::Wall &&
        currentMode != PlacingMode::Eraser) return;

    Cell *cell = grid[row][col];

    if (currentMode == PlacingMode::Wall) {
        if (cell->getType() == CellType::Empty)
            cell->setType(CellType::Wall);
    } else if (currentMode == PlacingMode::Eraser) {
        if (cell->getType() != CellType::Start &&
            cell->getType() != CellType::Goal)
            cell->reset();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    Q_UNUSED(event);
    isMouseDown = false;
}