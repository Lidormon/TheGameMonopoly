#include <QMessageBox>
#include <QInputDialog>
#include <QWidget>
#include "gamewindow.h"
#include "assets.h"
#include "model/companytile.h"
#include "model/player.h"
#include "model/railwaytile.h"
#include "model/luckcardtile.h"
#include "model/taxtile.h"
#include "monopolyerrors.h"
#include "taxwidget.h"
#include "ui_gamewindow.h"
#include "view/companywidget.h"
#include "view/cornerwidget.h"
#include "view/luckcardwidget.h"
#include "view/propertywidget.h"
#include "view/railwaywidget.h"

namespace view {

using namespace model;
using std::to_string;

// ========================= Constructor/Destructor =========================
GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow), game(nullptr)
{
    ui->setupUi(this);
    ui->imgJail->setPixmap(QPixmap(Assets::IMAGE_JAIL_ICON_PATH));

    // Events
    connect(ui->btnRollDice, &QPushButton::clicked, this, &GameWindow::btnRollDiceClick);
    connect(ui->btnFinishTurn, &QPushButton::clicked, this, &GameWindow::btnFinishTurnClick);
    connect(ui->btnUseJailCard, &QPushButton::clicked, this, &GameWindow::btnUseJailCardClick);
    connect(ui->btnBuyProperty, &QPushButton::clicked, this, &GameWindow::btnBuyPropertyClick);
    connect(ui->btnBuyHouse, &QPushButton::clicked, this, &GameWindow::btnBuyHouseClick);
    connect(ui->btnBuyHotel, &QPushButton::clicked, this, &GameWindow::btnBuyHotelClick);
    connect(ui->btnSellHouse, &QPushButton::clicked, this, &GameWindow::btnSellHouseClick);
    connect(ui->btnSellHotel, &QPushButton::clicked, this, &GameWindow::btnSellHotelClick);
    connect(ui->btnPlayerBack, &QPushButton::clicked, this, &GameWindow::btnPlayerBackClick);

}

GameWindow::~GameWindow() {
    delete ui;

    if (game)
        delete game;

    for (const auto *widget : boardSpaces) {
        delete widget;
    }

    for (const auto *widget : playerCards) {
        delete widget;
    }

    for (const auto *widget : playerPieces) {
        delete widget;
    }
}

// ========================= Init =========================

void GameWindow::init(const std::vector<model::Player> &players) {
    game = new Monopoly(players);

    initBoard();
    initPlayerCards(players);
    initPlayerPieces(players);

    updateActions();
}

void GameWindow::initBoard() {
    auto tiles = Assets::getAllTiles();
    std::vector<RotatingWidget *> widgets(tiles.size());
    int len = tiles.size() / 4;
    int rowLen = (len-1)*80 + 2*120;

    ui->imgDie1->move(rowLen/2 - 150, rowLen/2 - 150);
    ui->imgDie1->hide();
    ui->imgDie2->move(rowLen/2 + 50, rowLen/2 + 50);
    ui->imgDie2->hide();


    ui->frmBoard->setFixedSize(rowLen, rowLen);
    for (size_t i = 0; i < tiles.size(); i++) {
        QString name(tiles[i]->getName().c_str());

        switch(tiles[i]->getType()) {
        case MonoTile::TILE_PROPERTY: {
            PropertyTile *tile = (PropertyTile *)tiles[i];
            PropertyWidget *widget = new PropertyWidget(ui->frmBoard);
            widget->setName(name);
            widget->setPropColor(tile->getColor().getColor());
            if (tile->isOwned())
                widget->setOwnerColor(tile->getOwner()->getColor());
            else
                widget->setOwnerColor(Qt::transparent);
            widget->setPrice(tile->getPrice());
            widget->setHouseCount(tile->getHouseCount());
            widgets[i] = widget;
            break;
        } case MonoTile::TILE_RAILWAY: {
            RailwayTile *tile = (RailwayTile *)tiles[i];
            RailwayWidget *widget = new RailwayWidget(ui->frmBoard);
            widget->setName(name);
            if (tile->isOwned())
                widget->setOwnerColor(tile->getOwner()->getColor());
            else
                widget->setOwnerColor(Qt::transparent);
            widgets[i] = widget;
            break;
        } case MonoTile::TILE_COMPANY: {
            CompanyTile *tile = (CompanyTile *)tiles[i];
            CompanyWidget *widget = new CompanyWidget(ui->frmBoard);
            widget->setName(name);
            if (tile->isOwned())
                widget->setOwnerColor(tile->getOwner()->getColor());
            else
                widget->setOwnerColor(Qt::transparent);
            widgets[i] = widget;
            break;
        } case MonoTile::TILE_TAX: {
            TaxTile *tile = (TaxTile *)tiles[i];
            TaxWidget *widget = new TaxWidget(ui->frmBoard);
            widget->setName(name);
            widget->setPrice(tile->getPayOnStep());
            widgets[i] = widget;
            break;
        } case MonoTile::TILE_LUCK_CARD: {
            LuckCardWidget *widget = new LuckCardWidget(ui->frmBoard);
            widget->setName(name);
            widgets[i] = widget;
            break;
        } case MonoTile::TILE_GO: {
            QPixmap image(Assets::IMAGE_GO_PATH);
            widgets[i] = new CornerWidget(image, ui->frmBoard);
            widgets[i]->move(rowLen - 120, rowLen - 120);
            break;
        } case MonoTile::TILE_JAIL: {
            QPixmap image(Assets::IMAGE_JAIL_PATH);
            widgets[i] = new CornerWidget(image, ui->frmBoard);
            widgets[i]->move(0, rowLen - 120);
            break;
        } case MonoTile::TILE_FREE_PARKING: {
            QPixmap image(Assets::IMAGE_FREE_PARIKING_PATH);
            widgets[i] = new CornerWidget(image, ui->frmBoard);
            widgets[i]->move(0, 0);
            break;
        } case MonoTile::TILE_GOTO_JAIL: {
            QPixmap image(Assets::IMAGE_GO_TO_JAIL_PATH);
            widgets[i] = new CornerWidget(image, ui->frmBoard);
            widgets[i]->move(rowLen - 120, 0);
            break;
        }}
    }

    // Position board spaces:
    for (int i = 1; i < len; i++) {
        widgets[i]->setRotation(ROT_UP);
        widgets[i]->move(rowLen - 120 - 80*i, rowLen - 120);
        int i1 = 1*len + i;
        widgets[i1]->setRotation(ROT_RIGHT);
        widgets[i1]->move(0, rowLen - 120 - 80*i);
        int i2 = 2*len + i;
        widgets[i2]->setRotation(ROT_DOWN);
        widgets[i2]->move(120 + 80*(i-1), 0);
        int i3 = 3*len + i;
        widgets[i3]->setRotation(ROT_LEFT);
        widgets[i3]->move(rowLen - 120, 120 + 80*(i-1));
    }
    boardSpaces = widgets;
}

void GameWindow::initPlayerCards(const std::vector<model::Player> &players) {
    ui->sclPlayer->hide();

    ui->lstPlayers->layout()->removeItem(ui->verticalSpacer);
    int id = 0;
    for (const Player &player : players) {
        PlayerCardWidget *widget = new PlayerCardWidget(id);
        ui->lstPlayers->layout()->addWidget(widget);
        playerCards.push_back(widget);
        id++;

        connect(widget, &PlayerCardWidget::click, this, &GameWindow::cardPlayerClick);
    }
    ui->lstPlayers->layout()->addItem(ui->verticalSpacer);

    updatePlayerCards();
    playerCards[0]->setCurrent();
}

void GameWindow::initPlayerPieces(const std::vector<model::Player> &players) {
    for (const Player &player : players) {
        QWidget *wgt = new QWidget(ui->frmBoard);
        wgt->setMinimumSize(10, 10);
        wgt->setMaximumSize(10, 10);
        playerPieces.push_back(wgt);
    }

    updatePlayerPieces();
}

// ========================= Methods =========================

void GameWindow::displayRoll(int roll1, int roll2) {
    switch(roll1) {
    case 1:
        ui->imgDie1->setPixmap(QPixmap(Assets::IMAGE_DIE1_PATH));
        break;
    case 2:
        ui->imgDie1->setPixmap(QPixmap(Assets::IMAGE_DIE2_PATH));
        break;
    case 3:
        ui->imgDie1->setPixmap(QPixmap(Assets::IMAGE_DIE3_PATH));
        break;
    case 4:
        ui->imgDie1->setPixmap(QPixmap(Assets::IMAGE_DIE4_PATH));
        break;
    case 5:
        ui->imgDie1->setPixmap(QPixmap(Assets::IMAGE_DIE5_PATH));
        break;
    case 6:
        ui->imgDie1->setPixmap(QPixmap(Assets::IMAGE_DIE6_PATH));
        break;
    default:
        throw std::out_of_range("Roll must be 1-6. Got " + to_string(roll1));
    }

    switch(roll2) {
    case 1:
        ui->imgDie2->setPixmap(QPixmap(Assets::IMAGE_DIE1_PATH));
        break;
    case 2:
        ui->imgDie2->setPixmap(QPixmap(Assets::IMAGE_DIE2_PATH));
        break;
    case 3:
        ui->imgDie2->setPixmap(QPixmap(Assets::IMAGE_DIE3_PATH));
        break;
    case 4:
        ui->imgDie2->setPixmap(QPixmap(Assets::IMAGE_DIE4_PATH));
        break;
    case 5:
        ui->imgDie2->setPixmap(QPixmap(Assets::IMAGE_DIE5_PATH));
        break;
    case 6:
        ui->imgDie2->setPixmap(QPixmap(Assets::IMAGE_DIE6_PATH));
        break;
    default:
        throw std::out_of_range("Roll must be 1-6. Got " + to_string(roll1));
    }

    ui->imgDie1->show();
    ui->imgDie2->show();
}

void GameWindow::fastStart() {
    game->fastStart();
    updateBoard();
}

void GameWindow::displayLuckCard(const model::LuckCard &card, bool chance) {
    QMessageBox msg;
    msg.setWindowTitle(chance ? LuckCardTile::CHANCE : LuckCardTile::COMMUNITY_CHEST);
    msg.setText(QString::fromStdString(card.getText()));
    msg.setIcon(QMessageBox::Information);
    msg.exec();
}

void GameWindow::update() {
    updateBoard();
    updatePlayerCards();
    updatePlayerPieces();
    updateActions();
    checkWin();
}

void GameWindow::updatePlayerCards() {
    std::string name = game->getCurrentPlayer().getName();

    for (int i = 0; i < game->getPlayers().size(); i++) {
        PlayerCardWidget *widget = playerCards[i];
        const Player &player = game->getPlayers().get(i);

        widget->setName(QString::fromStdString(player.getName()));
        widget->setColor(player.getColor());
        widget->setMoney(player.getMoney());
        widget->setRailways(player.getOwnedTiles().countRailways());
        if (player.isInJail())
            widget->setJail(player.getJailTurns());
        else
            widget->setJail(PlayerCardWidget::NOT_IN_JAIL);
        if (player.getName() == name)
            widget->setCurrent();
        else widget->unsetCurrent();
    }
}

void GameWindow::updateBoard() {
    auto tiles = Assets::getAllTiles();

    for (size_t i = 0; i < tiles.size(); i++) {
        switch(tiles[i]->getType()) {
        case MonoTile::TILE_PROPERTY: {
            PropertyWidget *widget = (PropertyWidget*) boardSpaces[i];
            PropertyTile *prop = (PropertyTile*) tiles[i];
            if (tiles[i]->isOwned())
                widget->setOwnerColor(tiles[i]->getOwner()->getColor());
            widget->setHouseCount(prop->getHouseCount());
        } break;
        case MonoTile::TILE_RAILWAY: {
            RailwayWidget* widget = (RailwayWidget*) boardSpaces[i];
            if (tiles[i]->isOwned())
                widget->setOwnerColor(tiles[i]->getOwner()->getColor());
        } break;
        case MonoTile::TILE_COMPANY: {
            CompanyWidget* widget = (CompanyWidget*) boardSpaces[i];
            if (tiles[i]->isOwned())
                widget->setOwnerColor(tiles[i]->getOwner()->getColor());
        } break;
        default: break;
        }
    }
}

void GameWindow::updateActions() {
    Monopoly::Actions actions = game->getAvailableActions();

    if (actions & Monopoly::ActionRollDice)
        ui->btnRollDice->show();
    else ui->btnRollDice->hide();

    if (actions & Monopoly::ActionFinishTurn)
        ui->btnFinishTurn->show();
    else ui->btnFinishTurn->hide();

    if (actions & Monopoly::ActionUseOutOfJailCard)
        ui->btnUseJailCard->show();
    else ui->btnUseJailCard->hide();

    if (actions & Monopoly::ActionBuyProperty)
        ui->btnBuyProperty->show();
    else ui->btnBuyProperty->hide();

    if (actions & Monopoly::ActionBuyHouse)
        ui->btnBuyHouse->show();
    else ui->btnBuyHouse->hide();

    if (actions & Monopoly::ActionSellHouse)
        ui->btnSellHouse->show();
    else ui->btnSellHouse->hide();

    if (actions & Monopoly::ActionRollDice)
        ui->btnRollDice->show();
    else ui->btnRollDice->hide();

    if (actions & Monopoly::ActionBuyHotel)
        ui->btnBuyHotel->show();
    else ui->btnBuyHotel->hide();

    if (actions & Monopoly::ActionSellHotel)
        ui->btnSellHotel->show();
    else ui->btnSellHotel->hide();

    // Player has no more money, and no more stuff to sell
    if (actions == Monopoly::ActionNone) {
        Player player = game->getCurrentPlayer();
        int i = game->getPlayerTurn();
        delete playerCards[i];
        delete playerPieces[i];
        playerCards.erase(playerCards.begin() + i);
        playerPieces.erase(playerPieces.begin() + i);
        game->playerLooseGame();

        QString text = "Player '" + QString::fromStdString(player.getName()) +
                       "' has lost the game";
        QMessageBox msg;
        msg.setWindowTitle("Game Over");
        msg.setText(text);
        msg.setIcon(QMessageBox::Information);
        msg.exec();

        if (game->getPlayers().size() == 1) {
            QString name = QString::fromStdString(game->getPlayers().get(0).getName());
            QString text = "Player '" + name + "' has won the game";
            QMessageBox box;
            box.setWindowTitle("Congradulations");
            box.setText(text);
            box.setIcon(QMessageBox::Information);
            box.exec();
            this->close();
        }
        else ui->btnFinishTurn->click();
    }
}

void GameWindow::updatePlayerPieces() {
    int len = boardSpaces.size() / 4;
    int rowLen = (len-1)*80 + 2*120;
    std::string name = game->getCurrentPlayer().getName();

    const PlayerList &players = game->getPlayers();
    for (int i = 0; i < players.size(); i++) {
        int playerX = 18 * (i%4) + 8;
        int playerY = 45 + (i/4) * 20;

        int spaceId = players[i].getLocation();
        int spaceX, spaceY;
        int k = spaceId % len;
        switch(spaceId/len) {
        case 0: // Bottom row
            spaceX = rowLen - 120 - 80*k;
            spaceY = rowLen - 120;
            break;
        case 1: // Left row
            spaceX = 0;
            spaceY = rowLen - 120 - 80*k;
            std::swap(playerX, playerY);
            break;
        case 2: // Top row
            spaceX = 120 + 80*(k-1);
            spaceY = 0;
            break;
        case 3: // Right row
            spaceX = rowLen - 120;
            spaceY = 120 + 80*(k-1);
            std::swap(playerX, playerY);
            break;
        default: throw std::runtime_error("Impossible to get here.");
        }

        playerPieces[i]->move(spaceX + playerX, spaceY + playerY);
        if (players[i].getName() == name) {
            playerPieces[i]->setStyleSheet(
                QString("background-color: ") + players[i].getColor().name() + ";" +
                QString("border: 2px solid red;")
                );
        } else {
            playerPieces[i]->setStyleSheet(
                QString("background-color: ") + players[i].getColor().name() + ";" +
                QString("border: 1px solid black;")
                );
        }
    }
}

void GameWindow::checkWin() {
    for (const auto player : game->getPlayers()) {
        if (player.getMoney() >= 4000) {
            QString name = QString::fromStdString(player.getName());
            QString text = "Player '" + name + "' has won the game";
            QMessageBox box;
            box.setWindowTitle("Congradulations");
            box.setText(text);
            box.setIcon(QMessageBox::Information);
            box.exec();
            this->close();
            break;
        }
    }
}


// ========================= Events =========================

void GameWindow::cardPlayerClick(int index) {
    ui->sclPlayers->hide();
    ui->sclPlayer->show();

    const Player &player = game->getPlayers().get(index);

    ui->lblPlayerName->setText(QString::fromStdString(player.getName()));
    ui->lblPlayerName->setStyleSheet(
        QString("color: ") + player.getColor().name()
    );

    QString money("");
    if (player.getMoney() < 0) money.append("- ");
    money.append("$ ").append(QString::number(player.getMoney()));
    ui->lblPlayerMoney->setText(money);

    if (player.isInJail()) {
        QString jailStr =
            QString::number(player.getJailTurns())
            .append(" turns in jail");
        ui->lblJailTurns->setText(jailStr);
        ui->wgtInJail->show();
    } else {
        ui->wgtInJail->hide();
    }
}

void GameWindow::btnPlayerBackClick() {
    ui->sclPlayer->hide();
    ui->sclPlayers->show();
}

void GameWindow::btnRollDiceClick() {
    game->rollDice();
    int roll = game->getLastRoll();
    displayRoll(game->getDie1(), game->getDie2());
    if (!game->getCurrentPlayer().isInJail())
        game->moveCurrentPlayerBy(roll);

    update();
}

void GameWindow::btnFinishTurnClick() {
    ui->imgDie1->hide();
    ui->imgDie2->hide();

    game->finishTurn();

    update();
}

void GameWindow::btnUseJailCardClick() {
    game->useOutOfJailCard();

    update();
}

void GameWindow::btnBuyPropertyClick() {
    game->buyProperty();
    update();
}

void GameWindow::btnBuyHouseClick() {
    const auto &props = game->getBuyableHouseProperties();

    QStringList items;
    for (const auto &prop : props) {
        QString name = QString::fromStdString(prop->getName());
        QString colorName = QString::fromStdString(prop->getColor().getName());
        QString price = QString::number(prop->getHousePrice());
        items.push_back(name + "(" + colorName + ") - $" + price);
    }

    QInputDialog diag;
    diag.setWindowTitle("Buy House");
    diag.setLabelText("Choose a property to buy a house for:");
    diag.setComboBoxEditable(false);
    diag.setComboBoxItems(items);
    // If Cancel button has been pressed
    if (diag.exec() == QDialog::Rejected) return;

    QString choice = diag.textValue();
    int i = items.indexOf(choice);
    game->buyHouse(props[i]);

    update();
}

void GameWindow::btnBuyHotelClick() {
    const auto &props = game->getBuyableHotelProperties();

    QStringList items;
    for (const auto &prop : props) {
        QString name = QString::fromStdString(prop->getName());
        QString colorName = QString::fromStdString(prop->getColor().getName());
        QString price = QString::number(prop->getHotelPrice());
        items.push_back(name + "(" + colorName + ") - $" + price);
    }

    QInputDialog diag;
    diag.setWindowTitle("Buy Hotel");
    diag.setLabelText("Choose a property to buy a hotel for:");
    diag.setComboBoxEditable(false);
    diag.setComboBoxItems(items);
    // If Cancel button has been pressed
    if (diag.exec() == QDialog::Rejected) return;

    QString choice = diag.textValue();
    int i = items.indexOf(choice);
    game->buyHotel(props[i]);

    update();
}

void GameWindow::btnSellHouseClick() {
    const auto &props = game->getSellableHouseProperties();

    QStringList items;
    for (const auto &prop : props) {
        QString name = QString::fromStdString(prop->getName());
        QString colorName = QString::fromStdString(prop->getColor().getName());
        QString price = QString::number(prop->getHousePrice()/2);
        items.push_back(name + "(" + colorName + ") - $" + price);
    }

    QInputDialog diag;
    diag.setWindowTitle("Sell House");
    diag.setLabelText("Choose a property to sell a house from:");
    diag.setComboBoxEditable(false);
    diag.setComboBoxItems(items);
    // If Cancel button has been pressed
    if (diag.exec() == QDialog::Rejected) return;

    QString choice = diag.textValue();
    int i = items.indexOf(choice);
    game->sellHouse(props[i]);

    update();
}

void GameWindow::btnSellHotelClick() {
    const auto &props = game->getSellableHotelProperties();

    QStringList items;
    for (const auto &prop : props) {
        QString name = QString::fromStdString(prop->getName());
        QString colorName = QString::fromStdString(prop->getColor().getName());
        QString price = QString::number(prop->getHotelPrice()/2);
        items.push_back(name + "(" + colorName + ") - $" + price);
    }

    QInputDialog diag;
    diag.setWindowTitle("Sell Hotel");
    diag.setLabelText("Choose a property to sell a hotel from:");
    diag.setComboBoxEditable(false);
    diag.setComboBoxItems(items);
    // If Cancel button has been pressed
    if (diag.exec() == QDialog::Rejected) return;

    QString choice = diag.textValue();
    int i = items.indexOf(choice);
    game->sellHotel(props[i]);

    update();
}

} // namespace view
