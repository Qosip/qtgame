#include "E_sorcerer.h"

E_Sorcerer::E_Sorcerer(QString img, float Ox, float Oy, int maxR, int lif) : QGraphicsPixmapItem(QPixmap(img)){
    this->OriginalX = Ox;
    this->OriginalY = Oy;
    this->setPos(Ox, Oy);
    this->loop = 0;
    this->setScale(1.4);
    this->angle = ((rand()%120)/10.0)/12.0;//3.14/12
    this->b_death = false;
    this->randomidle = 0;
    this->loopidle = 300;
    this->sensrun = 1;
    this->maxRange = maxR;
    this->setZValue(3.5);
    this->life = lif;
    this->healthdeco = new QGraphicsPixmapItem(QPixmap("../qtprojetbase/src/character/Heart/bar_deco.png"));
    this->healthdeco->setZValue(3.5);
    this->healthdeco->setPos(-20,-20);
    this->bar = new QGraphicsPixmapItem(QPixmap("../qtprojetbase/src/character/Heart/bar.png"));
    this->bar->setZValue(3.5);
    this->bar->setPos(-20,-20);
    this->full_dead = false;
    this->is_hurting = false;
    this->sens_hurt = 1;
}
void E_Sorcerer::idle(int sens){
    QTransform transform;
    transform.scale(sens, 1);
    if (this->loop<37 && this->loop%6 == 0){
        QPixmap pixmap(QString("../qtprojetbase/src/character/ennemy/sorcerer/idle/idle") + QString::QString::number(loop/6) + QString(".png"));
        pixmap = pixmap.transformed(transform);
        this->setPixmap(pixmap);
    }
    else if (this->loop<61 && this->loop%6 == 0){
        QPixmap pixmap(QString("../qtprojetbase/src/character/ennemy/sorcerer/idle/idle") + QString::QString::number(loop/6) + QString(".png"));
        pixmap = pixmap.transformed(transform);
        this->setPixmap(pixmap);
    }
    else if (this->loop%6 == 0){
        QPixmap pixmap(QString("../qtprojetbase/src/character/ennemy/sorcerer/idle/idle") + QString::QString::number(7) + QString(".png"));
        pixmap = pixmap.transformed(transform);
        this->setPixmap(pixmap);
        this->loop = 37;
    }
    this->loop ++;
}
void E_Sorcerer::attack(int sens){
    QTransform transform;
    transform.scale(sens, 1);
    if (this->loop<61 && this->loop%6 == 0){
        QPixmap pixmap(QString("../qtprojetbase/src/character/ennemy/sorcerer/attack/attack") + QString::QString::number(loop/6) + QString(".png"));
        pixmap = pixmap.transformed(transform);
        this->setPixmap(pixmap);
    }
    else if (this->loop%6 == 0){
        QPixmap pixmap(QString("../qtprojetbase/src/character/ennemy/sorcerer/attack/attack") + QString::QString::number(1) + QString(".png"));
        pixmap = pixmap.transformed(transform);
        this->setPixmap(pixmap);
        this->loop = 1;
    }
    this->loop ++;
}
void E_Sorcerer::death(){
    //faire avec les positions
    if (this->loop>61) {
        this->setZValue(-2);
        this->b_death = true;
        this->full_dead = true;
        this->angle = 0;
    }
    if (this->loop<41 && this->loop%4 == 0){
        this->setPixmap(QString("../qtprojetbase/src/character/ennemy/sorcerer/death/death") + QString::QString::number(loop/4) + QString(".png"));
        if (loop == 16){
            this->setPos(this->pos().rx(), this->pos().ry()-1);
        }
        else if (loop == 20){
            this->setPos(this->pos().rx(), this->pos().ry()-8);
        }
        else if (loop == 24){
            this->setPos(this->pos().rx(), this->pos().ry()-5);
        }
        else if (loop == 28){
            this->setPos(this->pos().rx(), this->pos().ry()-6);
        }
        else if (loop == 32){
            this->setPos(this->pos().rx(), this->pos().ry()+20);
        }
        this->loop++;
    }
    else {
        this->loop++;
    }
}
void E_Sorcerer::run(int sens){
    QTransform transform;
    transform.scale(sens, 1);
    if (this->loop<19 && this->loop%6 == 0){
        QPixmap pixmap(QString("../qtprojetbase/src/character/ennemy/sorcerer/run/run") + QString::QString::number(loop/6) + QString(".png"));
        pixmap = pixmap.transformed(transform);
        this->setPixmap(pixmap);
    }
    else if (this->loop<37 && this->loop%6 == 0){
        QPixmap pixmap(QString("../qtprojetbase/src/character/ennemy/sorcerer/run/run") + QString::QString::number(loop/6) + QString(".png"));
        pixmap = pixmap.transformed(transform);
        this->setPixmap(pixmap);
    }
    else if (this->loop%6 == 0){
        QPixmap pixmap(QString("../qtprojetbase/src/character/ennemy/sorcerer/run/run") + QString::QString::number(5) + QString(".png"));
        pixmap = pixmap.transformed(transform);
        this->setPixmap(pixmap);
        this->loop = 31;
    }
    this->loop ++;
}

void E_Sorcerer::health(){
    QTransform scaleTransform;
    scaleTransform.scale( life/100.0 , 1);
    bar->setTransform(scaleTransform);
    healthdeco->setPos(this->pos().rx() + this->boundingRect().width()/2 - healthdeco->boundingRect().width()/2, this->pos().ry()-30);
    bar->setPos(this->pos().rx()+14 + this->boundingRect().width()/2 - healthdeco->boundingRect().width()/2, this->pos().ry()-30);
}

void E_Sorcerer::hurt(){
    QTransform transform;
    transform.scale(sens_hurt, 1);
    if (this->loop<10 && this->loop%3 == 0){
        this->setPos(this->pos().rx() + 7 * sens_hurt, this->pos().ry());
        if ((this->OriginalX + this->maxRange)>this->pos().rx() && (this->OriginalX - this->maxRange)<this->pos().rx()){
            this->setPos(this->pos().rx() + 20 * sens_hurt, this->pos().ry());        }
        else {
            this->setPos(this->OriginalX, this->OriginalY);
        }
    }
    if (this->loop<19 && this->loop%3 == 0){
        QPixmap pixmap(QString("../qtprojetbase/src/character/ennemy/sorcerer/hurt/hurt") + QString::QString::number(loop/3) + QString(".png"));
        pixmap = pixmap.transformed(transform);
        this->setPixmap(pixmap);
    }
    else if (this->loop>18){
        is_hurting = false;
    }
    this->loop ++;
}

E_Sorcerer::~E_Sorcerer()
{
    delete healthdeco;
    delete bar;
}
