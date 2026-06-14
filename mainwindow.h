#pragma once

#include <QMainWindow>
#include <QGridLayout>
#include <QWidget>
#include <QPushButton>
#include <vector>

#include "grid/cell.h"

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

    // grid data
    std::vector<std::vector<Cell*>> grid;

    // reset grid
    void setupGrid();
};