#include <QApplication>
#include "mainWindow.h"

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    MainWindow mainWindow;
    //mainWindow.show();
    //mainWindow.showFullScreen();
    return application.exec();
}
