#include "mainmenuwindow.h"
#include "ui_mainmenuwindow.h"
#include "view/playerswindow.h"

#include <monopoly.h>

namespace view {

constexpr char PROP_PLAYER_COUNT[] = "playerCount";


// ========================= Constructor/Destructor =========================

MainMenuWindow::MainMenuWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainMenuWindow)
{
    ui->setupUi(this);
    ui->btn2Player->setProperty(PROP_PLAYER_COUNT, 2);
    ui->btn3Player->setProperty(PROP_PLAYER_COUNT, 3);
    ui->btn4Player->setProperty(PROP_PLAYER_COUNT, 4);
    ui->btn5Player->setProperty(PROP_PLAYER_COUNT, 5);
    ui->btn6Player->setProperty(PROP_PLAYER_COUNT, 6);
    ui->btn7Player->setProperty(PROP_PLAYER_COUNT, 7);
    ui->btn8Player->setProperty(PROP_PLAYER_COUNT, 8);

    connect(ui->btn2Player, &QPushButton::clicked, this, &MainMenuWindow::btnPlayersClick);
    connect(ui->btn3Player, &QPushButton::clicked, this, &MainMenuWindow::btnPlayersClick);
    connect(ui->btn4Player, &QPushButton::clicked, this, &MainMenuWindow::btnPlayersClick);
    connect(ui->btn5Player, &QPushButton::clicked, this, &MainMenuWindow::btnPlayersClick);
    connect(ui->btn6Player, &QPushButton::clicked, this, &MainMenuWindow::btnPlayersClick);
    connect(ui->btn7Player, &QPushButton::clicked, this, &MainMenuWindow::btnPlayersClick);
    connect(ui->btn8Player, &QPushButton::clicked, this, &MainMenuWindow::btnPlayersClick);
    connect(ui->btnExit, &QPushButton::clicked, this, &MainMenuWindow::btnExitClick);
}

MainMenuWindow::~MainMenuWindow()
{
    delete ui;
}

// ========================= Events =========================

void MainMenuWindow::btnExitClick() {
    this->close();
}

void MainMenuWindow::btnPlayersClick() {
    int count = sender()->property(PROP_PLAYER_COUNT).value<int>();

    Monopoly::playersWindow->setPlayerCount(count);
    Monopoly::playersWindow->show();
    this->hide();
}

} // namespace view
