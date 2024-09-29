#ifndef RAILWAYWIDGET_H
#define RAILWAYWIDGET_H

#include "rotatingwidget.h"

namespace view {

class RailwayWidget : public RotatingWidget
{
    Q_OBJECT
public:
    explicit RailwayWidget(QWidget *parent = nullptr);

public:
    static constexpr int BASE_WIDTH = 80;
    static constexpr int BASE_HEIGHT = 120;

public: // Getters and Setters
    QColor getOwnerColor() const;
    void setOwnerColor(const QColor &newOwnerColor);
    QString getName() const;
    void setName(const QString &newName);

public: // RotatingWidget interface
    void paintRotated(QPaintEvent *event, QPainter &painter) override;

private: // Properties
    QColor ownerColor;
    QString name;
};

} // namespace view

#endif // RAILWAYWIDGET_H
