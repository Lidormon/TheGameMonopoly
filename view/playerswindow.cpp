#include<QMessageBox>
#include<vector>

#include "playerswindow.h"
#include "ui_playerswindow.h"
#include "view/gamewindow.h"
#include "view/mainmenuwindow.h"
#include "monopoly.h"

namespace view {

using namespace model;
using std::vector, std::to_string;

PlayersWindow::PlayersWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::PlayersWindow), playerCount(0)
{
    ui->setupUi(this);

    connect(ui->btnStart, &QPushButton::clicked, this, &PlayersWindow::btnStartClick);
    connect(ui->btnBack, &QPushButton::clicked, this, &PlayersWindow::btnBackClick);

    ui->clrPlayer1->setColor(QColorConstants::Svg::gold);
    ui->clrPlayer2->setColor(QColorConstants::Svg::teal);
    ui->clrPlayer3->setColor(QColorConstants::Svg::purple);
    ui->clrPlayer4->setColor(QColorConstants::Svg::darkgreen);
    ui->clrPlayer5->setColor(QColorConstants::Svg::turquoise);
    ui->clrPlayer6->setColor(QColorConstants::Svg::orangered);
    ui->clrPlayer7->setColor(QColorConstants::Svg::red);
    ui->clrPlayer8->setColor(QColorConstants::Svg::khaki);
}

PlayersWindow::~PlayersWindow()
{
    delete ui;
}

void PlayersWindow::setPlayerCount(int count) {
    this->playerCount = count;

    if (count > 4) ui->chkFastStart->hide();
    else ui->chkFastStart->show();

    // Show all
    ui->lblPlayer3->show();
    ui->txtPlayer3->show();
    ui->clrPlayer3->show();
    ui->lblPlayer4->show();
    ui->txtPlayer4->show();
    ui->clrPlayer4->show();
    ui->lblPlayer5->show();
    ui->txtPlayer5->show();
    ui->clrPlayer5->show();
    ui->lblPlayer6->show();
    ui->txtPlayer6->show();
    ui->clrPlayer6->show();
    ui->lblPlayer7->show();
    ui->txtPlayer7->show();
    ui->clrPlayer7->show();
    ui->lblPlayer8->show();
    ui->txtPlayer8->show();
    ui->clrPlayer8->show();

    switch (count) {
    case 2:
        ui->lblPlayer3->hide();
        ui->txtPlayer3->hide();
        ui->clrPlayer3->hide();
    case 3:
        ui->lblPlayer4->hide();
        ui->txtPlayer4->hide();
        ui->clrPlayer4->hide();
    case 4:
        ui->lblPlayer5->hide();
        ui->txtPlayer5->hide();
        ui->clrPlayer5->hide();
    case 5:
        ui->lblPlayer6->hide();
        ui->txtPlayer6->hide();
        ui->clrPlayer6->hide();
    case 6:
        ui->lblPlayer7->hide();
        ui->txtPlayer7->hide();
        ui->clrPlayer7->hide();
    case 7:
        ui->lblPlayer8->hide();
        ui->txtPlayer8->hide();
        ui->clrPlayer8->hide();
    case 8: break;
    default: {
        std::string err = "Number of players must be 1-8, count=";
        err += std::to_string(count);
        throw std::out_of_range(err);
        }
    }
}

void PlayersWindow::btnStartClick() {
    vector<Player> players;
    const QString names[] = {
        ui->txtPlayer1->text(), ui->txtPlayer2->text(),
        ui->txtPlayer3->text(), ui->txtPlayer4->text(),
        ui->txtPlayer5->text(), ui->txtPlayer6->text(),
        ui->txtPlayer7->text(), ui->txtPlayer8->text()
    };
    const QColor colors[] = {
        ui->clrPlayer1->getColor(), ui->clrPlayer2->getColor(),
        ui->clrPlayer3->getColor(), ui->clrPlayer4->getColor(),
        ui->clrPlayer5->getColor(), ui->clrPlayer6->getColor(),
        ui->clrPlayer7->getColor(), ui->clrPlayer8->getColor()
    };

    switch (playerCount) {
    case 8:
        if (!addPlayer(players, 7, names[7], colors[7]))
            return;
    case 7:
        if (!addPlayer(players, 6, names[6], colors[6]))
            return;
    case 6:
        if (!addPlayer(players, 5, names[5], colors[5]))
            return;
    case 5:
        if (!addPlayer(players, 4, names[4], colors[4]))
            return;
    case 4:
        if (!addPlayer(players, 3, names[3], colors[3]))
            return;
    case 3:
        if (!addPlayer(players, 2, names[2], colors[2]))
            return;
    case 2:
        if (!addPlayer(players, 1, names[1], colors[1]))
            return;
        if (!addPlayer(players, 0, names[0], colors[0]))
            return;
        break;
    }

    for (int i = 0; i < playerCount; i++) {
        const QColor &color = colors[i];
        const QString &name = names[i];
        for (int j = i + 1; j < playerCount; j++) {
            const QColor &otherColor = colors[j];
            const QString &otherName = names[j];
            if (color == otherColor) {
                QString text("");
                text.append("Player ").append(QString::number(i+1))
                    .append(" can't have the same color as Player ")
                    .append(QString::number(j+1)).append("!");
                QMessageBox msg;
                msg.setWindowTitle("Error");
                msg.setText(text);
                msg.setIcon(QMessageBox::Critical);
                msg.exec();
                return;
            }

            if (name == otherName) {
                QString text("");
                text.append("Player ").append(QString::number(i+1))
                    .append(" can't have the same name as Player ")
                    .append(QString::number(j+1)).append("!");
                QMessageBox msg;
                msg.setWindowTitle("Error");
                msg.setText(text);
                msg.setIcon(QMessageBox::Critical);
                msg.exec();
                return;
            }
        }
    }

    Monopoly::gameWindow->init(players);
    if (ui->chkFastStart->isChecked() && !ui->chkFastStart->isHidden())
        Monopoly::gameWindow->fastStart();
    Monopoly::gameWindow->show();
    this->hide();
}

void PlayersWindow::btnBackClick() {
    Monopoly::menuWindow->show();
    close();
}

bool PlayersWindow::addPlayer(std::vector<model::Player> &players,
int id, const QString &name, const QColor &color) {
    if (name.isEmpty()) {
        QString text = "Player " + QString::number(id+1) + " name is empty!";

        QMessageBox msg;
        msg.setWindowTitle("Error");
        msg.setText(text);
        msg.setIcon(QMessageBox::Critical);
        msg.exec();
        return false;
    }

    players.emplace(players.begin(), name.toStdString(), color);
    return true;
}

} // namespace view
