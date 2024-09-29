#include "rotatingwidget.h"
#include "qpainter.h"

namespace view {

RotatingWidget::RotatingWidget(int baseW, int baseH, QWidget *parent)
    : QWidget{parent}, baseWidth(baseW), baseHeight(baseH) {

    setFixedSize(baseWidth, baseHeight);
}

TileRotation RotatingWidget::getRotation() const {
    return rotation;
}

void RotatingWidget::setRotation(TileRotation newRotation) {
    rotation = newRotation;
}

void RotatingWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    int max = std::max(baseHeight, baseWidth);
    setFixedSize(max, max);

    switch(rotation) {
    case ROT_UP: break;
    case ROT_RIGHT:
        painter.translate(baseHeight, 0);
        painter.rotate(90);
        break;
    case ROT_DOWN:
        painter.rotate(180);
        painter.translate(-baseWidth, -baseHeight);
        break;
    case ROT_LEFT:
        painter.translate(0, baseWidth);
        painter.rotate(270);
        break;
    }

    paintRotated(event, painter);

    switch(rotation) {
    case ROT_UP: case ROT_DOWN: setFixedSize(baseWidth, baseHeight); break;
    case ROT_RIGHT: case ROT_LEFT: setFixedSize(baseHeight, baseWidth); break;
    }
}

} // namespace view
