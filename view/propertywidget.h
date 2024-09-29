#ifndef PROPERTYWIDGET_H
#define PROPERTYWIDGET_H

#include "view/rotatingwidget.h"
#include <QWidget>

namespace view {

class PropertyWidget : public RotatingWidget
{
    Q_OBJECT
public:
    explicit PropertyWidget(QWidget *parent = nullptr);

public:
    static constexpr int BASE_WIDTH = 80;
    static constexpr int BASE_HEIGHT = 120;

public: // Getters and Setters
    QColor getPropColor() const;
    void setPropColor(const QColor &newPropColor);
    QColor getOwnerColor() const;
    void setOwnerColor(const QColor &newOwnerColor);
    QString getName() const;
    void setName(const QString &newName);
    int getPrice() const;
    void setPrice(int newPrice);


public: // RotatingWidget interface
    void paintRotated(QPaintEvent *event, QPainter &painter) override;

    int getHouseCount() const;
    void setHouseCount(int newHouseCount);

private: // Properties
    QColor propColor, ownerColor;
    QString name;
    int price;
    int houseCount;
};

} // namespace view

#endif // PROPERTYWIDGET_H
