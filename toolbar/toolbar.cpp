#include "toolbar.h"

Toolbar::Toolbar(QWidget *parent) : QWidget(parent) {
    QHBoxLayout *layout = new QHBoxLayout(this);
    QPushButton *runBtn = new QPushButton("▶ Run", this);

    layout->setSpacing(8);
    layout->setContentsMargins(8, 8, 8, 8);
    
    

    startBtn  = new QPushButton("Start",  this);
    goalBtn   = new QPushButton("Goal",   this);
    wallBtn   = new QPushButton("Wall",   this);
    eraserBtn = new QPushButton("Eraser", this);
    clearBtn  = new QPushButton("Clear",  this);

    styleButton(startBtn,  "#10b981");
    styleButton(goalBtn,   "#f43f5e");
    styleButton(wallBtn,   "#4b5563");
    styleButton(eraserBtn, "#94a3b8");
    styleButton(clearBtn,  "#374151");
    styleButton(runBtn, "#2563eb");

    layout->addWidget(startBtn);
    layout->addWidget(goalBtn);
    layout->addWidget(wallBtn);
    layout->addWidget(eraserBtn);
    layout->addStretch();
    layout->addWidget(clearBtn);
    layout->addWidget(runBtn);

    // 시작은 Start 활성화
    setActiveButton(startBtn);

    connect(startBtn,  &QPushButton::clicked, this, [this]() {
        setActiveButton(startBtn);
        emit modeChanged(PlacingMode::Start);
    });
    connect(goalBtn,   &QPushButton::clicked, this, [this]() {
        setActiveButton(goalBtn);
        emit modeChanged(PlacingMode::Goal);
    });
    connect(wallBtn,   &QPushButton::clicked, this, [this]() {
        setActiveButton(wallBtn);
        emit modeChanged(PlacingMode::Wall);
    });
    connect(eraserBtn, &QPushButton::clicked, this, [this]() {
        setActiveButton(eraserBtn);
        emit modeChanged(PlacingMode::Eraser);
    });
    connect(clearBtn,  &QPushButton::clicked, this, [this]() {
        emit clearRequested();
    });
    connect(runBtn, &QPushButton::clicked, this, [this]() {
        emit runRequested();
    });
}

void Toolbar::styleButton(QPushButton *btn, const QString &color) {
    btn->setFixedHeight(32);
    btn->setCursor(Qt::PointingHandCursor);
    btn->setStyleSheet(QString(
        "QPushButton {"
        "  background-color: %1;"
        "  color: white;"
        "  border: none;"
        "  border-radius: 6px;"
        "  padding: 0 16px;"
        "  font-size: 13px;"
        "  font-weight: 500;"
        "}"
        "QPushButton:hover { opacity: 0.85; }"
    ).arg(color));
}

void Toolbar::setActiveButton(QPushButton *btn) {
    // 이전 버튼 테두리 제거
    if (activeBtn) {
        activeBtn->setStyleSheet(
            activeBtn->styleSheet().replace(
                "border: 2px solid white;", ""
            )
        );
    }
    // 새 버튼 테두리 추가
    btn->setStyleSheet(btn->styleSheet() +
        "QPushButton { border: 2px solid white; }"
    );
    activeBtn = btn;
}