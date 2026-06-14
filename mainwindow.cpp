#include "mainwindow.h"
#include "toolbar/toolbar.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Pathfinding Visualizer");
    setFixedSize(720, 720);

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setSpacing(8);
    mainLayout->setContentsMargins(8, 8, 8, 8);

    toolbar = new Toolbar(this);
    mainLayout->addWidget(toolbar);

    QWidget *gridWidget = new QWidget(this);
    gridLayout = new QGridLayout(gridWidget);
    gridLayout->setSpacing(1);
    gridLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(gridWidget);

    centralWidget->setMouseTracking(true);
    setupGrid();
    connect(toolbar, &Toolbar::modeChanged, this, [this](PlacingMode mode) {
        currentMode = mode;
    });
    connect(toolbar, &Toolbar::clearRequested, this, [this]() {
        for (auto &r : grid)
            for (auto &c : r)
                c->reset();
        currentMode = PlacingMode::Start;
    });
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
        for (auto &r : grid)
            for (auto &c : r)
                if (c->getType() == CellType::Start)
                    c->reset();
        cell->setType(CellType::Start);

    } else if (currentMode == PlacingMode::Goal) {
        for (auto &r : grid)
            for (auto &c : r)
                if (c->getType() == CellType::Goal)
                    c->reset();
        cell->setType(CellType::Goal);

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