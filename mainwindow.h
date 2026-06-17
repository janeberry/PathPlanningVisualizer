#pragma once

#include <QMainWindow>
#include <QGridLayout>
#include <QWidget>
#include <vector>
#include <QTimer>

#include "grid/cell.h"
#include "toolbar/toolbar.h"
#include "algorithms/bfs.h"


const int ROWS = 30;
const int COLS = 30;


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget     *centralWidget;
    QGridLayout *gridLayout;
    Toolbar *toolbar;
    QVBoxLayout *mainLayout; 
    QTimer *animTimer;

    std::vector<std::vector<Cell*>> grid;
    PlacingMode currentMode = PlacingMode::Start;
    std::vector<std::pair<int,int>> visitedQueue;
    std::vector<std::pair<int,int>> pathQueue;
    
    bool isMouseDown = false;
    int animIndex = 0;
    bool isAnimatingVisited = true;

    void setupGrid();
    void runBFSAnimation();
    void animationStep();
    void clearVisualization();

private slots:
    void onCellPressed(int row, int col);
    void onCellEntered(int row, int col);

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;

signals:
    void modeUpdated(PlacingMode mode);
};

