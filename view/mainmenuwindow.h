#ifndef MAINMENUWINDOW_H
#define MAINMENUWINDOW_H

#include <QMainWindow>

namespace view {

namespace Ui {
class MainMenuWindow;
}

class MainMenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainMenuWindow(QWidget *parent = nullptr);
    ~MainMenuWindow();

public slots:
    void btnExitClick();
    void btnPlayersClick();

private:
    Ui::MainMenuWindow *ui;
};

} // namespace view
#endif // MAINMENUWINDOW_H
