#include "playercardwidget.h"
#include "ui_playercardwidget.h"

#include "assets.h"

namespace view {

PlayerCardWidget::PlayerCardWidget(int index, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PlayerCardWidget), index(index) {

    ui->setupUi(this);
    ui->wgtJail->sizePolicy().setRetainSizeWhenHidden(true);
    ui->imgJail->setPixmap(QPixmap(Assets::IMAGE_JAIL_ICON_PATH));
}

PlayerCardWidget::~PlayerCardWidget() {
    delete ui;
}

// ========================= Getters and Setters =========================

int PlayerCardWidget::getIndex() const {
    return index;
}

void PlayerCardWidget::setName(const QString &name) {
    ui->lblName->setText(name);
}

void PlayerCardWidget::setColor(const QColor &color) {
    ui->wgtColor->setStyleSheet(
        QString("background-color: ") + color.name()
    );
}

void PlayerCardWidget::setMoney(int money) {
    QString str("");
    if (money < 0)
        str.append("- ");
    str.append("$ ").append(QString::number(money));
    ui->lblMoney->setText(str);
}

void PlayerCardWidget::setRailways(int railways) {
    QString str("Railways: ");
    str.append(QString::number(railways));
    ui->lblTrains->setText(str);
}

void PlayerCardWidget::setJail(int turns) {
    if (turns == NOT_IN_JAIL) {
        ui->wgtJail->hide();
        return;
    }

    ui->wgtJail->show();

    QString str = QString::number(turns-1) + " turns in jail";

    ui->lblJailTurns->setText(str);
}

void PlayerCardWidget::setCurrent() {
    QFont font = ui->lblName->font();
    font.setBold(true);
    font.setItalic(true);
    ui->lblName->setFont(font);
}

void PlayerCardWidget::unsetCurrent() {
    QFont font = ui->lblName->font();
    font.setBold(false);
    font.setItalic(false);
    ui->lblName->setFont(font);
}

void PlayerCardWidget::mousePressEvent(QMouseEvent *event) {
    emit click(index);
}

} // namespace view
