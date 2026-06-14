#include "cell.h"
#include <QPainter>

Cell::Cell(int row, int col, QWidget *parent)
    : QWidget(parent), row(row), col(col), type(CellType::Empty)
{
    setFixedSize(22, 22);
    setAttribute(Qt::WA_Hover);
}

CellType Cell::getType() const {
    return type;
}

void Cell::setType(CellType newType) {
    type = newType;
    update(); // repaint 트리거
}

void Cell::reset() {
    setType(CellType::Empty);
}

QColor Cell::colorForType() const {
    switch (type) {
        case CellType::Empty:   return QColor("#0d0f18");
        case CellType::Wall:    return QColor("#4b5563"); // slate-600
        case CellType::Start:   return QColor("#10b981"); // emerald-500
        case CellType::Goal:    return QColor("#f43f5e"); // rose-500
        case CellType::Visited: return QColor("#7dd3fc"); // sky-300
        case CellType::Path:    return QColor("#fbbf24"); // amber-400
        default:                return QColor("#0d0f18");
    }
}

void Cell::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);

    painter.fillRect(rect(), QColor("#171717"));
    QRect inner = rect().adjusted(1, 1, -1, -1);
    painter.fillRect(inner, colorForType());
}

void Cell::mousePressEvent(QMouseEvent *event) {
    Q_UNUSED(event);
    emit pressed(row, col);
}

void Cell::enterEvent(QEnterEvent *event) {
    Q_UNUSED(event);
    emit entered(row, col);
}