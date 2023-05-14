#ifndef MYVIEW_H
#define MYVIEW_H

#include <QGraphicsView>
#include <QMainWindow>
#include <QResizeEvent>

class MyView : public QGraphicsView{
    Q_OBJECT
public:
    MyView(): QGraphicsView(){

    }
protected:
    /*virtual void resizeEvent (QResizeEvent* event) {
        this->fitInView(sceneRect(), Qt::KeepAspectRatio);
    }*/
};

#endif // MYVIEW_H
