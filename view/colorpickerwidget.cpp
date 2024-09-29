#include <QColorDialog>
#include "colorpickerwidget.h"
#include "ui_colorpickerwidget.h"

namespace view {

ColorPickerWidget::ColorPickerWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ColorPickerWidget), color(Qt::red)
{
    ui->setupUi(this);
}

ColorPickerWidget::~ColorPickerWidget()
{
    delete ui;
}

QColor ColorPickerWidget::getColor() const { return color; }

void ColorPickerWidget::setColor(const QColor &newColor) {
    color = newColor;
    ui->wgtColor->setStyleSheet(
        QString("background-color: ") + color.name() + QString(";") +
        QString("border: 1px solid;")
    );
}

void ColorPickerWidget::mousePressEvent(QMouseEvent *event) {
    QColorDialog diag;
    this->connect(&diag, &QColorDialog::colorSelected, this, &ColorPickerWidget::colorPicked);
    diag.setCurrentColor(color);
    diag.exec();

    if (diag.selectedColor().isValid())
        setColor(diag.selectedColor());
}

} // namespace view
