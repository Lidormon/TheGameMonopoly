#ifndef CORNERWIDGET_H
#define CORNERWIDGET_H

#include "rotatingwidget.h"

namespace view {

class CornerWidget : public RotatingWidget
{
    Q_OBJECT
public:
    explicit CornerWidget(const QPixmap &image, QWidget *parent = nullptr);

public:
    static constexpr int BASE_WIDTH = 120;
    static constexpr int BASE_HEIGHT = 120;

public: // Getters and Setters
    QPixmap getImage() const;
    void setImage(const QPixmap &newImage);


public: // RotatingWidget interface
    void paintRotated(QPaintEvent *event, QPainter &painter) override;

private:
    QPixmap image;
};

} // namespace view

#endif // CORNERWIDGET_H
