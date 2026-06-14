#pragma once

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>

#include "placingmode.h"

class Toolbar : public QWidget {
    Q_OBJECT

public:
    explicit Toolbar(QWidget *parent = nullptr);

signals:
    void modeChanged(PlacingMode mode);
    void clearRequested();

private:
    QPushButton *startBtn;
    QPushButton *goalBtn;
    QPushButton *wallBtn;
    QPushButton *eraserBtn;
    QPushButton *clearBtn;

    void styleButton(QPushButton *btn, const QString &color);
    void setActiveButton(QPushButton *btn);

    QPushButton *activeBtn = nullptr;
};