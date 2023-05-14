#include "E_nightborne.h"

E_Nightborne::E_Nightborne(QString img, float Ox, float Oy, int maxR) : QGraphicsPixmapItem(QPixmap(img)){
    this->OriginalX = Ox;
    this->OriginalY = Oy;
    this->setPos(Ox, Oy);
    this->loop = 0;
    this->scale = 3.0;
    this->setScale(scale);
    this->b_death = false;
    this->randomidle = 0;
    this->loopidle = 300;
    this->sensrun = 1;
    this->maxRange = maxR;
    this->setZValue(3.5);
    this->healthdeco = new QGraphicsPixmapItem(QPixmap("../qtprojetbase/src/character/Heart/bar_deco.png"));
    this->healthdeco->setZValue(3.5);
    this->healthdeco->setPos(-20,-20);
    this->bar = new QGraphicsPixmapItem(QPixmap("../qtprojetbase/src/character/Heart/bar.png"));
    this->bar->setZValue(3.5);
    this->bar->setPos(-20,-20);
    this->full_dead = false;
    this->is_hurting = false;
    this->sens_hurt = 1;
    this->max_Health = 400;
    this->life = max_Health;
}

void E_Nightborne::idle(int sens){
    QTransform transform;
    transform.scale(sens, 1);
    if (this->loop<55 && this->loop%6 == 0){
        QPixmap pixmap(QString("../qtprojetbase/src/character/ennemy/NightBorne/idle/idle") + QString::QString::number(loop/6) + QString(".png"));
        pixmap = pixmap.transformed(transform);
        this->setPixmap(pixmap);
    }
    else if (this->loop%6 == 0){
        QPixmap pixmap(QString("../qtprojetbase/src/character/ennemy/NightBorne/idle/idle") + QString::QString::number(1) + QString(".png"));
        pixmap = pixmap.transformed(transform);
        this->setPixmap(pixmap);
        this->loop = 6;
    }
    this->loop ++;
}
void E_Nightborne::attack(int sens){
    QTransform transform;
    transform.scale(sens, 1);
    if (this->loop<73 && this->loop%6 == 0){ //%6 72
        QPixmap pixmap(QString("../qtprojetbase/src/character/ennemy/NightBorne/attack/attack") + QString::QString::number(loop/6) + QString(".png"));
        pixmap = pixmap.transformed(transform);
        this->setPixmap(pixmap);
    }
    else if (this->loop%6 == 0){
        QPixmap pixmap(QString("../qtprojetbase/src/character/ennemy/NightBorne/attack/attack") + QString::QString::number(1) + QString(".png"));
        pixmap = pixmap.transformed(transform);
        this->setPixmap(pixmap);
        this->loop = 6;
    }
    this->loop ++;
}
void E_Nightborne::death(){
    //faire avec les positions
    if (this->loop>95) {
        this->setZValue(-2);
        this->b_death = true;
        this->full_dead = true;
    }
    if (this->loop<93 && this->loop%4 == 0){
        this->setPixmap(QString("../qtprojetbase/src/character/ennemy/NightBorne/death/death") + QString::QString::number(loop/4) + QString(".png"));
        this->loop++;
    }
    else {
        this->loop++;
    }
}
void E_Nightborne::run(int sens){
    QTransform transform;
    transform.scale(sens, 1);
    if (this->loop<37 && this->loop%6 == 0){
        QPixmap pixmap(QString("../qtprojetbase/src/character/ennemy/NightBorne/run/run") + QString::QString::number(loop/6) + QString(".png"));
        pixmap = pixmap.transformed(transform);
        this->setPixmap(pixmap);
    }
    else if (this->loop%6 == 0){
        QPixmap pixmap(QString("../qtprojetbase/src/character/ennemy/NightBorne/run/run") + QString::QString::number(1) + QString(".png"));
        pixmap = pixmap.transformed(transform);
        this->setPixmap(pixmap);
        this->loop = 6;
    }
    this->loop ++;
}

void E_Nightborne::health(){
    QTransform scaleTransform;
    scaleTransform.scale( life/max_Health , 1);
    bar->setTransform(scaleTransform);
    healthdeco->setPos(this->pos().rx() + 1.9*this->boundingRect().width() - healthdeco->boundingRect().width()/2, this->pos().ry() + 50);
    bar->setPos(this->pos().rx()+14 + 1.9*this->boundingRect().width() - healthdeco->boundingRect().width()/2, this->pos().ry() + 50);
}

void E_Nightborne::hurt(){
    QTransform transform;
    transform.scale(sens_hurt, 1);
    if (this->loop<7 && this->loop%3 == 0){
        this->setPos(this->pos().rx() + 7 * sens_hurt, this->pos().ry());
        if ((this->OriginalX + this->maxRange)>this->pos().rx() && (this->OriginalX - this->maxRange)<this->pos().rx()){
            this->setPos(this->pos().rx() + 20 * sens_hurt, this->pos().ry());        }
        else {
            this->setPos(this->OriginalX, this->OriginalY);
        }
    }
    if (this->loop<16 && this->loop%3 == 0){
        QPixmap pixmap(QString("../qtprojetbase/src/character/ennemy/NightBorne/hit/hit") + QString::QString::number(loop/3) + QString(".png"));
        pixmap = pixmap.transformed(transform);
        this->setPixmap(pixmap);
    }
    else if (this->loop>13){
        is_hurting = false;
    }
    this->loop ++;
}

E_Nightborne::~E_Nightborne()
{
    delete healthdeco;
    delete bar;
}
