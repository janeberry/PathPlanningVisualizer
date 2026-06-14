#pragma once

#include <QMainWindow>
#include <QGridLayout>
#include <QWidget>
#include <vector>

#include "grid/cell.h"

const int ROWS = 30;
const int COLS = 30;

enum class PlacingMode {
    Start,
    Goal,
    Wall,
    Eraser
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget     *centralWidget;
    QGridLayout *gridLayout;

    std::vector<std::vector<Cell*>> grid;
    PlacingMode currentMode = PlacingMode::Start;
    bool isMouseDown = false;

    void setupGrid();

private slots:
    void onCellPressed(int row, int col);
    void onCellEntered(int row, int col);

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;
};

