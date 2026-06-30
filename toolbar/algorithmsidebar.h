#pragma once

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

enum class Algorithm {
    BFS,
    DFS,
    Dijkstra,
    AStar
};

class AlgorithmSidebar : public QWidget {
    Q_OBJECT

public:
    explicit AlgorithmSidebar(QWidget *parent = nullptr);

signals:
    void algorithmChanged(Algorithm algo);
    void runRequested();

private:
    QPushButton *bfsBtn;
    QPushButton *dfsBtn;
    QPushButton *dijkstraBtn;
    QPushButton *astarBtn;
    QPushButton *runBtn;

    QPushButton *activeBtn = nullptr;

    void styleAlgoButton(QPushButton *btn);
    void setActiveButton(QPushButton *btn);
};