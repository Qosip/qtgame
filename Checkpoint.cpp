#include "Checkpoint.h"


void CheckPoint::Anim(){
    if (active){
        if (loop<43 && loop%7 == 0){
            this->setPixmap(QString("../qtprojetbase/src/environement/TransitionLevel/cv") + QString::QString::number(loop/7) + QString(".png"));
        }
        else if (loop%7 == 0){
            loop = 7;
            this->setPixmap(QString("../qtprojetbase/src/environement/TransitionLevel/cv") + QString::QString::number(loop/7) + QString(".png"));
        }
    }
    else{
        if (loop<43 && loop%7 == 0){
            this->setPixmap(QString("../qtprojetbase/src/environement/TransitionLevel/cr") + QString::QString::number(loop/7) + QString(".png"));
        }
        else if (loop%7 == 0){
            loop = 7;
            this->setPixmap(QString("../qtprojetbase/src/environement/TransitionLevel/cr") + QString::QString::number(loop/7) + QString(".png"));
        }
    }
    loop ++;
    angle += 3.14159/50;
    setPos(OriginalX, this->pos().ry() + sin (angle));
}

CheckPoint::~CheckPoint()
{

}

