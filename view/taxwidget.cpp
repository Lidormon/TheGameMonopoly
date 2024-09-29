#include "taxwidget.h"
#include "assets.h"

namespace view {

// Constructor

TaxWidget::TaxWidget(QWidget *parent)
    : RotatingWidget(BASE_WIDTH, BASE_HEIGHT, parent) {}

// Getters and Setters

QString TaxWidget::getName() const { return name; }

void TaxWidget::setName(const QString &newName) { name = newName; }

int TaxWidget::getPrice() const { return price; }

void TaxWidget::setPrice(int newPrice) { price = newPrice; }

// RotatingWidge override

void TaxWidget::paintRotated(QPaintEvent *event, QPainter &painter) {
    int width = BASE_WIDTH;
    int height = BASE_HEIGHT;

    QString priceStr = "- $ " + QString::number(price);
    QPixmap image(Assets::IMAGE_TAX_PATH);

    painter.setPen(QPen(Qt::black, 2));
    painter.setBrush(QBrush(QColor("#D0F0D0")));
    painter.drawRect(QRect(0, 0, width, height));
    painter.drawRect(QRect(0, height-20, width, 20));

    int mid = (width - 48)/2;
    painter.drawPixmap(QRect(mid,40,48,48), image);

    int flags = Qt::AlignCenter | Qt::TextWordWrap;
    painter.drawText(0, 0, width, 40, flags, name);
    painter.drawText(0, height-20, width, 20, flags, priceStr);
}

} // namespace view
