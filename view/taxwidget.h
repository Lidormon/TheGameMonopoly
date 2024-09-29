#ifndef TAXWIDGET_H
#define TAXWIDGET_H

#include "rotatingwidget.h"

namespace view {

class TaxWidget : public RotatingWidget
{
    Q_OBJECT
public:
    explicit TaxWidget(QWidget *parent = nullptr);

public:
    static constexpr int BASE_WIDTH = 80;
    static constexpr int BASE_HEIGHT = 120;

public: // Getters and Setters
    QString getName() const;
    void setName(const QString &newName);
    int getPrice() const;
    void setPrice(int newPrice);

public: // RotatingWidget interface
    void paintRotated(QPaintEvent *event, QPainter &painter) override;

private: // Properties
    QString name;
    int price;
};

} // namespace view

#endif // TAXWIDGET_H
