#include "companywidget.h"
#include "assets.h"
#include "model/companytile.h"

using namespace model;

namespace view {

// Constructor

CompanyWidget::CompanyWidget(QWidget *parent)
    : RotatingWidget(BASE_WIDTH, BASE_HEIGHT, parent) {}


// Getters and Setters

QColor CompanyWidget::getOwnerColor() const { return ownerColor; }

void CompanyWidget::setOwnerColor(const QColor &newOwnerColor) {
    ownerColor = newOwnerColor;
}

QString CompanyWidget::getName() const { return name; }

void CompanyWidget::setName(const QString &newName) { name = newName; }

// RotatingWidget interface

void CompanyWidget::paintRotated(QPaintEvent *event, QPainter &painter) {
    int width = BASE_WIDTH;
    int height = BASE_HEIGHT;

    QString priceStr = "$ " + QString::number(CompanyTile::PRICE);

    painter.setPen(QPen(Qt::black, 2));
    painter.setBrush(QBrush(QColor("#D0F0D0")));
    painter.drawRect(QRect(0, 0, width, height));
    painter.drawRect(QRect(0, height-20, width, 20));

    painter.setBrush(QBrush(ownerColor));
    painter.drawRect(QRect(0, 0, width, 12));

    int mid = (width - 48)/2;
    if (name == "Electric Company") {
        painter.drawPixmap(QRect(mid,52,48,48), QPixmap(Assets::IMAGE_ELECTRIC_PATH));
    } else if (name == "Water Works") {
        painter.drawPixmap(QRect(mid,52,48,48), QPixmap(Assets::IMAGE_WATER_PATH));
    }
    // If another type of company don't draw image.

    int flags = Qt::AlignCenter | Qt::TextWordWrap;
    painter.drawText(0, 12, width, 52-12, flags, name);
    painter.drawText(0, height-20, width, 20, flags, priceStr);
};

} // namespace view
