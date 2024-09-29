#ifndef COLORPICKERWIDGET_H
#define COLORPICKERWIDGET_H

#include <QWidget>

namespace view {

namespace Ui {
class ColorPickerWidget;
}

class ColorPickerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ColorPickerWidget(QWidget *parent = nullptr);
    ~ColorPickerWidget();

public:
    QColor getColor() const;
    void setColor(const QColor &newColor);

public: signals:
    void colorPicked(const QColor &color);

protected: // QWidget interface
    void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::ColorPickerWidget *ui;
    QColor color;

};

} // namespace view
#endif // COLORPICKERWIDGET_H
