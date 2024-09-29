#include "cornerwidget.h"

#include <assets.h>

namespace view {

// Constructor

CornerWidget::CornerWidget(const QPixmap &image, QWidget *parent)
    : RotatingWidget(BASE_WIDTH, BASE_HEIGHT, parent), image(image) {

    setRotation(ROT_UP);
}

// Getters and Setters

QPixmap CornerWidget::getImage() const { return image; }

void CornerWidget::setImage(const QPixmap &newImage) { image = newImage; }

// RotatingWidget interface

void CornerWidget::paintRotated(QPaintEvent *event, QPainter &painter) {
    int width = BASE_WIDTH;
    int height = BASE_HEIGHT;

    painter.setPen(QPen(Qt::black, 2));
    painter.setBrush(QBrush(QColor("#D0F0D0")));
    painter.drawRect(QRect(0, 0, width, height));

    painter.drawPixmap(0, 0, image);
}

} // namespace view
