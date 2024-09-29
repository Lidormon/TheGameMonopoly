#ifndef PLAYERSWINDOW_H
#define PLAYERSWINDOW_H

#include "model/player.h"
#include "view/colorpickerwidget.h"
#include <QLineEdit>
#include <QMainWindow>

namespace view {

namespace Ui {
class PlayersWindow;
}

class PlayersWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlayersWindow(QWidget *parent = nullptr);
    ~PlayersWindow();

public:
    void setPlayerCount(int count);

public slots:
    void btnStartClick();
    void btnBackClick();

private:
    Ui::PlayersWindow *ui;
    int playerCount;

private:
    bool addPlayer(std::vector<model::Player> &players,
        int id, const QString &name, const QColor &color);
};

} // namespace view
#endif // PLAYERSWINDOW_H
