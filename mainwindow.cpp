#include "mainWindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->Scene.push_back(new MyScene());
    /*this->mainView = new QGraphicsView;
    this->mainView->setScene(Scene[0]);
    this->mainView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->mainView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //mainView->resize(1920, 4000);
    mainView->setWindowTitle("Character View");
    //mainView->show();
    this->mainView->centerOn(0,0);
    this->setCentralWidget(mainView);
    this->setWindowTitle("My main window");*/
    //this->setFixedSize(1140, 642);

    //this->mainView->setSceneRect(0, 0, this->width(), this->height());

    //this->show();
    QImage img("../qtprojetbase/src/environement/background/backgroundlvl1.png");
    /*MyView* */View = new MyView();
    View->setScene(Scene[0]);
    View->setWindowTitle("Perso");
    View->setWindowFlags(Qt::FramelessWindowHint);
    View->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    View->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    View->show();
    View->setAttribute(Qt::WA_TranslucentBackground);

    //positionnement de la fenetre sinon elle se trouve en bas à droit de l'écran
    QScreen* screen = QGuiApplication::screenAt(QCursor::pos()); //on recupere l'ecran sur lequel afficher la fenetre
    QRect screenGeometry = screen->geometry();//taille de l'ecran en question
    int x = screenGeometry.x() + (screenGeometry.width() - size().width()) / 4;
    int y = screenGeometry.y() + (screenGeometry.height() - size().height()) / 4;
    View->move(x, y);

    this->timerWindow = new QTimer(this);
    connect(timerWindow, SIGNAL(timeout()), this, SLOT(update_window()));
    timerWindow->start(15); // 30 //7 possible pour anim payante
}

void MainWindow::update_window(){
    if (Scene[0]->current_lvl==1){
        //qDebug()<<"delete";
        //mainScene->~MyScene();

        //qDebug()<<Scene[0];
        //qDebug()<<"pet111";
        //Scene.remove(0);
        //Scene.clear();
        //this->Scene.push_back(new MyScene());
        //qDebug()<<Scene[0];
        //View->setScene(Scene[0]);
        //this->mainView->setScene(secondScene);

        //delete mainScene;
    }
}

MainWindow::~MainWindow(){

}

void MainWindow::slot_aboutMenu(){
    QMessageBox msgBox;
    msgBox.setText("A small QT/C++ projet...");
    msgBox.setModal(true); // on souhaite que la fenetre soit modale i.e qu'on ne puisse plus cliquer ailleurs
    msgBox.exec();
}
