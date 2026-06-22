#include "mainwindow.h"
#include "toolbar/toolbar.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Pathplanning Visualizer");
    setFixedSize(900, 760);

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setSpacing(8);
    mainLayout->setContentsMargins(8, 8, 8, 8);

    toolbar = new Toolbar(this);
    mainLayout->addWidget(toolbar);
    contentLayout = new QHBoxLayout();
    sidebar = new AlgorithmSidebar(this);
    contentLayout->addWidget(sidebar);

    QWidget *gridWidget = new QWidget(this);
    gridLayout = new QGridLayout(gridWidget);
    gridLayout->setSpacing(1);
    gridLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(gridWidget);

    mainLayout->addLayout(contentLayout);
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

    animTimer = new QTimer(this);    
    connect(sidebar, &AlgorithmSidebar::algorithmChanged, this, [this](Algorithm algo) {
        currentAlgorithm = algo;
    });
    connect(sidebar, &AlgorithmSidebar::runRequested, this, &MainWindow::runAlgorithmAnimation);
    connect(animTimer, &QTimer::timeout, this, &MainWindow::animationStep);

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

void MainWindow::clearVisualization() {
    for (auto &r : grid)
        for (auto &c : r)
            if (c->getType() == CellType::Visited ||
                c->getType() == CellType::Path)
                c->reset();
}

void MainWindow::runAlgorithmAnimation() {
    clearVisualization();

    bool found = false;
    std::vector<std::pair<int,int>> visited, path;

    if (currentAlgorithm == Algorithm::BFS) {
        BFSResult result = runBFS(grid, ROWS, COLS);
        visited = result.visitedOrder;
        path    = result.path;
        found   = result.found;
    } else if (currentAlgorithm == Algorithm::AStar) {
        AStarResult result = runAStar(grid, ROWS, COLS);
        visited = result.visitedOrder;
        path    = result.path;
        found   = result.found;
    }
    
    if (visited.empty() && !found) return;

    visitedQueue = visited;
    pathQueue    = path;
    animIndex    = 0;
    isAnimatingVisited = true;

    animTimer->start(15);
}

void MainWindow::animationStep() {
    if (isAnimatingVisited) {
        if (animIndex < (int)visitedQueue.size()) {
            auto [r, c] = visitedQueue[animIndex++];
            grid[r][c]->setType(CellType::Visited);
        } else {
            // visited done, path start
            isAnimatingVisited = false;
            animIndex = (int)pathQueue.size() - 1; // (goal→start)
        }
    } else {
        if (animIndex >= 0) {
            auto [r, c] = pathQueue[animIndex--];
            grid[r][c]->setType(CellType::Path);
        } else {
            animTimer->stop(); 
        }
    }
}
