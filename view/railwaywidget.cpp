#include "railwaywidget.h"
#include "assets.h"

#include <model/railwaytile.h>

namespace view {

// Constructor

RailwayWidget::RailwayWidget(QWidget *parent)
    : RotatingWidget(BASE_WIDTH, BASE_HEIGHT, parent) {}


// Getters and Setters

QColor RailwayWidget::getOwnerColor() const { return ownerColor; }

void RailwayWidget::setOwnerColor(const QColor &newOwnerColor) {
    ownerColor = newOwnerColor;
}

QString RailwayWidget::getName() const { return name; }

void RailwayWidget::setName(const QString &newName) { name = newName; }

// RotatingWidget interface

void RailwayWidget::paintRotated(QPaintEvent *event, QPainter &painter) {
    int width = BASE_WIDTH;
    int height = BASE_HEIGHT;

    QString priceStr = "$ " + QString::number(model::RailwayTile::PRICE);
    QPixmap image(Assets::IMAGE_RAILWAY_PATH);

    painter.setPen(QPen(Qt::black, 2));
    painter.setBrush(QBrush(QColor("#D0F0D0")));
    painter.drawRect(QRect(0, 0, width, height));
    painter.drawRect(QRect(0, height-20, width, 20));

    painter.setBrush(QBrush(ownerColor));
    painter.drawRect(QRect(0, 0, width, 12));

    int mid = (width - 48)/2;
    painter.drawPixmap(QRect(mid,52,48,48), image);

    int flags = Qt::AlignCenter | Qt::TextWordWrap;
    painter.drawText(0, 12, width, 52-12, flags, name);
    painter.drawText(0, height-20, width, 20, flags, priceStr);
}
} // namespace view
