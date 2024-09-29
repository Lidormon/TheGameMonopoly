#ifndef LUCKCARDWIDGET_H
#define LUCKCARDWIDGET_H

#include "rotatingwidget.h"

namespace view {

class LuckCardWidget : public RotatingWidget
{
    Q_OBJECT
public:
    explicit LuckCardWidget(QWidget *parent = nullptr);

public:
    static constexpr int BASE_WIDTH = 80;
    static constexpr int BASE_HEIGHT = 120;

public: // Getters and Setters
    QString getName() const;
    void setName(const QString &newName);

public: // RotatingWidget interface
    void paintRotated(QPaintEvent *event, QPainter &painter) override;

private: // Properties
    QString name;
};

} // namespace view

#endif // LUCKCARDWIDGET_H
