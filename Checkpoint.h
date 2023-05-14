#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <qdebug>
#include <math.h>

class CheckPoint : public QGraphicsPixmapItem {
private:
    int tile_code;
    float OriginalX;
    float OriginalY;
    float angle;
    bool active;
    int loop;
public:
    CheckPoint(int x, int y, int num) : QGraphicsPixmapItem(QPixmap("../qtprojetbase/src/environement/TransitionLevel/cr1")) {
        this->setPos(x*40-40, y*40 + 10);
        this->setScale(2);
        this->OriginalX = x*40-40;
        this->OriginalY = y*40 + 10;
        this->tile_code = num;
        this->setZValue(3);
        this->active = false;
        this->angle = 0;
        this->loop = 1;
        this->setScale(0.75);
    }
    const bool get_active(){
        bool d = this->active;
        return d;
    }
    const QPointF get_Point(){
        QPointF d(this->pos().rx(),this->pos().ry());
        return d;
    }
    void set_Active(bool acti) {
        this->active = acti;
    }
    void Anim();
    virtual ~CheckPoint();
};


#endif // CHECKPOINT_H
