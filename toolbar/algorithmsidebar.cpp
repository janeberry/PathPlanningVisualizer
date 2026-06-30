#include "algorithmsidebar.h"

AlgorithmSidebar::AlgorithmSidebar(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(8);
    layout->setContentsMargins(8, 8, 8, 8);

    QLabel *label = new QLabel("Algorithm", this);
    label->setStyleSheet("color: #94a3b8; font-size: 11px; font-weight: 600; letter-spacing: 1px;");
    layout->addWidget(label);

    bfsBtn      = new QPushButton("BFS", this);
    dfsBtn      = new QPushButton("DFS", this);
    dijkstraBtn = new QPushButton("Dijkstra", this);
    astarBtn    = new QPushButton("A*", this);
    runBtn      = new QPushButton("▶ Run", this);

    styleAlgoButton(bfsBtn);
    styleAlgoButton(dfsBtn);
    styleAlgoButton(dijkstraBtn);
    styleAlgoButton(astarBtn);

    runBtn->setFixedHeight(36);
    runBtn->setCursor(Qt::PointingHandCursor);
    runBtn->setStyleSheet(
        "QPushButton {"
        "  background-color: #2563eb;"
        "  color: white;"
        "  border: none;"
        "  border-radius: 6px;"
        "  font-size: 13px;"
        "  font-weight: 600;"
        "}"
    );

    layout->addWidget(bfsBtn);
    layout->addWidget(dfsBtn);
    layout->addWidget(dijkstraBtn);
    layout->addWidget(astarBtn);
    layout->addStretch();
    layout->addWidget(runBtn);

    setActiveButton(bfsBtn); 

    connect(bfsBtn, &QPushButton::clicked, this, [this]() {
        setActiveButton(bfsBtn);
        emit algorithmChanged(Algorithm::BFS);
    });
    connect(dfsBtn, &QPushButton::clicked, this, [this]() {
        setActiveButton(dfsBtn);
        emit algorithmChanged(Algorithm::DFS);
    });
    connect(dijkstraBtn, &QPushButton::clicked, this, [this]() {
        setActiveButton(dijkstraBtn);
        emit algorithmChanged(Algorithm::Dijkstra);
    });
    connect(astarBtn, &QPushButton::clicked, this, [this]() {
        setActiveButton(astarBtn);
        emit algorithmChanged(Algorithm::AStar);
    });
    connect(runBtn, &QPushButton::clicked, this, [this]() {
        emit runRequested();
    });
}

void AlgorithmSidebar::styleAlgoButton(QPushButton *btn) {
    btn->setFixedHeight(36);
    btn->setCursor(Qt::PointingHandCursor);
    btn->setStyleSheet(
        "QPushButton {"
        "  background-color: #1e293b;"
        "  color: #cbd5e1;"
        "  border: 1px solid #334155;"
        "  border-radius: 6px;"
        "  text-align: left;"
        "  padding-left: 12px;"
        "  font-size: 13px;"
        "}"
        "QPushButton:hover { background-color: #334155; }"
    );
}

void AlgorithmSidebar::setActiveButton(QPushButton *btn) {
    if (activeBtn) {
        styleAlgoButton(activeBtn); 
    }
    btn->setStyleSheet(btn->styleSheet() +
        "QPushButton { border: 2px solid #60a5fa; }"
    );
    activeBtn = btn;
}