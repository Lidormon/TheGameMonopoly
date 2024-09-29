#include "assets.h"
#include "propertywidget.h"
#include "model/propertytile.h"

#include <QPainter>

namespace view {

using namespace model;

// Constructor

PropertyWidget::PropertyWidget(QWidget *parent)
    : RotatingWidget(BASE_WIDTH, BASE_HEIGHT, parent) {}

// Getters and Setters

QColor PropertyWidget::getPropColor() const { return propColor; }

void PropertyWidget::setPropColor(const QColor &newPropColor) {
    propColor = newPropColor;
}

QColor PropertyWidget::getOwnerColor() const { return ownerColor; }

void PropertyWidget::setOwnerColor(const QColor &newOwnerColor) {
    ownerColor = newOwnerColor;
}

QString PropertyWidget::getName() const { return name; }

void PropertyWidget::setName(const QString &newName) { name = newName; }

int PropertyWidget::getPrice() const { return price; }

void PropertyWidget::setPrice(int newPrice) { price = newPrice; }

int PropertyWidget::getHouseCount() const { return houseCount; }

void PropertyWidget::setHouseCount(int newHouseCount) {
    houseCount = newHouseCount;
}

// RotatingWidget interface

void PropertyWidget::paintRotated(QPaintEvent *event, QPainter &painter) {
    int width = BASE_WIDTH;
    int height = BASE_HEIGHT;

    QString priceStr = "$ " + QString::number(price);

    painter.setPen(QPen(Qt::black, 2));
    painter.setBrush(QBrush(QColor("#D0F0D0")));
    painter.drawRect(QRect(0, 0, width, height));
    painter.drawRect(QRect(0, height-20, width, 20));

    painter.setBrush(QBrush(propColor));
    painter.drawRect(QRect(0, 0, width, 20));

    // if hotel
    if (houseCount == PropertyTile::HOTEL_HOUSE_COUNT) {
        QPixmap hotel(Assets::IMAGE_HOTEL_PATH);
        painter.drawPixmap(2, 2, hotel);
    // if houses
    } else if (houseCount > 0) {
        QPixmap house(Assets::IMAGE_HOUSE_PATH);
        for (int i = 0; i < houseCount; i++) {
            int x = 2 + 20*i;
            painter.drawPixmap(x, 2, house);
        }
    }

    painter.setBrush(QBrush(ownerColor));
    painter.drawRect(QRect(0, 20, width, 12));

    int flags = Qt::AlignCenter | Qt::TextWordWrap;
    painter.drawText(0, 32, width, height-52, flags, name);
    painter.drawText(0, height-20, width, 20, flags, priceStr);
}

} // namespace view
