#ifndef ROTATINGWIDGET_H
#define ROTATINGWIDGET_H

#include "view/tilerotation.h"
#include <QPainter>
#include <QWidget>

namespace view {

class RotatingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RotatingWidget(int baseW, int baseH, QWidget *parent = nullptr);

public: // Getters and Setters
    TileRotation getRotation() const;
    void setRotation(TileRotation newRotation);

public:
    virtual void paintRotated(QPaintEvent *event, QPainter &painter) = 0;

protected: // QWidget interface
    void paintEvent(QPaintEvent *event) override;

private: // Properties
    int baseWidth, baseHeight;
    TileRotation rotation;
};

} // namespace view

#endif // ROTATINGWIDGET_H
