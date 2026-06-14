#pragma once

#include <QWidget>
#include <QMouseEvent>
#include <QEnterEvent>


enum class CellType {
    Empty,
    Wall,
    Start,
    Goal,
    Visited,
    Path
};

class Cell : public QWidget {
    Q_OBJECT

public:
    explicit Cell(int row, int col, QWidget *parent = nullptr);

    // getter / setter
    CellType getType() const;
    void setType(CellType type);

    int getRow() const { return row; }
    int getCol() const { return col; }

    void reset();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void enterEvent(QEnterEvent *event) override;

signals:
    void pressed(int row, int col);
    void entered(int row, int col);

private:
    int row;
    int col;
    CellType type;

    QColor colorForType() const;
};