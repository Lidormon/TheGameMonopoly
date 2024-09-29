#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "model/luckcard.h"
#include "monopoly.h"
#include "view/playercardwidget.h"
#include "view/rotatingwidget.h"
#include <QMainWindow>

namespace view {

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

public:
    void init(const std::vector<model::Player> &players);
    void initBoard();
    void initPlayerCards(const std::vector<model::Player> &players);
    void initPlayerPieces(const std::vector<model::Player> &players);
    void fastStart();

private:
    Ui::GameWindow *ui;

public:
    // void movePlayerTo(int playerId, int spaceId);
    void displayRoll(int roll1, int roll2);
    void displayLuckCard(const model::LuckCard &card, bool chance);

    void update();
    void updatePlayerCards();
    void updateBoard();
    void updateActions();
    void updatePlayerPieces();
    void checkWin();

public slots:
    void btnRollDiceClick();
    void btnFinishTurnClick();
    void btnUseJailCardClick();
    void btnBuyPropertyClick();
    void btnBuyHouseClick();
    void btnBuyHotelClick();
    void btnSellHouseClick();
    void btnSellHotelClick();

    void cardPlayerClick(int index);
    void btnPlayerBackClick();

private:
    Monopoly *game;
    std::vector<view::RotatingWidget*> boardSpaces;
    std::vector<view::PlayerCardWidget*> playerCards;
    std::vector<QWidget*> playerPieces;
};

} // namespace view
#endif // GAMEWINDOW_H
