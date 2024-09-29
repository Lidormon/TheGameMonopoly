#include "luckcardwidget.h"

#include "assets.h"

#include "model/luckcardtile.h"

namespace view {

LuckCardWidget::LuckCardWidget(QWidget *parent)
    : RotatingWidget(BASE_WIDTH, BASE_HEIGHT, parent) {}


// Getters and Setters

QString LuckCardWidget::getName() const { return name; }

void LuckCardWidget::setName(const QString &newName) { name = newName; }

// RotatingWidge override

void LuckCardWidget::paintRotated(QPaintEvent *event, QPainter &painter) {
    int width = BASE_WIDTH;
    int height = BASE_HEIGHT;

    QPixmap image(Assets::IMAGE_TAX_PATH);

    painter.setPen(QPen(Qt::black, 2));
    painter.setBrush(QBrush(QColor("#D0F0D0")));
    painter.drawRect(QRect(0, 0, width, height));

    int flags = Qt::AlignCenter | Qt::TextWordWrap;
    painter.drawText(0, 0, width, 52, flags, name);

    if (name == model::LuckCardTile::CHANCE) {
        QFont font = painter.font();
        font.setPointSize(40);
        font.setBold(true);
        painter.setFont(font);
        painter.setBrush(QBrush(Qt::red));
        painter.drawText(0, 52, width, 48, Qt::AlignCenter, "?");
    } else if (name == model::LuckCardTile::COMMUNITY_CHEST) {
        int mid = (width - 48)/2;
        painter.drawPixmap(QRect(mid,52,48,48), QPixmap(Assets::IMAGE_COMMUNITY_CHEST_PATH));
    }
}

} // namespace view
