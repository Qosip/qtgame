#ifndef CPP_QT_TPMINIPROJET_MAINWINDOW_H
#define CPP_QT_TPMINIPROJET_MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>

#include <QApplication>
#include <QScreen>
#include <QDesktopWidget>
#include <qstyle.h>
#include <QTimer>

#include "MyView.h"
#include "MyScene.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private :
    QTimer* timerWindow;
    QVector<MyScene*> Scene;
    QGraphicsView* mainView;
    QMenu* helpMenu;
    QGraphicsView* PlayerView;
    MyView* View;
public:

    MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow();

public slots:
    void slot_aboutMenu();
    void update_window();
};


#endif //CPP_QT_TPMINIPROJET_MAINWINDOW_H
