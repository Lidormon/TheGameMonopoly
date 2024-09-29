#include <QApplication>
#include <iostream>

#include "assets.h"
#include "monopoly.h"
#include "qmessagebox.h"
#include "view/gamewindow.h"
#include "view/mainmenuwindow.h"
#include "view/playerswindow.h"


using namespace view;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    try {
        Assets::init();
    } catch (const std::exception &ex) {
        std::cerr << "Failed to load assets:" << std::endl << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    Monopoly::menuWindow = new MainMenuWindow;
    Monopoly::playersWindow = new PlayersWindow;
    Monopoly::gameWindow = new GameWindow;

    int result;
    try {
        Monopoly::menuWindow->show();
        result = a.exec();
    } catch (std::exception &ex) {
        QMessageBox msg;
        msg.setWindowTitle("An Exception has occured");
        msg.setText(ex.what());
        msg.setIcon(QMessageBox::Critical);
        msg.exec();
        exit(EXIT_FAILURE);
    }

    delete Monopoly::menuWindow;
    delete Monopoly::playersWindow;
    delete Monopoly::gameWindow;
    Assets::release();
    return result;
}
